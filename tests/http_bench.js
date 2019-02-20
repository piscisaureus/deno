// Used for benchmarking Deno's networking. See tools/http_benchmark.py
// TODO Replace this with a real HTTP server once
// https://github.com/denoland/deno/issues/726 is completed.
// Note: this is a keep-alive server.
const addr = Deno.args[1] || "127.0.0.1:4500";
const listener = Deno.listen("tcp", addr);
const response = new TextEncoder().encode(
  "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World\n"
);

let ctr = 0;
function dump() {
  if (++ctr % 1e5 === 0 && window.libdeno.tx !== undefined) {
    console.log("tx", window.libdeno.tx.counters);
    console.log("rx", window.libdeno.rx.counters);
  }
}

async function handle(conn) {
  const buffer = new Uint8Array(1024);
  try {
    while (true) {
      const r = await conn.read(buffer);

      if (r.eof) {
        break;
      }
      await conn.write(response);
      dump();
    }
  } finally {
    conn.close();
  }
}
async function main() {
  console.log("Listening on", addr);
  while (true) {
    const conn = await listener.accept();
    handle(conn);
  }
}
main();
