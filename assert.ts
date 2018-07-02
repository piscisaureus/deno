export function assert(cond: boolean, message?: string) {
  if (!cond) {
    debugger;
    throw new Error("Assertion failed" + (message ? `: ${message}` : ""));
  }
}
