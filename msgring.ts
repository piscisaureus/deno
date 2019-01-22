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

export interface Slice {
  byteOffset: number;
  byteLength: number;
}

export interface MsgRingCounters {
  role: string;
  message: number;
  acquire: number;
  release: number;
  spin: number;
  wait: number;
  wake: number;
  wrap: number;
}

export const enum FillDirection {
  TopDown,
  BottomUp
}

type OptionsObject<T> = { -readonly [P in keyof T]?: T[P] };
export type MsgRingConfig = OptionsObject<MsgRingDefaultConfig>;

const enum FrameAllocation {
  // Placeholder value indicating the absence of an allocation.
  None = 0,
  // Alignment (in bytes) of frame offset and frame length.
  Alignment = 8,
  // Length of frame header. Note: only 4 bytes are currently used.
  HeaderByteLength = 8
}

// prettier-ignore
const enum FrameHeader {
  // Do not use the highest bit. On 64-bit systems, 32-bit signed ints are very
  // efficient in v8, but numbers greater than 2**31-1 are heap allocated.

  // Placeholder value indicating the absence of a header.
  None               = 0x00000000,
  // Low 24 bits are reserved for the length of the frame (including header).
  ByteLengthMask     = 0x00ffffff,
  // The `epoch` serves as a filter for which frames are ready to be acquired.
  EpochMask          = 0x03000000,
  // Initial epoch values for respectively the sender and the receiver.
  EpochInitSender    = 0x00000000,
  EpochInitReceiver  = 0x01000000,
  // Every time a frame changes hands between receiver and sender, we add 1 to
  // the 2-bit epoch number; when the buffer wraps, add 2.
  EpochIncrementPass = 0x01000000,
  EpochIncrementWrap = 0x02000000,
  // Flag that indicates to receiver that a frame contains a message. If it
  // doesn't, that's due to insufficient space at the end of the buffer.
  HasMessageFlag     = 0x04000000,
  // Flag that indicates that there are waiter(s) that expect to be notified.
  HasWaitersFlag     = 0x08000000,
}

abstract class MsgRingDefaultConfig {
  // Whether buffers are filled upwards or downwards.
  readonly fillDirection: FillDirection = FillDirection.BottomUp;

  // The maximum number of times acquireFrame() will spin before sleeping.
  readonly spinCount: number = 100;

  // When spinning, for how long the thread yields the CPU on each cycle, in
  // milliseconds. Yielding happens by calling Atomics.wait() with a time-out.
  // Set to zero to never yield the CPU.
  readonly spinYieldCpuTime: number = 0;
}

abstract class MsgRingCommon extends MsgRingDefaultConfig {
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

  // A frame's epoch identifies which role (receiver or sender) released a
  // frame, and whether the buffer has since wrapped around. This epoch field
  // tracks which epoch acquireFrame() will currently acquire frames from.
  // Initialization is role-dependent, so it's done by our subclasses.
  protected epoch!: number;

  // The head and tail position indicate the range of bytes (frame) that is
  // locked by this receiver/sender. The value indicates the offset in bytes
  // from the start of the ring buffer, ***NOT*** adjusted for fill direction of
  // the buffer. Hence the first frame always starts at position 0.
  protected frameHeadPosition: number = 0;
  protected frameTailPosition: number = 0;

  // The frame byte length and whether it's at the end of the buffer can be
  // computed from the head and tail position. However we store them because
  // they are used often.
  protected frameByteLength: number = 0;
  protected frameIsAtEndOfBuffer: boolean = false;

  // Counters for debugging.
  protected messageCounter: number = 0;
  private acquireCounter: number = 0;
  private releaseCounter: number = 0;
  private wrapCounter: number = 0;
  private waitCounter: number = 0;
  private wakeCounter: number = 0;
  private spinCounter: number = 0;

  // `buffer` must be initialized with zeroes.
  constructor(readonly buffer: SharedArrayBuffer, options: MsgRingConfig = {}) {
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
      (Math.min(FrameHeader.ByteLengthMask, this.bufferByteLength) -
        FrameAllocation.HeaderByteLength) &
      ~(FrameAllocation.Alignment - 1);

    // Create various views on the SharedArrayBuffer.
    this.u8 = new Uint8Array(buffer);
    this.i32 = new Int32Array(buffer);
    this.u32 = new Uint32Array(buffer);

    // Initialize the frame structure inside the buffer.
    // We expect the buffer to be initialized with zeroes. If that's the
    // case, define a frame that spans the entire buffer and place it's header
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

  get counters(): MsgRingCounters {
    return {
      role: this.constructor.name,
      message: this.messageCounter,
      acquire: this.acquireCounter,
      release: this.releaseCounter,
      wrap: this.wrapCounter,
      wait: this.waitCounter,
      wake: this.wakeCounter,
      spin: this.spinCounter
    };
  }

  protected assert(condition: boolean): void {
    if (!condition) {
      throw new Error(`${this.constructor.name}: assertion failed.`);
    }
  }

  protected acquireFrame(wait = true): number {
    // Wrap around if the current head position is at the end of the buffer.
    if (this.frameIsAtEndOfBuffer) {
      // A frame can't wrap around the end of the buffer; if the current frame
      // is at the end of the buffer, the caller should release the remaining
      // bytes before attempting to acquire a new frame.
      this.assert(this.frameByteLength === 0);

      // Increment the epoch number. Note that the epoch number itself wraps
      // around on overflow, this is intentional.
      this.epoch =
        (this.epoch + FrameHeader.EpochIncrementWrap) & FrameHeader.EpochMask;

      // Rewind the current frame to the start of the ring buffer.
      this.frameHeadPosition = 0;
      this.frameTailPosition = 0;
      this.frameIsAtEndOfBuffer = false;
      this.wrapCounter++;
    }

    const headerI32Offset = this.getHeaderI32Offset(this.frameHeadPosition);
    let header = this.i32[headerI32Offset];

    let spinCountRemaining: number = this.spinCount;
    let futexWaitTime: number = this.spinYieldCpuTime;

    while ((header & FrameHeader.EpochMask) !== this.epoch) {
      // Sleep nor spin when acquiring in non-blocking mode.
      if (!wait) {
        return FrameHeader.None;
      }

      if (spinCountRemaining === 0) {
        // We're going to put the thread to sleep.
        // Use compare-and-swap to set the kHasWaiters flag.
        const expect = header;
        const target = header | FrameHeader.HasWaitersFlag;
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

    const byteLength = header & FrameHeader.ByteLengthMask;
    this.assert(byteLength <= this.bufferByteLength - this.frameHeadPosition);

    this.frameHeadPosition += byteLength;
    this.frameByteLength += byteLength;
    this.frameIsAtEndOfBuffer =
      this.frameHeadPosition === this.bufferByteLength;
    this.acquireCounter++;

    return header;
  }

  protected releaseFrame(byteLength: number, flags: number = 0): void {
    this.assert(byteLength >= FrameAllocation.HeaderByteLength);
    this.assert(byteLength <= this.frameByteLength);

    const tailEpoch = this.epoch + FrameHeader.EpochIncrementPass;
    const newHeader = byteLength | flags | tailEpoch;

    const headerI32Offset = this.getHeaderI32Offset(this.frameTailPosition);
    const oldHeader = Atomics.exchange(this.i32, headerI32Offset, newHeader);

    if (oldHeader & FrameHeader.HasWaitersFlag) {
      Atomics.wake(this.i32, headerI32Offset, 1);
      this.wakeCounter++;
    }

    this.frameTailPosition += byteLength;
    this.frameByteLength -= byteLength;
  }

  // Returns the byte offset of the header from the frame position, adjusted for
  // the fill direction of the buffer.
  protected getHeaderI32Offset(position: number): number {
    const headerByteOffset: number =
      this.fillDirectionBaseAdjustment *
        (this.bufferByteLength - FrameAllocation.HeaderByteLength) +
      this.fillDirectionOffsetAdjustment * position;
    return headerByteOffset / this.i32.BYTES_PER_ELEMENT;
  }

  // Creates a Slice object, given the byte length of the encapsulating frame.
  protected getMessageSlice(frameByteLength: number): Slice {
    // Compute the length of the message itself. Note that when writing a
    // message, it's length is always rounded up to match the alignment.
    const messageByteLength =
      frameByteLength - FrameAllocation.HeaderByteLength;

    // Compute the fill-direction adjusted offset of the message payload.
    const messageByteOffset =
      this.fillDirectionBaseAdjustment *
        (this.bufferByteLength - messageByteLength) +
      this.fillDirectionOffsetAdjustment *
        (this.frameTailPosition + FrameAllocation.HeaderByteLength);

    return {
      byteOffset: messageByteOffset,
      byteLength: messageByteLength
    };
  }
}

export class MsgRingSender extends MsgRingCommon {
  protected epoch: number = FrameHeader.EpochInitSender;

  // Number of bytes allocated by beginSend()/resizeSend(). It includes space
  // for the frame header and padding for alignment
  private allocationByteLength: number = FrameAllocation.None;

  // Note: byteLength will be rounded up to alignment.
  beginSend(messageByteLength: number): Slice {
    if (this.allocationByteLength !== FrameAllocation.None) {
      throw new Error("Already writing.");
    }
    this.allocate(messageByteLength);
    return this.getMessageSlice(this.allocationByteLength);
  }

  // Note: byteLength will be rounded up to alignment.
  // Noto: already-written data is discarded when buffer wraps.
  // TODO: copy bytes when allocation wraps.
  resizeSend(messageByteLength: number): Slice {
    if (this.allocationByteLength === FrameAllocation.None) {
      throw new Error("Not writing.");
    }
    this.allocate(messageByteLength);
    return this.getMessageSlice(this.allocationByteLength);
  }

  endSend(submit = true): void {
    if (this.allocationByteLength === FrameAllocation.None) {
      throw new Error("Not writing.");
    }
    if (submit) {
      // Release a frame that contains the header plus message.
      this.releaseFrame(this.allocationByteLength, FrameHeader.HasMessageFlag);
      this.messageCounter++;
    }
    this.allocationByteLength = FrameAllocation.None;
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
      throw new RangeError("Slice too big.");
    if (messageByteLength < 0)
      throw new RangeError("Slice must have positive byte length.");

    // Compute the total required length, including header and padding,
    this.allocationByteLength =
      FrameAllocation.HeaderByteLength + this.align(messageByteLength);

    while (this.frameByteLength < this.allocationByteLength) {
      // An allocation can't wrap around the end of the ring buffer.
      if (this.frameIsAtEndOfBuffer && this.frameByteLength > 0) {
        // Discard the allocation we've made so far. The allocation process will
        // restart at the beginning of the ring buffer.
        this.releaseFrame(this.frameByteLength);
      }
      // Consume the next frame to get closer to the target allocation length.
      this.acquireFrame();
    }
  }

  private align(byteCount: number): number {
    const alignmentMask = FrameAllocation.Alignment - 1;
    return (byteCount + alignmentMask) & ~alignmentMask;
  }
}

export class MsgRingReceiver extends MsgRingCommon {
  protected epoch: number = FrameHeader.EpochInitReceiver;
  private isReceiving: boolean = false;

  beginReceive(): Slice {
    if (this.isReceiving) throw new Error("Already receiving.");
    this.isReceiving = true;

    while (!(this.acquireFrame() & FrameHeader.HasMessageFlag)) {
      this.releaseFrame(this.frameByteLength);
    }
    return this.getMessageSlice(this.frameByteLength);
  }

  endReceive(release = true): void {
    if (!this.isReceiving) throw new Error("Not receiving.");
    this.isReceiving = false;

    if (release) {
      this.releaseFrame(this.frameByteLength);
      this.messageCounter++;
    }
  }

  receive<T extends TypedArray>(ctor: TypedArrayConstructor<T>): T {
    const messageSlice = this.beginReceive();
    let copy: T | undefined;
    try {
      // TODO: This is slow (>2x slowdown); find a more efficient solution.
      let view: T = new ctor(
        this.buffer,
        messageSlice.byteOffset,
        messageSlice.byteLength / ctor.BYTES_PER_ELEMENT
      );
      copy = new ctor(view);
      return copy;
    } finally {
      // Only release the frame if creating the view succeeded.
      this.endReceive(copy !== undefined);
    }
  }
}
