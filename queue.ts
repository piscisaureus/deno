import { assert } from "./assert";
import { Buf } from "./buf";

export const debugInfo = {
  spinCount: 0,
  waitCount: 0
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
  // including header slot(s). Size zero indicates that the buffer wraps here.
  kLengthMask = 0x00ffffff,
  kLengthBufWrap = 0x00000000,
  // Every time a slice changes hands between reader and writer, we add 1 to the
  // 2-bit epoch number, which wraps on overflow.
  kEpochBaseWriter = 0x00000000,
  kEpochBaseReader = 0x01000000,
  kEpochTransferDelta = 0x01000000,
  kEpochBufWrapDelta = 0x02000000,
  kEpochMask = 0x01000000 * 15,
  // Flag that indicates that a readable chunk does not contain useful data,
  // e.g. due to an abandoned write or insufficient space at the end of the
  // buffer.
  kIsWasteFlag = 0x40000000,
  // Flag that indicates that there are waiter(s).
  kHasWaitersFlag = 0x80000000,
  // Pseudo-header returned by poll to indicate that no slice is available.
  kNotAvailable = -1
}

console.log(HeaderBits.kEpochMask.toString(16));

export const YIELD: unique symbol = Symbol("YIELD");
export type YIELD = typeof YIELD;

// Todo: rename to Slice.
export interface Message {
  i32: Int32Array;
  pos: number;
  length: number;
}

interface SliceHeader {
  pos: number;
  length: number;
  isWaste: boolean;
  isEnd: boolean;
}

// Default maxSpinCount value for QueueReader.
// Optimal value TBD.
const READER_MAX_SPIN_COUNT = 1000; //100000;

let ctr = 0;
class QueueHead {
  static kEpochBase: number;

  "constructor": typeof QueueHead;
  // Helper buffer for the yieldThread() function.
  private static THREAD_YIELD_HELPER_BUF = new Int32Array(
    new SharedArrayBuffer(Int32Array.BYTES_PER_ELEMENT)
  );

  protected kEpochBase: number;

  private maxSpinCount: number = READER_MAX_SPIN_COUNT;

  private acqPos: number = 0;
  private acqEpoch: number;

  private relPos: number = 0;
  private relEpoch: number;

  constructor(protected buf: Buf) {
    const Self = this.constructor;
    this.acqEpoch = Self.kEpochBase;
    this.relEpoch = Self.kEpochBase + HeaderBits.kEpochTransferDelta;
  }

  getSliceHeader(
    pos: number = this.acqPos,
    epoch: number = this.acqEpoch,
    spinCount: number = this.maxSpinCount
  ): SliceHeader {
    let header: number = this.buf.i32[pos];
    wait: for (;;) {
      let headerEpoch = header & HeaderBits.kEpochMask;
      if (headerEpoch === epoch) {
        break wait;
      }

      while (!(header & HeaderBits.kHasWaitersFlag) && spinCount > 0) {
        header = Atomics.load(this.buf.i32, pos);
        headerEpoch = header & HeaderBits.kEpochMask;
        if (headerEpoch === epoch) {
          break wait;
        }
        Atomics.wait(QueueHead.THREAD_YIELD_HELPER_BUF, 0, 0, 1);
        spinCount--;
        debugInfo.spinCount++;
      }

      for (;;) {
        let expect, target;

        do {
          expect = header;
          target = header | HeaderBits.kHasWaitersFlag;

          header = Atomics.compareExchange(this.buf.i32, pos, expect, target);
          headerEpoch = header & HeaderBits.kEpochMask;
          if (headerEpoch === epoch) {
            break wait;
          }
        } while (header !== expect);

        Atomics.wait(this.buf.i32, pos, target);
        debugInfo.waitCount++;

        header = this.buf.i32[pos];
        headerEpoch = header & HeaderBits.kEpochMask;
        if (headerEpoch === epoch) {
          break wait;
        }
      }
    }

    let length = header & HeaderBits.kLengthMask;
    let endPos = pos + length;
    assert(endPos <= this.buf.i32.length);
    let isWaste = Boolean(header & HeaderBits.kIsWasteFlag);
    let isEnd = endPos === this.buf.i32.length;

    if (isEnd) {
      this.acqPos = 0;
      this.acqEpoch =
        (this.acqEpoch + HeaderBits.kEpochBufWrapDelta) & HeaderBits.kEpochMask;
    } else {
      this.acqPos = endPos;
    }

    return { pos, length, isWaste, isEnd };
  }

  putSliceHeader(
    length: number,
    isWaste: boolean,
    pos: number = this.relPos,
    epoch: number = this.relEpoch
  ) {
    assert((length & ~HeaderBits.kLengthMask) === 0);
    assert(pos + length <= this.buf.i32.length);
    assert(length >= HEADER_LENGTH);
    assert((epoch & ~HeaderBits.kEpochMask) === 0);
    const flags = Number(isWaste) * HeaderBits.kIsWasteFlag;
    const header = length | flags | epoch;
    const prev = Atomics.exchange(this.buf.i32, pos, header);
    if (prev & HeaderBits.kHasWaitersFlag) {
      Atomics.wake(this.buf.i32, pos, 2);
    }

    let endPos = pos + length;
    if (endPos === this.buf.i32.length) {
      this.relPos = 0;
      this.relEpoch =
        (this.relEpoch + HeaderBits.kEpochBufWrapDelta) & HeaderBits.kEpochMask;
    } else {
      this.relPos = endPos;
    }
  }
}

export class QueueWriter extends QueueHead {
  static kEpochBase = HeaderBits.kEpochBaseWriter;

  private reservation: SliceHeader | null = null;

  constructor(buf: Buf) {
    super(buf);
    //this.buf.i32[0] = this.buf.i32.length;
  }

  send(message: Int32Array) {
    // Length including header (in slots).
    const requiredLength = HEADER_LENGTH + message.length;

    acquire: for (;;) {
      if (this.reservation === null) {
        this.reservation = this.getSliceHeader();
      }
      while (this.reservation.length < requiredLength) {
        if (this.reservation.isEnd) {
          // Can't wrap around the end of the ring buffer. Discard what we got
          // so far and start over at the beginning of the buffer.
          this.putSliceHeader(this.reservation.length, true);
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
    if (this.reservation.length === requiredLength) {
      this.reservation = null;
    } else {
      this.reservation.pos += requiredLength;
      this.reservation.length -= requiredLength;
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
    this.putSliceHeader(requiredLength, false);
  }
}

export class QueueReader extends QueueHead {
  static kEpochBase: number = HeaderBits.kEpochBaseReader;

  // The recv() function actually shouldn't be an async function,
  // but in a browser environment buffers can only be transferred
  // between threads (workers) with postMessage().
  // We won't receive those messages unless we yield to the event
  // loop every now and then.
  recv(): Message {
    for (;;) {
      let sliceHeader = this.getSliceHeader();
      if (sliceHeader.isWaste) {
        this.putSliceHeader(sliceHeader.length, false);
      } else {
        // TODO: beginRecv()/endRecv()
        this.putSliceHeader(sliceHeader.length, false);
        return {
          i32: this.buf.i32,
          pos: sliceHeader.pos,
          length: sliceHeader.length
        };
      }
    }
  }
}
