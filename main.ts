import { Buf } from "./buf";

function domMain() {
  // This thread simulates the JS thread.
  console.log("In domMain()");
  new Worker("./main.ts"); // Spin up the web worker thread.
}

function workerMain() {
  // This thread simulates the backend thread (which can't allocate buffers
  // by itself).
  console.log("In workerMain()");
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
  domMain();
} else {
  workerMain();
}
