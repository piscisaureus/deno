function throwAssertionError(message?: string): never {
  debugger;
  throw new Error("Assertion failed" + (message ? `: ${message}` : ""));
}

export function assert(cond: boolean, message?: string): void {
  if (!cond) {
    return throwAssertionError(message);
  }
}

export function fail(message?: string): never {
  return throwAssertionError(message);
}
