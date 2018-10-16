import { PromiseHookType, PromiseRejectEvent } from "./libdeno";

/* tslint:disable-next-line:no-any */
const rejectMap = new Map<Promise<any>, string>();
// For uncaught promise rejection errors

/* tslint:disable-next-line:no-any */
const otherErrorMap = new Map<Promise<any>, string>();
// For reject after resolve / resolve after resolve errors

let promiseIdCounter = 0;

function getPromiseId(promise: Promise<unknown>): number {
  const obj = promise as { id?: number };
  if (obj.id) {
    return obj.id;
  } else {
    return (obj.id = ++promiseIdCounter);
  }
}

const typeNames = {
  [PromiseHookType.Init]: "Init",
  [PromiseHookType.Resolve]: "Resolve",
  [PromiseHookType.Before]: "Before",
  [PromiseHookType.After]: "After"
};

export function promiseHook(
  type: PromiseHookType,
  promise: Promise<unknown>,
  parent?: Promise<unknown>
) {
  console.log(
    `Promise hook ${typeNames[type]}`,
    getPromiseId(promise),
    parent ? getPromiseId(parent) : -1
  );
}

function callThenHook(promise: Promise<unknown>, resolve: unknown, reject: unknown, resolution: unknown) {
  console.log("Promise then", getPromiseId(promise), resolve, reject, resolution);
}

const then = Promise.prototype.then;
Promise.prototype.then = function(a, b) {
  let rv;
  try {
    return rv = then.call(this, a, b);
  } finally {
    callThenHook(this, a, b, rv);
  }
};

export function promiseRejectHandler(
  error: Error | string,
  event: PromiseRejectEvent,
  /* tslint:disable-next-line:no-any */
  promise: Promise<any>
) {
  switch (event) {
    case "RejectWithNoHandler":
      rejectMap.set(promise, (error as Error).stack || "RejectWithNoHandler");
      break;
    case "HandlerAddedAfterReject":
      rejectMap.delete(promise);
      break;
    default:
      // error is string here
      otherErrorMap.set(promise, `Promise warning: ${error as string}`);
  }
}

// Return true when continue, false to die on uncaught promise reject
export function promiseErrorExaminer(): boolean {
  if (otherErrorMap.size > 0) {
    for (const msg of otherErrorMap.values()) {
      console.log(msg);
    }
    otherErrorMap.clear();
  }
  if (rejectMap.size > 0) {
    for (const msg of rejectMap.values()) {
      console.log(msg);
    }
    rejectMap.clear();
    return false;
  }
  return true;
}
