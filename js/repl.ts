// Copyright 2018 the Deno authors. All rights reserved. MIT license.
import * as msg from "gen/msg_generated";
import * as flatbuffers from "./flatbuffers";
import { assert } from "./util";
import * as deno from "./deno";
import * as dispatch from "./dispatch";
import { exit } from "./os";
import { window } from "./globals";

function startRepl(name: string): void {
  dispatch.sendSync(...startReplReq(name));
}

function startReplReq(
  name: string
): [flatbuffers.Builder, msg.Any, flatbuffers.Offset] {
  const builder = flatbuffers.createBuilder();
  const name_ = builder.createString(name);

  msg.ReplStart.startReplStart(builder);
  msg.ReplStart.addName(builder, name_);
  const inner = msg.ReplStart.endReplStart(builder);
  return [builder, msg.Any.ReplStart, inner];
}

function exitRepl(name: string): void {
  dispatch.sendSync(...exitReplReq(name));
}

function exitReplReq(
  name: string
): [flatbuffers.Builder, msg.Any, flatbuffers.Offset] {
  const builder = flatbuffers.createBuilder();
  const name_ = builder.createString(name);
  msg.ReplExit.startReplExit(builder);
  msg.ReplExit.addName(builder, name_);
  const inner = msg.ReplExit.endReplExit(builder);
  return [builder, msg.Any.ReplExit, inner];
}

// @internal
export async function readline(name: string, prompt: string): Promise<string> {
  return res(await dispatch.sendAsync(...req(name, prompt)));
}

function req(
  name: string,
  prompt: string
): [flatbuffers.Builder, msg.Any, flatbuffers.Offset] {
  const builder = flatbuffers.createBuilder();
  const name_ = builder.createString(name);
  const prompt_ = builder.createString(prompt);
  msg.ReplReadline.startReplReadline(builder);
  msg.ReplReadline.addName(builder, name_);
  msg.ReplReadline.addPrompt(builder, prompt_);
  const inner = msg.ReplReadline.endReplReadline(builder);
  return [builder, msg.Any.ReplReadline, inner];
}

function res(baseRes: null | msg.Base): string {
  assert(baseRes != null);
  assert(msg.Any.ReplReadlineRes === baseRes!.innerType());
  const inner = new msg.ReplReadlineRes();
  assert(baseRes!.inner(inner) != null);
  const line = inner.line();
  assert(line !== null);
  return line || "";
}

// @internal
export async function replLoop(): Promise<void> {
  window.deno = deno; // FIXME use a new scope (rather than window).

  const replName = "deno";
  const prompt = "> ";

  startRepl(replName);

  let line = "";
  while (true) {
    try {
      line = await readline(replName, prompt);
      line = line.trim();
    } catch (err) {
      if (err.message === "EOF") {
        break;
      }
      console.error(err);
      exit(1);
    }
    if (!line) {
      continue;
    }
    if (line === ".exit") {
      break;
    }
    try {
      const result = eval.call(window, line); // FIXME use a new scope.
      console.log(result);
    } catch (err) {
      if (err instanceof Error) {
        console.error(`${err.constructor.name}: ${err.message}`);
      } else {
        console.error("Thrown:", err);
      }
    }
  }

  exitRepl(replName);
}
