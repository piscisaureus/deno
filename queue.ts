import { assert, fail, unreachable } from "./assert";

type TypedArray =
  | Int8Array
  | Uint8Array
  | Uint8ClampedArray
  | Int16Array
  | Uint16Array
  | Int32Array
  | Uint32Array
  | Float32Array
  | Float64Array;

export interface TypedArrayConstructor<T extends TypedArray> {
  new (arrayOrArrayBuffer: ArrayLike<number> | ArrayBufferLike): T;
  new (buffer: ArrayBufferLike, byteOffset: number, length?: number): T;
  readonly BYTES_PER_ELEMENT: number;
}

export interface QueueCounters {
  role: string;
  message: number;
  acquire: number;
  release: number;
  spin: number;
  wait: number;
  wake: number;
  wrap: number;
}

export interface PayloadSlice {
  byteOffset: number;
  byteLength: number;
}

interface SliceHeaderInfo {
  byteLength: number;
  isWaste?: boolean;
}

interface SliceInfo extends SliceHeaderInfo {
  // `position` is counted in bytes, but it's not affected by whether the buffer
  // is filled top-down or bottom-up.
  // IOW, the first slice in a buffer always has position == 0.
  position: number;
  isEndOfBuffer: boolean;
  isWaste: boolean;
}

// prettier-ignore
const enum HeaderBits {
  // Low 24 bits are reserved for the length of the slice (including header).
  kByteLengthMask     = 0x00ffffff,
  // Every time a slice changes hands between reader and writer, we add 1 to the
  // 2-bit epoch number, which wraps on overflow.
  kEpochTransferDelta = 0x01000000,
  kEpochBufWrapDelta  = 0x02000000,
  kEpochMask          = 0x03000000,
  // Initial (acquire) epoch values for respectively the writer and the reader.
  kEpochBaseWriter    = 0x00000000,
  kEpochBaseReader    = 0x01000000,  
  // Flag that indicates to reader that a slice does not have a payload, due to
  // to an abandoned write or insufficient space at the end of the buffer.
  kIsWasteFlag        = 0x04000000,
  // Flag that indicates that there are waiter(s) that expect to be notified.
  kHasWaitersFlag     = 0x08000000,
}

const enum FillDirection {
  kTopDown = 0,
  kBottomUp = 1
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

  // Length of slice header.
  static readonly kHeaderByteLength = 8;

  // Subclasses need to provide a value for kEpochBase.
  static readonly kEpochBase: number;

  public readonly buffer: SharedArrayBuffer;
  public readonly u8: Uint8Array;
  public readonly i32: Int32Array;
  public readonly u32: Uint32Array;

  // Cache the buffer length because it's much faster than buffer.byteLength;
  public readonly bufferByteLength: number;

  private acquireEpoch: number;
  private releaseEpoch: number;
  private acquirePosition: number = 0;
  private releasePosition: number = 0;

  protected messageCounter: number = 0;
  private acquireCounter: number = 0;
  private releaseCounter: number = 0;
  private waitCounter: number = 0;
  private wakeCounter: number = 0;
  private spinCounter: number = 0;
  private wrapCounter: number = 0;

  static readonly kFillDirection: FillDirection = FillDirection.kTopDown;
  protected readonly fillDirectionBaseAdjustment: number;
  protected readonly fillDirectionOffsetAdjustment: number;

  // `buffer` must be initialized with zeroes.
  constructor(buffer: SharedArrayBuffer) {
    // Set fill direction adjustment constants.
    switch (QueueUser.kFillDirection) {
      case FillDirection.kTopDown:
        this.fillDirectionOffsetAdjustment = 1;
        this.fillDirectionBaseAdjustment = 0;
        break;
      case FillDirection.kBottomUp:
        this.fillDirectionOffsetAdjustment = -1;
        this.fillDirectionBaseAdjustment = 1;
        break;
      default:
        throw unreachable();
    }

    // Set initial acquire and release epoch numbers.
    const Self = this.constructor as any;
    this.acquireEpoch = Self.kEpochBase;
    this.releaseEpoch = Self.kEpochBase + HeaderBits.kEpochTransferDelta;

    // Create various views on the SharedArrayBuffer.
    this.buffer = buffer.slice();
    this.u8 = new Uint8Array(buffer);
    this.i32 = new Int32Array(buffer);
    this.u32 = new Uint32Array(buffer);

    // Initialize the slice structure inside the buffer.
    this.bufferByteLength = buffer.byteLength;
    this.initBufferSlice();
  }

  get counters(): QueueCounters {
    return {
      role: this.constructor.name,
      message: this.messageCounter,
      acquire: this.acquireCounter,
      release: this.releaseCounter,
      wait: this.waitCounter,
      wake: this.wakeCounter,
      spin: this.spinCounter,
      wrap: this.wrapCounter
    };
  }

  private initBufferSlice() {
    // Typically we'd get a buffer that's initialized with zeroes. If that's the
    // case, define a slice that spans the entire buffer and place it's header
    // at offset 0, so the reader and writer don't get confused.
    Atomics.compareExchange(
      this.i32,
      (this.fillDirectionBaseAdjustment *
        (this.bufferByteLength - QueueUser.kHeaderByteLength)) /
        this.i32.BYTES_PER_ELEMENT,
      0,
      this.bufferByteLength
    );
  }

  protected acquireSlice(wait?: true): SliceInfo;
  protected acquireSlice(wait: false): SliceInfo | null;
  protected acquireSlice(wait = true): SliceInfo | null {
    const position: number = this.acquirePosition;

    // Compute the directionality-adjusted header offset.
    const headerByteOffset: number =
      this.fillDirectionBaseAdjustment *
        (this.bufferByteLength - QueueUser.kHeaderByteLength) +
      this.fillDirectionOffsetAdjustment * position;
    const headerI32Offset = headerByteOffset / this.i32.BYTES_PER_ELEMENT;

    let header: number = this.i32[headerI32Offset];
    let spinCountRemaining: number = QueueUser.kSpinCount;

    while ((header & HeaderBits.kEpochMask) !== this.acquireEpoch) {
      if (!wait) {
        return null;
      }

      let futexWaitTime: number | null;
      if (spinCountRemaining === 0) {
        // We're going to put the thread to sleep.
        // Use compare-and-swap to set the kHasWaiters flag.
        const expect = header;
        const target = header | HeaderBits.kHasWaitersFlag;
        header = Atomics.compareExchange(
          this.i32,
          headerI32Offset,
          expect,
          target
        );
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
        // as if we were going to sleep, but with a timeout of 0.1ms. If CPU
        // yielding is off we'll just refresh `header` from the ring buffer.
        futexWaitTime = QueueUser.kSpinYieldCpu ? 0.1 : null;
        spinCountRemaining--;
        this.spinCounter++;
      }

      if (
        futexWaitTime === null ||
        Atomics.wait(this.i32, headerI32Offset, header, futexWaitTime) !==
          "timed-out"
      ) {
        // If futexWait returned "ok" or "not-equal", the value in the buffer
        // is different from our local copy, so refresh it.
        header = Atomics.load(this.i32, headerI32Offset);
      }
    }

    const byteLength = header & HeaderBits.kByteLengthMask;
    const isWaste = Boolean(header & HeaderBits.kIsWasteFlag);

    const nextPosition = position + byteLength;
    assert(nextPosition <= this.bufferByteLength);
    const isEndOfBuffer = nextPosition === this.bufferByteLength;

    if (!isEndOfBuffer) {
      this.acquirePosition = nextPosition;
    } else {
      this.acquireEpoch = this.wrapEpoch(this.acquireEpoch);
      this.acquirePosition = 0;
      this.wrapCounter++;
    }

    this.acquireCounter++;
    return { position, byteLength, isEndOfBuffer, isWaste };
  }

  protected releaseSlice({
    byteLength,
    isWaste = false
  }: SliceHeaderInfo): void {
    const position: number = this.releasePosition;

    assert(byteLength >= QueueUser.kHeaderByteLength);
    assert((byteLength & ~HeaderBits.kByteLengthMask) === 0);
    assert(position + byteLength <= this.bufferByteLength);

    // Compute the directionality-adjusted header offset.
    const headerByteOffset: number =
      this.fillDirectionBaseAdjustment *
        (this.bufferByteLength - QueueUser.kHeaderByteLength) +
      this.fillDirectionOffsetAdjustment * position;
    const headerI32Offset = headerByteOffset / this.i32.BYTES_PER_ELEMENT;

    const flags = isWaste ? HeaderBits.kIsWasteFlag : 0;
    const header = byteLength | flags | this.releaseEpoch;
    const previous = Atomics.exchange(this.i32, headerI32Offset, header);
    this.i32[headerI32Offset + 1] =
      this.releaseEpoch / HeaderBits.kEpochTransferDelta;

    if (previous & HeaderBits.kHasWaitersFlag) {
      Atomics.wake(this.i32, headerI32Offset, QueueUser.kMaxConcurrentUsers);
      this.wakeCounter++;
    }

    const nextPosition = position + byteLength;
    assert(nextPosition <= this.bufferByteLength);
    const isEndOfBuffer = nextPosition === this.bufferByteLength;

    if (!isEndOfBuffer) {
      this.releasePosition = nextPosition;
    } else {
      this.releaseEpoch = this.wrapEpoch(this.releaseEpoch);
      this.releasePosition = 0;
    }

    this.releaseCounter++;
  }

  private wrapEpoch(epoch: number) {
    return (epoch + HeaderBits.kEpochBufWrapDelta) & HeaderBits.kEpochMask;
  }
}

export class QueueWriter extends QueueUser {
  static readonly kEpochBase = HeaderBits.kEpochBaseWriter;

  // The size of the allocation we made for the message, including header and
  // alignment padding.
  private allocationByteLength: number = -1;

  // This slice spans the part of the buffer that has been reserved for the
  // current (or next) message that will be written to the buffer. Note
  // that writeSlice may be non-null even when we're not writing.
  private writeSlice: SliceInfo;

  constructor(buffer: SharedArrayBuffer) {
    super(buffer);
    this.writeSlice = this.acquireSlice();
  }

  // Note: byteLength will be rounded up to alignment.
  beginWrite(byteLength: number) {
    if (this.allocationByteLength >= 0) {
      throw new Error("Already writing.");
    }
    return this.allocate(byteLength);
  }

  // Note: byteLength will be rounded up to alignment.
  // TODO: copy bytes when allocation wraps.
  resizeWrite(byteLength: number) {
    if (this.allocationByteLength < 0) {
      throw new Error("Not writing.");
    }
    return this.allocate(byteLength);
  }

  endWrite(submit = true): void {
    if (this.allocationByteLength < 0) {
      throw new Error("Not writing.");
    }

    if (submit) {
      const byteLength = this.allocationByteLength;
      this.releaseSlice({ byteLength });

      // Compute the length and offsets of the part of writeSlice that remains
      // reserved after emitting the allocated part as a slice.
      this.writeSlice.position += byteLength;
      this.writeSlice.byteLength -= byteLength;

      this.messageCounter++;
    }

    this.allocationByteLength = -1;
  }

  write(data: ArrayBufferView): void {
    // Convert `data` to an Uint8Array if necessary.
    const u8data: Uint8Array =
      data instanceof Uint8Array
        ? data
        : new Uint8Array(data.buffer, data.byteOffset, data.byteLength);
    // Allocate space.
    const target = this.beginWrite(data.byteLength);
    // Copy data.
    let submit = false;
    try {
      this.u8.set(u8data, target.byteOffset);
      submit = true;
    } finally {
      // Finalize.
      this.endWrite(submit);
    }
  }

  private allocate(requestedByteLength: number): PayloadSlice {
    // Compute the total required length, including header and padding,
    // in slots - not bytes.
    const targetByteLength =
      QueueWriter.kHeaderByteLength + this.align(requestedByteLength);

    // Acquire slices until we have the number of slots required.
    while (this.writeSlice.byteLength < targetByteLength) {
      if (this.writeSlice.isEndOfBuffer) {
        // Can't wrap around the end of the ring buffer. Discard what we got
        // so far and start over at the beginning of the buffer.
        if (this.writeSlice.byteLength > 0) {
          this.releaseSlice({ ...this.writeSlice, isWaste: true });
        }

        // Create a new allocation from scratch.
        this.writeSlice = this.acquireSlice();
        return this.allocate(requestedByteLength);
      }

      // Acquire the next slice and use it to make `writeSlice` longer.
      let h = this.acquireSlice();
      this.writeSlice.byteLength += h.byteLength;
      this.writeSlice.isEndOfBuffer = h.isEndOfBuffer;
    }

    // Update the stored lengths. The offset is updated in
    // acquireInitialSlice(), so we don't need to do that here.
    this.allocationByteLength = targetByteLength;

    // Adjust for for buffers that grow bottom-up.
    const payloadByteLength = targetByteLength - QueueWriter.kHeaderByteLength;
    const payloadByteOffset =
      this.fillDirectionBaseAdjustment *
        (this.bufferByteLength - payloadByteLength) +
      this.fillDirectionOffsetAdjustment *
        (this.writeSlice.position + QueueWriter.kHeaderByteLength);

    // Return information about the new allocation.
    return {
      byteOffset: payloadByteOffset,
      byteLength: payloadByteLength
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

  beginRead(): PayloadSlice {
    if (this.readSlice !== null) {
      throw new Error("Already reading.");
    }

    let readSlice = this.acquireSlice();
    while (readSlice.isWaste) {
      this.releaseSlice(readSlice);
      readSlice = this.acquireSlice();
    }
    this.readSlice = readSlice;

    // Compute the offset and length of the payload (the part after the header),
    // making adjustments for buffers that grow bottom-up.
    const payloadByteLength =
      readSlice.byteLength - QueueReader.kHeaderByteLength;
    const payloadByteOffset =
      this.fillDirectionBaseAdjustment *
        (this.bufferByteLength - payloadByteLength) +
      this.fillDirectionOffsetAdjustment *
        (readSlice.position + QueueReader.kHeaderByteLength);

    return {
      byteOffset: payloadByteOffset,
      byteLength: payloadByteLength
    };
  }

  endRead(release = true): void {
    if (this.readSlice === null) {
      throw new Error("Not reading.");
    }
    if (release) {
      this.releaseSlice(this.readSlice);
      this.messageCounter++;
    }
    this.readSlice = null;
  }

  readInto<T extends TypedArray>(ctor: TypedArrayConstructor<T>): T {
    const payload = this.beginRead();
    let copy: T | undefined;
    try {
      // TODO: This is slow (>2x slowdown); find a more efficient solution.
      let view: T = new ctor(
        this.buffer,
        payload.byteOffset,
        payload.byteLength / ctor.BYTES_PER_ELEMENT
      );
      copy = new ctor(view);
      return copy;
    } finally {
      // Only release the slice if creating the view succeeded.
      this.endRead(copy !== undefined);
    }
  }
}
