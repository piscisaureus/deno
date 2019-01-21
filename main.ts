import { Buf } from "./buf";
import { QueueReader, QueueWriter } from "./queue";

async function main(
  threadId: number,
  mqIn: QueueReader,
  mqOut: QueueWriter,
  stopBuf: Uint32Array
) {
  let msgOut = new Int32Array([1, 2, 3, 4, 5, 6]);

  const PER_ROUND = 1e7;
  let received = 0;

  // Seed the buffer with some messages.
  //for (let i = 0; i < 1e5; i++) {
  for (let i = 0; i < (threadId == 1 ? 0 : 0); i++) {
    console.log(threadId, "Bootstrap message sent");
    mqOut.write(msgOut);
  }

  const start = Date.now();

  for (let round = 0; round < 100; round++) {
    console.log(`====== ROUND ${round} ======`);
    if (Atomics.load(stopBuf, 0)) break;
    for (let i = 0; i < PER_ROUND; ) {
      if (threadId === 1) {
        let msgIn = mqIn.beginRead();
        mqIn.endRead();
      } else {
        let slOut = mqOut.beginWrite(24);
        mqOut.endWrite();
      }
      //let msgIn = mqIn.readInto(Int32Array);
      i++;
    }
    received += PER_ROUND;
    console.log(
      threadId,
      "messages processed:",
      received,
      "bufs:",
      Buf.debugInfo(),
      mqIn.buffer.byteLength,
      mqOut.buffer.byteLength
    );
    const elapsed = (Date.now() - start) / 1000;
    console.log(
      threadId,
      "throughput (msg/sec):",
      Math.floor(received / elapsed),
      mqIn.counters,
      mqOut.counters
    );
    console.log(mqIn, mqOut);
    await new Promise(res => setTimeout(res, 10));
  }
}

async function extra(stopBuf: Uint32Array) {
  const PER_ROUND = 1e7;
  const PER_SUBROUND = 10;
  let received = 0;
  const start = Date.now();

  let ab = new SharedArrayBuffer(PER_SUBROUND * 100);
  let i32 = new Int32Array(ab);
  let mqIn = new QueueReader(ab);
  let mqOut = new QueueWriter(ab);

  for (let round = 0; round < 100; round++) {
    console.log(`====== EXTRA ${round} ======`);
    if (Atomics.load(stopBuf, 0)) break;
    for (let i = 0; i < PER_ROUND; i += PER_SUBROUND) {
      let outLen = (Math.ceil(Math.random() * 30) | 0) + 8;
      for (let j = 0; j < PER_SUBROUND; j++) {
        let slOut = mqOut.beginWrite(outLen);
        i32[slOut.byteOffset / 4 + 1] = 1e6 + 1e3 * (i % 10) + j;
        i32[slOut.byteOffset / 4 + 2] = 0;
        mqOut.endWrite();
      }
      for (let j = 0; j < PER_SUBROUND; j++) {
        let slIn = mqIn.beginRead();
        i32[slIn.byteOffset / 4 + 1] *= -1;
        i32[slIn.byteOffset / 4 + 2] = -(1e6 + 1e3 * (i % 10) + j);
        mqIn.endRead();
      }
    }
    received += PER_ROUND;
    console.log("messages processed:", received, "bufs:", Buf.debugInfo());
    const elapsed = (Date.now() - start) / 1000;
    console.log(
      "throughput (msg/sec):",
      Math.floor(received / elapsed),
      mqIn.counters,
      mqOut.counters
    );
    await new Promise(res => setTimeout(res, 10));
  }
}

interface StartupMessage {
  threadId: number;
  bufPort: MessagePort;
  bufIdBuf: SharedArrayBuffer;
  mqInBuf: SharedArrayBuffer;
  mqOutBuf: SharedArrayBuffer;
  stopBuf: Uint32Array;
}

const stopBuf = new Uint32Array(new SharedArrayBuffer(4));

async function domSetup() {
  // This thread simulates the JS thread.
  console.log("In domMain()");
  // Set up the buffer port and send startup info to the worker.
  const bufChan = new MessageChannel();
  // Create small initial buffers for the mq.
  const mqBuf1 = new SharedArrayBuffer(4 * 8 * 1e5 * 1);
  const mqBuf2 = new SharedArrayBuffer(4 * 9.6 * 1e5 * 2);
  // Create buffer for the buffer ID counter;
  const bufIdBuf = new SharedArrayBuffer(4);
  // Spin up the web worker thread.
  const worker1 = new Worker("./main.ts");
  worker1.postMessage(
    {
      threadId: 1,
      bufPort: bufChan.port1,
      bufIdBuf: bufIdBuf,
      mqInBuf: mqBuf1,
      mqOutBuf: mqBuf2,
      stopBuf
    } as StartupMessage,
    [bufChan.port1]
  );
  // Spin up the web worker thread.
  const worker2 = new Worker("./main.ts");
  worker2.postMessage(
    {
      threadId: 2,
      bufPort: bufChan.port2,
      bufIdBuf: bufIdBuf,
      mqInBuf: mqBuf2,
      mqOutBuf: mqBuf1,
      stopBuf
    } as StartupMessage,
    [bufChan.port2]
  );
}

async function workerSetup() {
  // This thread simulates the backend thread (which can't allocate buffers
  // by itself).
  console.log("In workerMain()");
  // Wait for start-up data.
  const {
    threadId,
    bufPort,
    bufIdBuf,
    mqInBuf,
    mqOutBuf,
    stopBuf
  }: StartupMessage = await new Promise<StartupMessage>(res =>
    addEventListener("message", e => res(e.data), { once: true })
  );
  // Set up buffer port and message queues.
  Buf.setup(bufPort, bufIdBuf);
  const mqIn = new QueueReader(Buf.import(mqInBuf).ab);
  const mqOut = new QueueWriter(Buf.import(mqOutBuf).ab);
  await main(threadId, mqIn, mqOut, stopBuf);
}

// Disable parcel HMR since it seems to always get stuck in a reload loop,
// and then we keep creating extra workers, and lots of badness happens.
const globalEval = eval;
const global = globalEval("this");
if (global.beenHereBefore) {
  throw new Error("Please disable parcel HMR.");
}
global.beenHereBefore = true;

if (typeof window !== "undefined") {
  global.start = () => domSetup().catch(console.error);
  global.stop = () => Atomics.store(stopBuf, 0, 1);
  global.extra = () => extra(stopBuf);
} else {
  workerSetup().catch(console.error);
}
