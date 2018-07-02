import { assert } from "./assert";

const bufTable: { [id: number]: Buf } = Object.create(null);
let idCounter: Uint32Array;
let port: MessagePort;

export class Buf {
  private constructor(
    readonly id: number,
    readonly ab: SharedArrayBuffer,
    readonly i32: Int32Array
  ) {}

  static async get(id: number): Promise<Buf> {
    while (!(id in bufTable)) {
      // Wait for the other side to transfer it over.
      await null;
    }
    return bufTable[id];
  }

  static tryGet(id: number): Buf | null {
    // Returns null if we're still waiting for the buffer to transferred.
    return bufTable[id] || null;
  }

  static import(ab: SharedArrayBuffer): Buf {
    // TODO: find a way to re-use buffer IDs. With the current scheme the
    // program will crash after 2^31 allocations.
    const id = 1 + Atomics.add(idCounter, 0, 1);
    // The buffer ID is guaranteed to be greater than zero, and it
    // must be small enough to fit in an Int32Array slot.
    assert(id > 0 && id === ~~id);
    const i32 = new Int32Array(ab);
    const buf = new Buf(id, ab, i32);
    bufTable[id] = buf;
    port.postMessage({ id: buf.id, ab: buf.ab }); // Share with other thread.
    console.log("Sent buffer", buf.id);
    return buf;
  }

  static alloc(byteLength: number): Buf {
    const ab = new SharedArrayBuffer(byteLength);
    return this.import(ab);
  }

  static free(buf: Buf): void {
    if (buf.id === 0) {
      throw new Error("Buffer already freed");
    }
    // Remove from buffer table.
    // TODO: maintain a pool.
    delete bufTable[buf.id];
    // Don't delete properties or otherwise change object shape,
    // V8 get's moody when you do that.
    const obj = buf as any; // "Cast away" property readonly-ness.
    obj.id = 0;
    obj.ab = null;
    obj.i32 = null;
  }

  static receive(e: MessageEvent) {
    const { id, ab } = e.data;
    console.log("Received buffer", id);
    assert(!(id in bufTable), "Duplicate buffer ID");
    const i32 = new Int32Array(ab);
    bufTable[id] = new Buf(id, ab, i32);
  }

  static setup(p: MessagePort, idBuf: SharedArrayBuffer) {
    idCounter = new Uint32Array(idBuf);
    port = p;
    port.onmessage = Buf.receive;
    port.start();
  }

  static debugInfo() {
    return Object.keys(bufTable).length;
  }
}
