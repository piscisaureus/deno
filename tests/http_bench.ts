// Used for benchmarking Deno's networking. See tools/http_benchmark.py
// Note: this is a keep-alive server.
import * as deno from "deno";
const addr = deno.args[1] || "0.0.0.0:4500";
const resBody = new TextEncoder().encode("Hello World\n");

const server = deno.httpListen(addr);
console.log(`Server listening on ${addr}`);

function serve(req: deno.ServerRequest, res: deno.ServerResponse) {
  res.status = 200;
  res.headers = [["server", "ryans server"], ["content-type", "text/plain"]];
  res.writeResponse(resBody);
}

async function run() {
  for (;;) {
    serve(...(await server.accept()));
  }
}

for (let i = 0; i < 1 /* parallel accepts */; i++) {
  run();
}
