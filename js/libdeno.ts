import { RawSourceMap } from "./types";
import { globalEval } from "./global_eval";

// The libdeno functions are moved so that users can't access them.
type MessageCallback = (msg: Uint8Array) => void;

// These enum values must match v8::PromiseHookType.
export enum PromiseHookType {
  Init = 0,
  Resolve,
  Before,
  After
}

export type PromiseRejectEvent =
  | "RejectWithNoHandler"
  | "HandlerAddedAfterReject"
  | "ResolveAfterResolved"
  | "RejectAfterResolved";

interface Libdeno {
  recv(cb: MessageCallback): void;

  send(control: ArrayBufferView, data?: ArrayBufferView): null | Uint8Array;

  print(x: string, isErr?: boolean): void;

  setGlobalErrorHandler: (
    handler: (
      message: string,
      source: string,
      line: number,
      col: number,
      error: Error
    ) => void
  ) => void;

  setPromiseHook: (
    handler: (
      type: PromiseHookType,
      promise: Promise<unknown>,
      parent?: Promise<unknown>
    ) => void
  ) => void;

  setPromiseRejectHandler: (
    handler: (
      error: Error | string,
      event: PromiseRejectEvent,
      /* tslint:disable-next-line:no-any */
      promise: Promise<any>
    ) => void
  ) => void;

  setPromiseErrorExaminer: (handler: () => boolean) => void;

  mainSource: string;
  mainSourceMap: RawSourceMap;
}

const window = globalEval("this");
export const libdeno = window.libdeno as Libdeno;
