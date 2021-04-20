// Copyright 2018-2021 the Deno authors. All rights reserved. MIT license.

const listener = Deno.listenTls({
  port: Number(Deno.args[0]),
  certFile: "./cli/tests/tls/localhost.crt",
  keyFile: "./cli/tests/tls/localhost.key",
  alpnProtocols: ["h2", "http/1.1", "foobar"],
});

console.log("READY");

for await (const conn of listener) {
  // Start a `read` op to avoid closing the TLS stream before the handshake is
  // complete. We don't expect to actually receive any data, so `read()` should
  // return `null`.
  if (await conn.read(new Uint8Array(1)) !== null) {
    throw new Error("did not expect to receive data on TLS stream");
  }
  conn.close();
}
