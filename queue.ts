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
const HEADER_LENGTH = 1;
// The size of the NEXT_BUFFER marker is 2 slots (including it's header).
const NEXT_BUFFER_MARKER_LENGTH = HEADER_LENGTH + 1;
// The size of a queue buffer (in slots).
const QUEUE_BUFFER_LENGTH = 0x1000000;

export const YIELD = Symbol("YIELD");

export interface Message {
  i32: Int32Array;
  pos: number;
  length: number;
}

// Default maxSpinCount value for QueueReader.
// Optimal value TBD.
const READER_MAX_SPIN_COUNT = 10000; //100000;

export class QueueWriter {
  private writerPos: number = 0; // Write position in the current buffer.

  constructor(private buf: Buf) {}

  send(message: Int32Array) {
    // Length including header (in slots).
    const length = HEADER_LENGTH + message.length;

    // See if there is enough space in the current buffer for this message.
    // Note that we keep two slots reserved, because we must be able to fit the
    // eventual 'go-to-the-next-buffer' marker after this message.
    const needed = length + NEXT_BUFFER_MARKER_LENGTH;
    const avail = this.buf.i32.length - this.writerPos;

    if (needed > avail) {
      // Allocate a new buffer. It should be zero-filled already.
      // TODO: should probably just reject messages that don't fit
      // in a buffer of default length.
      const byteLength =
        Math.max(QUEUE_BUFFER_LENGTH, needed) * Uint32Array.BYTES_PER_ELEMENT;
      const nextBuf = Buf.alloc(byteLength);
      // Write the go-to-next-buffer meta message.
      this.write(this.writerPos, HDR_NEXT_BUFFER, [nextBuf.id]);
      // Free the old buffer; the receiver should still have a reference to it.
      Buf.free(this.buf);
      // Switch over to the new buffer.
      this.buf = nextBuf;
      this.writerPos = 0;
    }

    // Write the message itself.
    this.write(this.writerPos, length, message);
    this.writerPos += length;
  }

  private write(
    pos: number,
    header: number,
    payload: Int32Array | number[]
  ): void {
    // The header is used for synchronization. Once we set it it,
    // the reader will think that it has received a message.
    // So we have to write the payload first, and the header last.
    const payloadPos = pos + HEADER_LENGTH;
    assert(payloadPos + payload.length <= this.buf.i32.length);

    // Copy the payload into the buffer.
    // Slow:
    // this.buf.i32.set(payload, payloadPos);
    for (let i = 0; i < payload.length; i++) {
      this.buf.i32[payloadPos + i] = payload[i];
    }

    // Atomically fetch the previous value from the header slot and
    // place the header value into it.
    const prev = Atomics.exchange(this.buf.i32, pos, header);
    assert(prev === HDR_INITIAL || prev === HDR_READER_ASLEEP);

    // If the previous value was HDR_READER_ASLEEP, the reader went to sleep
    // and needs to be woken.
    if (prev === HDR_READER_ASLEEP) {
      // Between js<->rust, the wake/wait mechanism will be different
      // because the rust thread will block on epoll() or similar.
      // For the prototype we use the "futex" support in Atomics.
      Atomics.wake(this.buf.i32, pos, 1);
    }
  }
}

export class QueueReader {
  private readerPos: number = 0; // We've processed messages up to this point.
  private maxSpinCount: number = READER_MAX_SPIN_COUNT;

  constructor(private buf: Buf) {}

  poll(will_sleep: boolean): Int32Array | Message | null | YIELD {
    let header: number;

    for (;;) {
      if (!will_sleep) {
        // If we're spinning, simply read the header from the slot where we
        // expect it to appear.
        header = this.buf.i32[this.readerPos];
        if (header === 0) header = Atomics.load(this.buf.i32, this.readerPos);
      } else {
        // If we're planning to sleep the thread when there are no message(s)
        // available, we'll place HDR_READER_ASLEEP in the slot where the next
        // next message header is supposed to appear. Thus the writer thread will
        // know that it has to wake as up.

        // Use compareExchange here to avoid a race condition; if the writer has
        // written a header in the meantime, we won't overwrite it.
        header = Atomics.compareExchange(
          this.buf.i32,
          this.readerPos,
          HDR_INITIAL,
          HDR_READER_ASLEEP
        );
      }

      // Check for any special header values.
      switch (header) {
        case HDR_INITIAL:
          // No message available.
          return null;

        case HDR_READER_ASLEEP:
          // Depending on whether the sleep/wake implementation allows for
          // spurious wake-ups, this may or may not be acceptable.
          // If spurious wake-ups are expected, we should go back to sleep.
          // But for now, be conservative and just throw.
          throw new Error("Queue state error");

        case HDR_NEXT_BUFFER:
          // Fetch the ID for the new buffer from the queue.
          const bufIdPos = this.readerPos + HEADER_LENGTH;
          assert(bufIdPos < this.buf.i32.length);
          const bufId = this.buf.i32[bufIdPos];

          // Check if the new buffer is available.
          const nextBuf = Buf.tryGet(bufId);
          if (nextBuf === null) {
            // We won't need this in Deno.
            // If poll() needs to move on to the next queue buffer, but this
            // thread hasn't received that buffer yet, tell the caller to yield
            // to the event loop so it can process incoming message events.
            return YIELD;
          }

          // Release the old queue buffer.
          Buf.free(this.buf);

          // Move over to the next one.
          this.buf = nextBuf;
          this.readerPos = 0;

          // Go back to start.
          continue;
      }

      // Since the header wasn't any special value, there is a message.
      const payloadPos = this.readerPos + HEADER_LENGTH;

      // Do some cursory checks, then update readerPos to point at the end of
      // this message. Note that the value of `header` at this point indicates
      // the total length of header and payload.
      const maxLength =
        this.buf.i32.length - this.readerPos - NEXT_BUFFER_MARKER_LENGTH;
      assert(header >= HEADER_LENGTH && header <= maxLength);
      this.readerPos += header;

      // Copy the message out of the buffer. TODO: don't do that.
      return { i32: this.buf.i32, pos: this.readerPos, length: header };
      // SLow:
      // return this.buf.i32.subarray(payloadPos, this.readerPos);
    }
  }

  // The recv() function actually shouldn't be an async function,
  // but in a browser environment buffers can only be transferred
  // between threads (workers) with postMessage().
  // We won't receive those messages unless we yield to the event
  // loop every now and then.
  recv(): Int32Array | Message | YIELD {
    let msg: Int32Array | Message | null | YIELD;
    let spinCountLeft = this.maxSpinCount;

    for (;;) {
      msg = this.poll(spinCountLeft === 0);

      // If we got a message or YIELD, break out of the loop.
      if (msg !== null) {
        return msg;
      }

      if (spinCountLeft > 0) {
        // We had spins left, so not sleeping now.
        // However this would be an opportune moment to do some other stuff, if there is anything to do.
        --spinCountLeft;
        debugInfo.spinCount++;
      } else {
        // Sleep the thread; the writer will wake us up.
        // See remarks in QueueWriter.write().
        //console.log("Sleeping")
        Atomics.wait(this.buf.i32, this.readerPos, HDR_READER_ASLEEP);
        debugInfo.waitCount++;
      }
    }
  }
}
