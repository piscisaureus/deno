import { assert } from "./assert";
import { Buf } from "./buf";

export const debugInfo = {
  spinCountRemaining: { reader: 0, writer: 0 },
  waitCount: { reader: 0, writer: 0 }
};

// In the queue buffer, every message is prefixed by a one-slot header.
// * Initially the header slot contains zero, meaning that there is no message
//   here (yet).
// * Greater than zero means that there is a message at this position.
//   The value itself is the total length of the message *and* the header,
//   in slots.
//   (I.O.W., the length of the message itself is `header-1` slots.)
// * The *reader* can change the value to `HDR_READER_ASLEEP` (-1) to let the
//   writer know it is asleep and needs to be woken.
// * The *writer* can change the value to `HDR_NEXT_BUFFER` (-2) to let the
//   reader know the buffer was full and it has moved on to the next one.
//   (The next buffer id is placed in the adjacent slot).
const HDR_INITIAL = 0;
const HDR_READER_ASLEEP = -1;
const HDR_NEXT_BUFFER = -2;

// The size of the header is 1 slot.
const HEADER_LENGTH = 2;
// The size of the NEXT_BUFFER marker is 2 slots (including it's header).
const NEXT_BUFFER_MARKER_LENGTH = HEADER_LENGTH + 1;
// The size of a queue buffer (in slots).
const QUEUE_BUFFER_LENGTH = 0x1000000;

const kMarkerSlot = 0;
const kLengthSlot = 1;

enum HeaderBits {
  // Low 24 bits are reserved for the slice length (measured in slots),
  // including header slot(s).
  kLengthMask = 0x00ffffff,
  // Every time a slice changes hands between reader and writer, we add 1 to the
  // 2-bit epoch number, which wraps on overflow.
  kEpochBaseWriter = 0x00000000,
  kEpochBaseReader = 0x01000000,
  kEpochTransferDelta = 0x01000000,
  kEpochBufWrapDelta = 0x02000000,
  kEpochMask = 0x03000000,
  // Flag that indicates that a readable chunk does not contain useful data,
  // e.g. due to an abandoned write or insufficient space at the end of the
  // buffer.
  kIsWasteFlag = 0x04000000,
  // Flag that indicates that there are waiter(s).
  kHasWaitersFlag = 0x08000000,
  // Pseudo-header returned by poll to indicate that no slice is available.
  kNotAvailable = -1
}

export const YIELD: unique symbol = Symbol("YIELD");
export type YIELD = typeof YIELD;

// Todo: rename to Slice.
export interface Message {
  i32: Int32Array;
  pos: number;
  length: number;
}

interface SliceHeaderInfo {
  length: number;
  isWaste?: boolean;
}

interface SliceInfo extends SliceHeaderInfo {
  pos: number;
  isEnd: boolean;
  isWaste: boolean;
}

// Default kSpinCount value for QueueReader.
// Optimal value TBD.
const READER_MAX_SPIN_COUNT = 100; //0; //1000; //100000;

let ctr = 0;
abstract class QueueHead {
  // These constants define spinning behaviour.
  static readonly kSpinCount: number = READER_MAX_SPIN_COUNT;
  static readonly kSpinYieldCpu: boolean = false;

  // Hack to get TypeScript to get type info for 'this.constructor' right.
  readonly "constructor": typeof QueueHead;

  // Subclasses have to provide values for these.
  static readonly kEpochBase: number;
  static readonly kKind: "reader" | "writer";

  private acqEpoch: number;
  private relEpoch: number;

  private acqPos: number = 0;
  private relPos: number = 0;

  constructor(protected buf: Buf) {
    const Self = this.constructor;
    this.acqEpoch = Self.kEpochBase;
    this.relEpoch = Self.kEpochBase + HeaderBits.kEpochTransferDelta;
  }

  private wrapEpoch(epoch: number) {
    return (epoch + HeaderBits.kEpochBufWrapDelta) & HeaderBits.kEpochMask;
  }

  getSliceHeader(): SliceInfo {
    const pos: number = this.acqPos;
    let header: number = this.buf.i32[pos];
    let spinCountRemaining: number = QueueHead.kSpinCount;

    while ((header & HeaderBits.kEpochMask) !== this.acqEpoch) {
      let futexWaitTime;

      if (spinCountRemaining === 0) {
        // We're going to put the thread to sleep.
        // Use compare-and-swap to set the kHasWaiters flag.
        const expect = header;
        const target = header | HeaderBits.kHasWaitersFlag;
        header = Atomics.compareExchange(this.buf.i32, pos, expect, target);
        if (expect !== header) {
          // The buffer slot that holds the header has been modified after we
          // last read it; compareExchange did not set the flag, but `header`
          // is now up-to-date again.
          continue;
        }
        header = target;
        futexWaitTime = Infinity;
      } else {
        // We're spinning.
        --spinCountRemaining;
        futexWaitTime = QueueHead.kSpinYieldCpu
          ? 1 // Use futexWait to yield the CPU for 1ms.
          : null; // Skip futexWait and go read the buffer again.
      }

      if (
        futexWaitTime === null ||
        Atomics.wait(this.buf.i32, pos, header, futexWaitTime) !== "timed-out"
      ) {
        // If futexWait returned "ok" or "not-equal", the value in the buffer
        // has changed, so refresh our copy.
        header = Atomics.load(this.buf.i32, pos);
      }
    }

    const length = header & HeaderBits.kLengthMask;
    const isWaste = Boolean(header & HeaderBits.kIsWasteFlag);

    const endPos = pos + length;
    assert(endPos <= this.buf.i32.length);
    const isEnd = endPos === this.buf.i32.length;

    if (!isEnd) {
      this.acqPos = endPos;
    } else {
      this.acqEpoch = this.wrapEpoch(this.acqEpoch);
      this.acqPos = 0;
    }

    return { pos, length, isEnd, isWaste };
  }

  putSliceHeader({ length, isWaste = false }: SliceHeaderInfo): void {
    const pos: number = this.relPos;

    assert(length >= HEADER_LENGTH);
    assert((length & ~HeaderBits.kLengthMask) === 0);
    assert(pos + length <= this.buf.i32.length);

    const flags = Number(isWaste) * HeaderBits.kIsWasteFlag;
    const header = length | flags | this.relEpoch;
    const previous = Atomics.exchange(this.buf.i32, pos, header);

    if (previous & HeaderBits.kHasWaitersFlag) {
      Atomics.wake(this.buf.i32, pos, 2);
    }

    const endPos = pos + length;
    assert(endPos <= this.buf.i32.length);
    const isEnd = endPos === this.buf.i32.length;

    if (!isEnd) {
      this.relPos = endPos;
    } else {
      this.relEpoch = this.wrapEpoch(this.relEpoch);
      this.relPos = 0;
    }
  }
}

export class QueueWriter extends QueueHead {
  static readonly kEpochBase = HeaderBits.kEpochBaseWriter;
  static readonly kKind: "writer" = "writer";

  private reservation: SliceInfo | null = null;

  constructor(buf: Buf) {
    super(buf);
    //this.buf.i32[0] = this.buf.i32.length;
  }

  send(message: Int32Array) {
    // Length including header (in slots).
    const length = HEADER_LENGTH + message.length;

    acquire: for (;;) {
      if (this.reservation === null) {
        this.reservation = this.getSliceHeader();
      }
      while (this.reservation.length < length) {
        if (this.reservation.isEnd) {
          // Can't wrap around the end of the ring buffer. Discard what we got
          // so far and start over at the beginning of the buffer.
          this.putSliceHeader({ ...this.reservation, isWaste: true });
          this.reservation = null;
          continue acquire;
        }
        let h = this.getSliceHeader();
        this.reservation.length += h.length;
        this.reservation.isEnd = h.isEnd;
      }
      break;
    }

    let headerPos: number = this.reservation.pos;
    if (this.reservation.length === length) {
      this.reservation = null;
    } else {
      this.reservation.pos += length;
      this.reservation.length -= length;
    }

    const messagePos = headerPos + HEADER_LENGTH;
    assert(messagePos + message.length <= this.buf.i32.length);

    // Copy the message itself into the buffer.
    // Slow:
    // this.buf.i32.set(message, messagePos);
    for (let i = 0; i < message.length; i++) {
      this.buf.i32[messagePos + i] = message[i];
    }

    // Write header.
    this.putSliceHeader({ length });
  }
}

export class QueueReader extends QueueHead {
  static readonly kEpochBase: number = HeaderBits.kEpochBaseReader;
  static readonly kKind: "reader" = "reader";

  // The recv() function actually shouldn't be an async function,
  // but in a browser environment buffers can only be transferred
  // between threads (workers) with postMessage().
  // We won't receive those messages unless we yield to the event
  // loop every now and then.
  recv(): Message {
    for (;;) {
      let sliceHeader = this.getSliceHeader();
      if (sliceHeader.isWaste) {
        this.putSliceHeader(sliceHeader);
      } else {
        // TODO: beginRecv()/endRecv()
        this.putSliceHeader(sliceHeader);
        return {
          i32: this.buf.i32,
          pos: sliceHeader.pos,
          length: sliceHeader.length
        };
      }
    }
  }
}
