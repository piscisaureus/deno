import { assert, fail } from "./assert";
import { Buf } from "./buf";

export interface ArrayBufferViewConstructor<T extends ArrayBufferView> {
  new (from: T): T;
  new (buffer: ArrayBufferLike, byteOffset: number, length: number): T;
}

export interface Message {
  buf: Buf;
  byteOffset: number;
  byteLength: number;
}

export interface QueueCounters {
  role: string;
  spin: number;
  wait: number;
  wake: number;
  wrap: number;
}

interface SliceHeaderInfo {
  length: number;
  isWaste?: boolean;
}

interface SliceInfo extends SliceHeaderInfo {
  offset: number;
  isEndOfBuffer: boolean;
  isWaste: boolean;
}

// prettier-ignore
enum HeaderBits {
  // Low 24 bits are reserved for the slice length (measured in slots),
  // including header slot(s).
  kLengthMask         = 0x00ffffff,
  // Every time a slice changes hands between reader and writer, we add 1 to the
  // 2-bit epoch number, which wraps on overflow.
  kEpochBaseWriter    = 0x00000000,
  kEpochBaseReader    = 0x01000000,
  kEpochTransferDelta = 0x01000000,
  kEpochBufWrapDelta  = 0x02000000,
  kEpochMask          = 0x03000000,
  // Flag that indicates that a readable chunk does not contain useful data,
  // e.g. due to an abandoned write or insufficient space at the end of the
  // buffer.
  kIsWasteFlag        = 0x04000000,
  // Flag that indicates that there are waiter(s).
  kHasWaitersFlag     = 0x08000000,
}

abstract class QueueUser {
  // These constants define spinning behaviour.
  static readonly kSpinCount: number = 100;
  static readonly kSpinYieldCpu: boolean = false;

  // Maximum number of threads that will access the ring buffer simultaneously.
  // Currently we support one reader and one writer only.
  static readonly kMaxConcurrentUsers = 2;

  // Slice allocation alignment (in bytes).
  static readonly kAlignmentBytes = 8;

  // Slot size (in bytes).
  static readonly kSlotByteLength = Int32Array.BYTES_PER_ELEMENT;

  // Length of slice header (in i32 slots).
  static readonly kHeaderLength = 2;

  // Subclasses need to provide a value for kEpochBase.
  static readonly kEpochBase: number;

  private acquireEpoch: number;
  private releaseEpoch: number;
  private acquireOffset: number = 0;
  private releaseOffset: number = 0;

  private waitCounter: number = 0;
  private wakeCounter: number = 0;
  private spinCounter: number = 0;
  private wrapCounter: number = 0;

  constructor(protected buf: Buf) {
    // Set initial acquire and release epoch numbers.
    const Self = this.constructor as any;
    this.acquireEpoch = Self.kEpochBase;
    this.releaseEpoch = Self.kEpochBase + HeaderBits.kEpochTransferDelta;

    // Typically we'd get a buffer that's initialized with zeroes. If that's the
    // case, define a slice that spans the entire buffer and place it's header
    // at offset 0, so the reader and writer don't get confused.
    Atomics.compareExchange(buf.i32, 0, 0, buf.i32.length);
  }

  get counters(): QueueCounters {
    return {
      role: this.constructor.name,
      wait: this.waitCounter,
      wake: this.wakeCounter,
      spin: this.spinCounter,
      wrap: this.wrapCounter
    };
  }

  protected acquireSlice(wait?: true): SliceInfo;
  protected acquireSlice(wait: false): SliceInfo | null;
  protected acquireSlice(wait = true): SliceInfo | null {
    const offset: number = this.acquireOffset;
    let header: number = this.buf.i32[offset];
    let spinCountRemaining: number = QueueUser.kSpinCount;

    while ((header & HeaderBits.kEpochMask) !== this.acquireEpoch) {
      if (!wait) {
        return null;
      }

      let futexWaitTime;
      if (spinCountRemaining === 0) {
        // We're going to put the thread to sleep.
        // Use compare-and-swap to set the kHasWaiters flag.
        const expect = header;
        const target = header | HeaderBits.kHasWaitersFlag;
        header = Atomics.compareExchange(this.buf.i32, offset, expect, target);
        if (expect !== header) {
          // The buffer slot that holds the header has been modified after we
          // last read it; compareExchange did not set the flag, but `header`
          // is now up-to-date again.
          continue;
        }
        header = target;
        futexWaitTime = Infinity;
        this.waitCounter++;
      } else {
        // We're spinning. If CPU yielding is enabled, we'll call futexWait
        // as if we were going to sleep, but with a timeout of 1ms. If CPU
        // yielding is off we'll just refresh `header` from the ring buffer.
        futexWaitTime = QueueUser.kSpinYieldCpu ? 1 : null;
        spinCountRemaining--;
        this.spinCounter++;
      }

      if (
        futexWaitTime === null ||
        Atomics.wait(this.buf.i32, offset, header, futexWaitTime) !==
          "timed-out"
      ) {
        // If futexWait returned "ok" or "not-equal", the value in the buffer
        // is different from our local copy, so refresh it.
        header = Atomics.load(this.buf.i32, offset);
      }
    }

    const length = header & HeaderBits.kLengthMask;
    const isWaste = Boolean(header & HeaderBits.kIsWasteFlag);

    const endOffset = offset + length;
    assert(endOffset <= this.buf.i32.length);
    const isEndOfBuffer = endOffset === this.buf.i32.length;

    if (!isEndOfBuffer) {
      this.acquireOffset = endOffset;
    } else {
      this.acquireEpoch = this.wrapEpoch(this.acquireEpoch);
      this.acquireOffset = 0;
      this.wrapCounter++;
    }

    return { offset, length, isEndOfBuffer, isWaste };
  }

  protected releaseSlice({ length, isWaste = false }: SliceHeaderInfo): void {
    const offset: number = this.releaseOffset;

    assert(length >= QueueUser.kHeaderLength);
    assert((length & ~HeaderBits.kLengthMask) === 0);
    assert(offset + length <= this.buf.i32.length);

    const flags = Number(isWaste) * HeaderBits.kIsWasteFlag;
    const header = length | flags | this.releaseEpoch;
    const previous = Atomics.exchange(this.buf.i32, offset, header);

    if (previous & HeaderBits.kHasWaitersFlag) {
      Atomics.wake(this.buf.i32, offset, QueueUser.kMaxConcurrentUsers);
      this.wakeCounter++;
    }

    const endOffset = offset + length;
    assert(endOffset <= this.buf.i32.length);
    const isEndOfBuffer = endOffset === this.buf.i32.length;

    if (!isEndOfBuffer) {
      this.releaseOffset = endOffset;
    } else {
      this.releaseEpoch = this.wrapEpoch(this.releaseEpoch);
      this.releaseOffset = 0;
    }
  }

  private wrapEpoch(epoch: number) {
    return (epoch + HeaderBits.kEpochBufWrapDelta) & HeaderBits.kEpochMask;
  }
}

export class QueueWriter extends QueueUser {
  static readonly kEpochBase = HeaderBits.kEpochBaseWriter;

  // The length *in slots* of the allocation we made for the user,
  // including header and padding.
  private allocationLength: number = -1;

  // The number of bytes allocated for the user, *not* including the header,
  // and the byte offset into the underlying `Buf`.
  private messageByteOffset: number = -1;
  private messageByteLength: number = -1;

  // This slice spans the part of the buffer that has been reserved for the
  // current (or next) message that will be written to the buffer. Note
  // that writeSlice may be non-null even when we're not writing.
  private writeSlice: SliceInfo | null = null;

  beginWrite(byteLength: number) {
    if (this.allocationLength >= 0) {
      throw new Error("Already writing.");
    }
    return this.allocate(byteLength);
  }

  // TODO: copy bytes when allocation wraps.
  resizeWrite(byteLength: number) {
    if (this.allocationLength < 0) {
      throw new Error("Not writing.");
    }
    return this.allocate(byteLength);
  }

  endWrite(submit = true): void {
    if (this.allocationLength < 0) {
      throw new Error("Not writing.");
    }

    if (submit) {
      const length = this.allocationLength;
      this.releaseSlice({ length });

      if (this.writeSlice === null) {
        fail("this.writeSlice should not be null");
      } else if (this.writeSlice.length === length) {
        this.writeSlice = null;
      } else {
        this.writeSlice.offset += length;
        this.writeSlice.length -= length;
        this.messageByteOffset += length * QueueWriter.kSlotByteLength;
      }
    }

    this.allocationLength = -1;
  }

  write(data: ArrayBufferView): void {
    // Allocate space.
    const range = this.beginWrite(data.byteLength);

    let submit = false;
    try {
      // Copy data into buffer.
      const sourceView = new Uint8Array(
        data.buffer,
        data.byteOffset,
        data.byteLength
      );
      const targetView = new Uint8Array(
        range.buf.ab,
        range.byteOffset,
        range.byteLength
      );
      targetView.set(sourceView);
      submit = true;
    } finally {
      this.endWrite(submit);
    }
  }

  private allocate(messageByteLength: number): Message {
    // Compute the total required length, including header and padding,
    // in slots - not bytes.
    const messageLength =
      this.align(messageByteLength) / QueueWriter.kSlotByteLength;
    const targetLength = QueueWriter.kHeaderLength + messageLength;

    // Bootstrap writeSlice if it isn't set, and compute the byte offset of the
    // message payload into the underlying `Buf`.
    if (this.writeSlice === null) {
      this.writeSlice = this.acquireSlice();
      this.messageByteOffset =
        (this.writeSlice.offset + QueueWriter.kHeaderLength) *
        QueueWriter.kSlotByteLength;
    }

    // Acquire slices until we have the number of slots required.
    while (this.writeSlice.length < targetLength) {
      if (this.writeSlice.isEndOfBuffer) {
        // Can't wrap around the end of the ring buffer. Discard what we got
        // so far and start over at the beginning of the buffer.
        this.releaseSlice({ ...this.writeSlice, isWaste: true });
        this.writeSlice = null;

        // Create a new allocation from scratch.
        return this.allocate(messageByteLength);
      }

      // Acquire the next slice and use it to make `writeSlice` longer.
      let h = this.acquireSlice();
      this.writeSlice.length += h.length;
      this.writeSlice.isEndOfBuffer = h.isEndOfBuffer;
    }

    // Update the stored lengths. The offset is updated in
    // acquireInitialSlice(), so we don't need to do that here.
    this.allocationLength = targetLength;
    this.messageByteLength = messageByteLength;

    // Return information about the new allocation.
    return {
      buf: this.buf,
      byteOffset: this.messageByteOffset,
      byteLength: this.messageByteLength
    };
  }

  private align(byteCount: number) {
    const alignmentMask = QueueUser.kAlignmentBytes - 1;
    return (byteCount + alignmentMask) & ~alignmentMask;
  }
}

export class QueueReader extends QueueUser {
  static readonly kEpochBase: number = HeaderBits.kEpochBaseReader;

  private readSlice: SliceInfo | null = null;

  beginRead(): Message {
    if (this.readSlice !== null) {
      throw new Error("Already reading.");
    }
    this.readSlice = this.acquireSlice();
    return {
      buf: this.buf,
      byteOffset:
        (this.readSlice.offset + QueueReader.kHeaderLength) *
        QueueReader.kSlotByteLength,
      byteLength:
        (this.readSlice.length - QueueReader.kHeaderLength) *
        QueueReader.kSlotByteLength
    };
  }

  endRead(release = true): void {
    if (this.readSlice === null) {
      throw new Error("Not reading.");
    }
    if (release) {
      this.releaseSlice(this.readSlice);
    }
    this.readSlice = null;
  }

  readInto<T extends ArrayBufferView>(
    viewConstructor: ArrayBufferViewConstructor<T>
  ): T {
    const message = this.beginRead();
    let view: T | undefined;
    try {
      // Create a view of the proper type on the underlying ArrayBuffer,
      // then call the constructor again to make a copy. Assign to a variable
      // so we can tell success from failure in the `finally` block.
      // TODO: This is slow (>2x slowdown); find a more efficient solution.
      view = new viewConstructor(
        new viewConstructor(
          message.buf.ab,
          message.byteOffset,
          message.byteLength
        )
      );
      return view;
    } finally {
      // Only release the slice if creating the view succeeded.
      this.endRead(view !== undefined);
    }
  }
}
