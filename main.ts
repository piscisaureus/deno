import { Buf } from "./buf";
import { QueueReader, QueueWriter, Message } from "./queue";

async function main(
  threadId: number,
  mqIn: QueueReader,
  mqOut: QueueWriter,
  stopBuf: Uint32Array
) {
  let msg: Message;
  let msgOut = new Int32Array([1, 2, 3, 4, 5, 6]);

  const PER_ROUND = 1e7;
  let received = 0;

  // Seed the buffer with some messages.
  //for (let i = 0; i < 1e5; i++) {
  for (let i = 0; i < 1e5; i++) {
    mqOut.write(msgOut);
  }

  const start = Date.now();

  for (let round = 0; round < 100; round++) {
    console.log(`====== ROUND ${round} ======`);
    if (Atomics.load(stopBuf, 0)) break;
    for (let i = 0; i < PER_ROUND; ) {
      mqOut.write(msgOut);
      msg = mqIn.beginRead();
      mqIn.endRead();
      i++;
    }
    received += PER_ROUND;
    console.log(
      threadId,
      "messages processed:",
      received,
      "bufs:",
      Buf.debugInfo(),
      (<any>mqIn).buf.ab.byteLength,
      (<any>mqOut).buf.ab.byteLength
    );
    const elapsed = (Date.now() - start) / 1000;
    console.log(
      threadId,
      "throughput (msg/sec):",
      Math.floor(received / elapsed),
      "mqIn counters",
      mqIn.counters,
      "mqOut counters",
      mqOut.counters
    );
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
  const mqIn = new QueueReader(Buf.import(mqInBuf));
  const mqOut = new QueueWriter(Buf.import(mqOutBuf));
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
} else {
  workerSetup().catch(console.error);
}
