// Copyright 2018-2019 the Deno authors. All rights reserved. MIT license.
import { libdeno } from "./libdeno";
import * as flatbuffers from "./flatbuffers";
import * as msg from "gen/msg_generated";
import * as errors from "./errors";
import * as util from "./util";

let nextCmdId = 0;
const promiseTable = new Map<number, util.Resolvable<msg.Base>>();

let fireTimers: () => void;

export function setFireTimersCallback(fn: () => void) {
  fireTimers = fn;
}

export function handleAsyncMsgFromRust2() {
  // This is the libdeno.setIdle callback
  util.log("handleAsyncMsgFromRust2");

  // TODO Should we loop here?

  // Before we block on beginReceive, we check if there are actually any pending
  // promises. If not, we return.
  if (promiseTable.size === 0) {
    util.log("promiseTable empty");
    return;
  }

  const { byteOffset, byteLength } = libdeno.rx.beginReceive();
  const buf = libdeno.rx.u8.subarray(byteOffset, byteOffset + byteLength);
  const u32 = libdeno.rx.u32.subarray(
    byteOffset / 4,
    (byteOffset + byteLength) / 4
  );
  const resType = u32[6];
  if (resType === 738197504 || resType === 771751936) {
    // Read or write.
    const cmdId = u32[7];
    const promise = promiseTable.get(cmdId);
    util.assert(promise != null, `Expecting promise in table. ${cmdId}`);
    promiseTable.delete(cmdId);
    promise!.resolve((null as unknown) as msg.Base);
  } else {
    handleAsyncMsgFromRust(buf);
  }
  libdeno.rx.endReceive();
}

export function handleAsyncMsgFromRust(ui8: Uint8Array) {
  // If a the buffer is empty, recv() on the native side timed out and we
  // did not receive a message.
  if (ui8.length) {
    const bb = new flatbuffers.ByteBuffer(ui8);
    const base = msg.Base.getRootAsBase(bb);
    const cmdId = base.cmdId();
    const promise = promiseTable.get(cmdId);
    util.assert(promise != null, `Expecting promise in table. ${cmdId}`);
    promiseTable.delete(cmdId);
    const err = errors.maybeError(base);
    if (err != null) {
      promise!.reject(err);
    } else {
      promise!.resolve(base);
    }
  }
  // Fire timers that have become runnable.
  fireTimers();
}

// @internal
export function sendAsync(
  builder: flatbuffers.Builder,
  innerType: msg.Any,
  inner: flatbuffers.Offset,
  data?: ArrayBufferView
): Promise<msg.Base> {
  const [cmdId, resBuf] = sendInternal(builder, innerType, inner, data, false);
  util.assert(resBuf == null);
  const promise = util.createResolvable<msg.Base>();
  promiseTable.set(cmdId, promise);
  return promise;
}

let msgTemplate = new Uint32Array([
  20,
  1179664,
  4,
  0,
  786443,
  16,
  3 /*promise id*/,
  721420288,
  12,
  393216,
  262152,
  6,
  999 /*rid*/
]);
let msgTemplateU8 = new Uint8Array(msgTemplate.buffer);

export function sendAsync2(isRead: boolean, rid: number): Promise<msg.Base> {
  let cmdId = nextCmdId++;
  let opCode = isRead ? 721420288 : 754974720;
  msgTemplate[6] = cmdId;
  msgTemplate[7] = opCode;
  msgTemplate[12] = rid;
  libdeno.tx.send(msgTemplateU8);
  const promise = util.createResolvable<msg.Base>();
  promiseTable.set(cmdId, promise);
  return promise;
}

// @internal
export function sendSync(
  builder: flatbuffers.Builder,
  innerType: msg.Any,
  inner: flatbuffers.Offset,
  data?: ArrayBufferView
): null | msg.Base {
  const [cmdId, resBuf] = sendInternal(builder, innerType, inner, data, true);
  util.assert(cmdId >= 0);
  if (resBuf == null) {
    return null;
  } else {
    const u8 = new Uint8Array(resBuf!);
    const bb = new flatbuffers.ByteBuffer(u8);
    const baseRes = msg.Base.getRootAsBase(bb);
    errors.maybeThrowError(baseRes);
    return baseRes;
  }
}

function sendInternal(
  builder: flatbuffers.Builder,
  innerType: msg.Any,
  inner: flatbuffers.Offset,
  data: undefined | ArrayBufferView,
  sync = true
): [number, null | Uint8Array] {
  const cmdId = nextCmdId++;
  msg.Base.startBase(builder);
  msg.Base.addInner(builder, inner);
  msg.Base.addInnerType(builder, innerType);
  msg.Base.addSync(builder, sync);
  msg.Base.addCmdId(builder, cmdId);
  builder.finish(msg.Base.endBase(builder));

  const u8 = builder.asUint8Array();
  const u32 = new Uint32Array(u8.buffer, u8.byteOffset, u8.byteLength / 4);
  util.log("sendInternal", sync, u32.byteLength, Array.from(u32));

  let res;
  if (sync) {
    res = libdeno.send(u8, data);
  } else {
    res = null;
  }

  libdeno.tx.resizeSend(u8.byteLength);
  libdeno.tx.endSend(!sync);

  // builder.inUse = false;
  return [cmdId, res];
}
