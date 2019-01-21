export type TypedArray =
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

export interface Message {
  byteOffset: number;
  byteLength: number;
}

export interface Counters {
  role: string;
  message: number;
  acquire: number;
  release: number;
  spin: number;
  wait: number;
  wake: number;
  wrap: number;
}

// prettier-ignore
const enum SliceHeader {
  // Pseudo-header returned when no slice could be acquired.
  None               = 0x00000000,
  // Low 24 bits are reserved for the length of the slice (including header).
  ByteLengthMask     = 0x00ffffff,
  // Every time a slice changes hands between receiver and sender, we add 1 to
  // the 2-bit epoch number, which wraps on overflow.
  EpochTransferDelta = 0x01000000,
  EpochBufWrapDelta  = 0x02000000,
  EpochMask          = 0x03000000,
  // Initial epoch values for respectively the sender and the receiver.
  EpochBaseSender    = 0x00000000,
  EpochBaseReceiver  = 0x01000000,
  // Flag that indicates to receiver that a slice contains a message. It may not
  // due to an abandoned send or insufficient space at the end of the buffer.
  HasMessageFlag     = 0x04000000,
  // Flag that indicates that there are waiter(s) that expect to be notified.
  HasWaitersFlag     = 0x08000000,
}

type OptionsObject<T> = { -readonly [P in keyof T]?: T[P] };
export type MsgRingOptions = OptionsObject<MsgRingDefaultOptions>;

export const enum FillDirection {
  TopDown,
  BottomUp
}

abstract class MsgRingDefaultOptions {
  // Whether buffers are filled upwards or downwards.
  readonly fillDirection: FillDirection = FillDirection.BottomUp;

  // The maximum number of times acquireSlice() will spin before sleeping.
  readonly spinCount: number = 100;

  // When spinning, for how long the thread yields the CPU on each cycle, in
  // milliseconds. Yielding happens by calling Atomics.wait() with a time-out.
  // Set to zero to never yield the CPU.
  readonly spinYieldCpuTime: number = 0;
}

abstract class MsgRingAccess extends MsgRingDefaultOptions {
  // Slice allocation alignment (in bytes).
  static readonly kAlignmentByteLength = 8;

  // Length of slice header.
  static readonly kHeaderByteLength = 8;

  // Maximum fraction of the buffer that can be allocated to a single message.
  static readonly kMaxMessageSizeDenom = 4; // Quarter of the buffer.

  // Role-dependent initial epoch. Subclasses should assign a value to it.
  static readonly kEpochBase: number;

  // We'll create some (public) views on the underlying buffer. It's much
  // faster to recycle these than to create them on the spot every time, and
  // also much faster than using a DataView. They are public so whoever needs
  // to receive/send a message payload can use them too.
  public readonly u8: Uint8Array;
  public readonly i32: Int32Array;
  public readonly u32: Uint32Array;

  // Cache the buffer length because it's much faster than buffer.byteLength.
  // (Which is in itself quite surprising -- I suspect that
  // SharedArrayBuffer.byteLength incurs a runtime call, possibly to check
  // whether the buffer has been neutered.)
  public readonly bufferByteLength: number;

  // The maximum message size of a message.
  public readonly maxMessageByteLength: number;

  // These constant properties are used to adjust adjust offsets based on the
  // fill direction of the buffer.
  private readonly fillDirectionBaseAdjustment: 0 | 1;
  private readonly fillDirectionOffsetAdjustment: 1 | -1;

  // The head and tail position indicate the range of bytes (slice) that is
  // locked by this receiver/sender. The value indicates the offset in bytes
  // from the start of the ring buffer, ***NOT*** adjusted for fill direction of
  // the buffer. Hence the first slice always starts at position 0.
  protected sliceHeadPosition: number = 0;
  protected sliceTailPosition: number = 0;

  // The slice byte length and whether it's at the end of the buffer can be
  // computed from the head and tail position. However we store them because
  // they are used often.
  protected sliceByteLength: number = 0;
  protected sliceIsAtEndOfBuffer: boolean = false;

  // The epoch number identifies who (receiver or sender) released a slice and
  // whether the header was written after wrapping around the end of the buffer.
  private epoch: number;

  // Counters for debugging.
  protected messageCounter: number = 0;
  private acquireCounter: number = 0;
  private releaseCounter: number = 0;
  private waitCounter: number = 0;
  private wakeCounter: number = 0;
  private spinCounter: number = 0;
  private wrapCounter: number = 0;

  // `buffer` must be initialized with zeroes.
  constructor(
    readonly buffer: SharedArrayBuffer,
    options: MsgRingOptions = {}
  ) {
    // Initialize (default) options.
    super();
    Object.assign(this, options);

    // Set fill direction adjustment constants.
    switch (this.fillDirection) {
      case FillDirection.TopDown:
        this.fillDirectionOffsetAdjustment = 1;
        this.fillDirectionBaseAdjustment = 0;
        break;
      case FillDirection.BottomUp:
        this.fillDirectionOffsetAdjustment = -1;
        this.fillDirectionBaseAdjustment = 1;
        break;
      default:
        throw new Error("Invalid fill direction.");
    }

    this.bufferByteLength = buffer.byteLength;
    this.maxMessageByteLength =
      (Math.min(
        SliceHeader.ByteLengthMask,
        this.bufferByteLength / MsgRingAccess.kMaxMessageSizeDenom
      ) -
        MsgRingAccess.kHeaderByteLength) &
      ~(MsgRingAccess.kAlignmentByteLength - 1);

    // Create various views on the SharedArrayBuffer.
    this.u8 = new Uint8Array(buffer);
    this.i32 = new Int32Array(buffer);
    this.u32 = new Uint32Array(buffer);

    // Set role-dependent initial epoch.
    const Self = this.constructor as typeof MsgRingAccess;
    this.epoch = Self.kEpochBase;

    // Initialize the slice structure inside the buffer.
    // We expect the buffer to be initialized with zeroes. If that's the
    // case, define a slice that spans the entire buffer and place it's header
    // at offset 0, so the receiver and sender don't get confused.
    // Since the other user (receiver/sender) may have gotten here first, only
    // do the initializtion if the first slot is still contains zero.
    Atomics.compareExchange(
      this.i32,
      this.getHeaderI32Offset(0),
      0,
      this.bufferByteLength
    );
  }

  get counters(): Counters {
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

  protected assert(condition: boolean): void {
    if (!condition) {
      throw new Error(`${this.constructor.name}: assertion failed.`);
    }
  }

  protected acquireSlice(wait = true): number {
    // Wrap around if the current head position is at the end of the buffer.
    if (this.sliceIsAtEndOfBuffer) {
      // A slice can't wrap around the end of the buffer; if the current slice
      // is at the end of the buffer, the caller should release the remaining
      // bytes before attempting to acquire a new slice.
      this.assert(this.sliceByteLength === 0);

      // Rewind the current slice to the start of the ring buffer.
      this.sliceHeadPosition = 0;
      this.sliceTailPosition = 0;
      this.sliceIsAtEndOfBuffer = false;

      // Increment the epoch number. Note that the epoch number itself wraps
      // around on overflow, this is intentional.
      this.epoch =
        (this.epoch + SliceHeader.EpochBufWrapDelta) & SliceHeader.EpochMask;
      this.wrapCounter++;
    }

    const headerI32Offset = this.getHeaderI32Offset(this.sliceHeadPosition);
    let header = this.i32[headerI32Offset];

    let spinCountRemaining: number = this.spinCount;
    let futexWaitTime: number = this.spinYieldCpuTime;

    while ((header & SliceHeader.EpochMask) !== this.epoch) {
      // Sleep nor spin when acquiring in non-blocking mode.
      if (!wait) {
        return SliceHeader.None;
      }

      if (spinCountRemaining === 0) {
        // We're going to put the thread to sleep.
        // Use compare-and-swap to set the kHasWaiters flag.
        const expect = header;
        const target = header | SliceHeader.HasWaitersFlag;
        header = Atomics.compareExchange(
          this.i32,
          headerI32Offset,
          expect,
          target
        );
        if (expect !== header) {
          // The buffer slot that holds the header has been modified after we
          // last receive it; compareExchange did not set the flag, but `header`
          // is now up-to-date again.
          continue;
        }
        header = target;
        futexWaitTime = Infinity;
        this.waitCounter++;
      } else {
        // We still have spins left.
        spinCountRemaining--;
        this.spinCounter++;
      }

      // If we're spinning and CPU yielding is enabled, we'll call futexWait
      // just as as if we were going to sleep, but with some very small time-out
      // value. If yielding is off, just refresh `header` from the ring buffer.
      if (
        futexWaitTime <= 0 ||
        Atomics.wait(this.i32, headerI32Offset, header, futexWaitTime) !==
          "timed-out"
      ) {
        // If futexWait returned "ok" or "not-equal", the value in the buffer
        // is different from our local copy, so refresh it.
        header = Atomics.load(this.i32, headerI32Offset);
      }
    }

    const byteLength = header & SliceHeader.ByteLengthMask;
    this.assert(byteLength <= this.bufferByteLength - this.sliceHeadPosition);

    this.sliceHeadPosition += byteLength;
    this.sliceByteLength += byteLength;
    this.sliceIsAtEndOfBuffer =
      this.sliceHeadPosition === this.bufferByteLength;
    this.acquireCounter++;

    return header;
  }

  protected releaseSlice(byteLength: number, flags: number = 0): void {
    this.assert(byteLength >= MsgRingAccess.kHeaderByteLength);
    this.assert(byteLength <= this.sliceByteLength);

    const tailEpoch = this.epoch + SliceHeader.EpochTransferDelta;
    const newHeader = byteLength | flags | tailEpoch;

    const headerI32Offset = this.getHeaderI32Offset(this.sliceTailPosition);
    const oldHeader = Atomics.exchange(this.i32, headerI32Offset, newHeader);

    if (oldHeader & SliceHeader.HasWaitersFlag) {
      Atomics.wake(this.i32, headerI32Offset, 1);
      this.wakeCounter++;
    }

    this.sliceTailPosition += byteLength;
    this.sliceByteLength -= byteLength;
  }

  // Returns the byte offset of the header from the slice position, adjusted for
  // the fill direction of the buffer.
  protected getHeaderI32Offset(position: number): number {
    const headerByteOffset: number =
      this.fillDirectionBaseAdjustment *
        (this.bufferByteLength - MsgRingAccess.kHeaderByteLength) +
      this.fillDirectionOffsetAdjustment * position;
    return headerByteOffset / this.i32.BYTES_PER_ELEMENT;
  }

  // Creates a Message object, given the byte length of the encapsulating slice.
  protected getMessage(sliceByteLength: number): Message {
    // Compute the length of the message itself. Note that when writing a
    // message, it's length is always rounded up to match the alignment.
    const messageByteLength = sliceByteLength - MsgRingSender.kHeaderByteLength;

    // Compute the fill-direction adjusted offset of the message payload.
    const messageByteOffset =
      this.fillDirectionBaseAdjustment *
        (this.bufferByteLength - messageByteLength) +
      this.fillDirectionOffsetAdjustment *
        (this.sliceTailPosition + MsgRingAccess.kHeaderByteLength);

    return {
      byteOffset: messageByteOffset,
      byteLength: messageByteLength
    };
  }
}

export class MsgRingSender extends MsgRingAccess {
  static readonly kEpochBase = SliceHeader.EpochBaseSender;
  static readonly kNotWriting = -1;

  // Byte length of the allocation made for the message, which also includes
  // room for the slice header and alignment padding.
  private allocationByteLength: number = MsgRingSender.kNotWriting;

  // Note: byteLength will be rounded up to alignment.
  beginSend(messageByteLength: number): Message {
    if (this.allocationByteLength !== MsgRingSender.kNotWriting) {
      throw new Error("Already writing.");
    }
    this.allocate(messageByteLength);
    return this.getMessage(this.allocationByteLength);
  }

  // Note: byteLength will be rounded up to alignment.
  // Noto: already-written data is discarded when buffer wraps.
  // TODO: copy bytes when allocation wraps.
  resizeSend(messageByteLength: number): Message {
    if (this.allocationByteLength === MsgRingSender.kNotWriting) {
      throw new Error("Not writing.");
    }
    this.allocate(messageByteLength);
    return this.getMessage(this.allocationByteLength);
  }

  endSend(submit = true): void {
    if (this.allocationByteLength === MsgRingSender.kNotWriting) {
      throw new Error("Not writing.");
    }
    if (submit) {
      // Release a slice that contains the header plus message.
      this.releaseSlice(this.allocationByteLength, SliceHeader.HasMessageFlag);
      this.messageCounter++;
    }
    this.allocationByteLength = MsgRingSender.kNotWriting;
  }

  send(data: ArrayBufferView): void {
    // Convert `data` to an Uint8Array view if necessary.
    const u8data: Uint8Array =
      data instanceof Uint8Array
        ? data
        : new Uint8Array(data.buffer, data.byteOffset, data.byteLength);
    // Allocate space.
    const target = this.beginSend(data.byteLength);
    // Copy data.
    this.u8.set(u8data, target.byteOffset);
    // Close the send.
    this.endSend();
  }

  private allocate(messageByteLength: number): void {
    // Check whether messageByteLength is in range, and if so, store it.
    if (messageByteLength > this.maxMessageByteLength)
      throw new RangeError("Message too big.");
    if (messageByteLength < 0)
      throw new RangeError("Message must have positive byte length.");

    // Compute the total required length, including header and padding,
    this.allocationByteLength =
      MsgRingSender.kHeaderByteLength + this.align(messageByteLength);

    while (this.sliceByteLength < this.allocationByteLength) {
      // An allocation can't wrap around the end of the ring buffer.
      if (this.sliceIsAtEndOfBuffer && this.sliceByteLength > 0) {
        // Discard the allocation we've made so far. The allocation process will
        // restart at the beginning of the ring buffer.
        this.releaseSlice(this.sliceByteLength);
      }
      // Consume the next slice to get closer to the target allocation length.
      this.acquireSlice();
    }
  }

  private align(byteCount: number): number {
    const alignmentMask = MsgRingAccess.kAlignmentByteLength - 1;
    return (byteCount + alignmentMask) & ~alignmentMask;
  }
}

export class MsgRingReceiver extends MsgRingAccess {
  static readonly kEpochBase: number = SliceHeader.EpochBaseReceiver;

  private isReceiving: boolean = false;

  beginReceive(): Message {
    if (this.isReceiving) throw new Error("Already receiving.");
    this.isReceiving = true;

    while (!(this.acquireSlice() & SliceHeader.HasMessageFlag)) {
      this.releaseSlice(this.sliceByteLength);
    }
    return this.getMessage(this.sliceByteLength);
  }

  endReceive(release = true): void {
    if (!this.isReceiving) throw new Error("Not receiving.");
    this.isReceiving = false;

    if (release) {
      this.releaseSlice(this.sliceByteLength);
      this.messageCounter++;
    }
  }

  receive<T extends TypedArray>(ctor: TypedArrayConstructor<T>): T {
    const message = this.beginReceive();
    let copy: T | undefined;
    try {
      // TODO: This is slow (>2x slowdown); find a more efficient solution.
      let view: T = new ctor(
        this.buffer,
        message.byteOffset,
        message.byteLength / ctor.BYTES_PER_ELEMENT
      );
      copy = new ctor(view);
      return copy;
    } finally {
      // Only release the slice if creating the view succeeded.
      this.endReceive(copy !== undefined);
    }
  }
}
