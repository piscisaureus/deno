// Copyright 2018-2021 the Deno authors. All rights reserved. MIT license.

const listener = Deno.listenTls({
  port: Number(Deno.args[0]),
  certFile: "./cli/tests/tls/localhost.crt",
  keyFile: "./cli/tests/tls/localhost.key",
  alpnProtocols: ["h2", "http/1.1", "foobar"],
});

console.log("READY");

for await (const conn of listener) {
  if (await conn.read(new Uint8Array(1)) !== null) {
    throw new Error("should not receive data on TLS connection");
  }
  conn.close();
}
