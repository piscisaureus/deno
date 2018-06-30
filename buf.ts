
export type BufTransferList = Array<{ id: number, ab: SharedArrayBuffer }>;

const bufTable: { [id: number]: Buf } = Object.create(null);
let idCounter = 0;

export class Buf {
  private constructor(
    readonly id: number,
    readonly ab: SharedArrayBuffer,
    readonly i32: Int32Array
  ) {}

  static get(id: number): Buf | undefined {
    return bufTable[id];
  }

  static alloc(byteLength: number): Buf {
    // TODO: find a way to re-use buffer IDs. With the current scheme the
    // program will crash after 2^31 allocations.
    const id = ++idCounter;
    // The buffer ID is guaranteed to be greater than zero, and it
    // must be small enough to fit in an Int32Array slot.
    assert(id > 0 && id === ~~id);
    const ab = new SharedArrayBuffer(byteLength);
    const i32 = new Int32Array(ab);
    const buf = new Buf(id, ab, i32);
    bufTable[id] = buf;
    return buf;
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

  static receive(buffers: BufTransferList) {
    for (const {id, ab} of buffers) {
      assert(!bufTable.hasOwnProperty(id), "Duplicate buffer ID");
      const i32 = new Int32Array(ab);
      bufTable[id] = new Buf(id, ab, i32);
    }
  }
}
