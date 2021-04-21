// Copyright 2018-2021 the Deno authors. All rights reserved. MIT license.
import {
  assert,
  assertEquals,
  assertStrictEquals,
  assertThrows,
  assertThrowsAsync,
  deferred,
  unitTest,
} from "./test_util.ts";
import { BufReader, BufWriter } from "../../../test_util/std/io/bufio.ts";
import { TextProtoReader } from "../../../test_util/std/textproto/mod.ts";

const SIZE_64KB = 1 << 16;
const SIZE_1MB = 1 << 20;

const encoder = new TextEncoder();
const decoder = new TextDecoder();

unitTest(async function connectTLSNoPerm(): Promise<void> {
  await assertThrowsAsync(async () => {
    await Deno.connectTls({ hostname: "github.com", port: 443 });
  }, Deno.errors.PermissionDenied);
});

unitTest(
  { perms: { read: true, net: true } },
  async function connectTLSInvalidHost(): Promise<void> {
    const listener = await Deno.listenTls({
      hostname: "localhost",
      port: 3567,
      certFile: "cli/tests/tls/localhost.crt",
      keyFile: "cli/tests/tls/localhost.key",
    });

    await assertThrowsAsync(async () => {
      await Deno.connectTls({ hostname: "127.0.0.1", port: 3567 });
    }, TypeError);

    listener.close();
  },
);

unitTest(async function connectTLSCertFileNoReadPerm(): Promise<void> {
  await assertThrowsAsync(async () => {
    await Deno.connectTls({
      hostname: "github.com",
      port: 443,
      certFile: "cli/tests/tls/RootCA.crt",
    });
  }, Deno.errors.PermissionDenied);
});

unitTest(
  { perms: { read: true, net: true } },
  function listenTLSNonExistentCertKeyFiles(): void {
    const options = {
      hostname: "localhost",
      port: 3500,
      certFile: "cli/tests/tls/localhost.crt",
      keyFile: "cli/tests/tls/localhost.key",
    };

    assertThrows(() => {
      Deno.listenTls({
        ...options,
        certFile: "./non/existent/file",
      });
    }, Deno.errors.NotFound);

    assertThrows(() => {
      Deno.listenTls({
        ...options,
        keyFile: "./non/existent/file",
      });
    }, Deno.errors.NotFound);
  },
);

unitTest({ perms: { net: true } }, function listenTLSNoReadPerm(): void {
  assertThrows(() => {
    Deno.listenTls({
      hostname: "localhost",
      port: 3500,
      certFile: "cli/tests/tls/localhost.crt",
      keyFile: "cli/tests/tls/localhost.key",
    });
  }, Deno.errors.PermissionDenied);
});

unitTest(
  {
    perms: { read: true, write: true, net: true },
  },
  function listenTLSEmptyKeyFile(): void {
    const options = {
      hostname: "localhost",
      port: 3500,
      certFile: "cli/tests/tls/localhost.crt",
      keyFile: "cli/tests/tls/localhost.key",
    };

    const testDir = Deno.makeTempDirSync();
    const keyFilename = testDir + "/key.pem";
    Deno.writeFileSync(keyFilename, new Uint8Array([]), {
      mode: 0o666,
    });

    assertThrows(() => {
      Deno.listenTls({
        ...options,
        keyFile: keyFilename,
      });
    }, Error);
  },
);

unitTest(
  { perms: { read: true, write: true, net: true } },
  function listenTLSEmptyCertFile(): void {
    const options = {
      hostname: "localhost",
      port: 3500,
      certFile: "cli/tests/tls/localhost.crt",
      keyFile: "cli/tests/tls/localhost.key",
    };

    const testDir = Deno.makeTempDirSync();
    const certFilename = testDir + "/cert.crt";
    Deno.writeFileSync(certFilename, new Uint8Array([]), {
      mode: 0o666,
    });

    assertThrows(() => {
      Deno.listenTls({
        ...options,
        certFile: certFilename,
      });
    }, Error);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function dialAndListenTLS(): Promise<void> {
    const resolvable = deferred();
    const hostname = "localhost";
    const port = 3500;

    const listener = Deno.listenTls({
      hostname,
      port,
      certFile: "cli/tests/tls/localhost.crt",
      keyFile: "cli/tests/tls/localhost.key",
    });

    const response = encoder.encode(
      "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World\n",
    );

    listener.accept().then(
      async (conn): Promise<void> => {
        assert(conn.remoteAddr != null);
        assert(conn.localAddr != null);
        await conn.write(response);
        // TODO(bartlomieju): this might be a bug
        setTimeout(() => {
          conn.close();
          resolvable.resolve();
        }, 0);
      },
    );

    const conn = await Deno.connectTls({
      hostname,
      port,
      certFile: "cli/tests/tls/RootCA.pem",
    });
    assert(conn.rid > 0);
    const w = new BufWriter(conn);
    const r = new BufReader(conn);
    const body = `GET / HTTP/1.1\r\nHost: ${hostname}:${port}\r\n\r\n`;
    const writeResult = await w.write(encoder.encode(body));
    assertEquals(body.length, writeResult);
    await w.flush();
    const tpr = new TextProtoReader(r);
    const statusLine = await tpr.readLine();
    assert(statusLine !== null, `line must be read: ${String(statusLine)}`);
    const m = statusLine.match(/^(.+?) (.+?) (.+?)$/);
    assert(m !== null, "must be matched");
    const [_, proto, status, ok] = m;
    assertEquals(proto, "HTTP/1.1");
    assertEquals(status, "200");
    assertEquals(ok, "OK");
    const headers = await tpr.readMIMEHeader();
    assert(headers !== null);
    const contentLength = parseInt(headers.get("content-length")!);
    const bodyBuf = new Uint8Array(contentLength);
    await r.readFull(bodyBuf);
    assertEquals(decoder.decode(bodyBuf), "Hello World\n");
    conn.close();
    listener.close();
    await resolvable;
  },
);

let nextPort = 3501;
function getPort() {
  return nextPort++;
}

async function tlsPair(): Promise<[Deno.Conn, Deno.Conn]> {
  const port = getPort();
  const listener = Deno.listenTls({
    hostname: "localhost",
    port,
    certFile: "cli/tests/tls/localhost.crt",
    keyFile: "cli/tests/tls/localhost.key",
  });

  const acceptPromise = listener.accept();
  const connectPromise = Deno.connectTls({
    hostname: "localhost",
    port,
    certFile: "cli/tests/tls/RootCA.pem",
  });
  const conns = await Promise.all([acceptPromise, connectPromise]);

  listener.close();

  return conns;
}

async function sleep(msec: number): Promise<void> {
  await new Promise((res, _rej) => setTimeout(res, msec));
}

async function sendThenCloseWriteThenReceive(
  conn: Deno.Conn,
  chunkCount: number,
  chunkSize: number,
): Promise<void> {
  const byteCount = chunkCount * chunkSize;
  const buf = new Uint8Array(chunkSize); // Note: buf is size of _chunk_.
  let n: number;

  // Slowly send 42s.
  buf.fill(42);
  for (let remaining = byteCount; remaining > 0; remaining -= n) {
    n = await conn.write(buf.subarray(0, remaining));
    assert(n >= 1);
    await sleep(10);
  }

  // Send EOF.
  await conn.closeWrite();

  // Receive 69s.
  for (let remaining = byteCount; remaining > 0; remaining -= n) {
    buf.fill(0);
    n = await conn.read(buf) as number;
    assert(n >= 1);
    assertStrictEquals(buf[0], 69);
    assertStrictEquals(buf[n - 1], 69);
  }

  conn.close();
}

async function receiveThenSend(
  conn: Deno.Conn,
  chunkCount: number,
  chunkSize: number,
): Promise<void> {
  const byteCount = chunkCount * chunkSize;
  const buf = new Uint8Array(byteCount); // Note: buf size equals `byteCount`.
  let n: number;

  // Receive 42s.
  for (let remaining = byteCount; remaining > 0; remaining -= n) {
    buf.fill(0);
    n = await conn.read(buf) as number;
    assert(n >= 1);
    assertStrictEquals(buf[0], 42);
    assertStrictEquals(buf[n - 1], 42);
  }

  // Slowly send 69s.
  buf.fill(69);
  for (let remaining = byteCount; remaining > 0; remaining -= n) {
    n = await conn.write(buf.subarray(0, remaining));
    assert(n >= 1);
    await sleep(10);
  }

  conn.close();
}

unitTest(
  { perms: { read: true, net: true } },
  async function tlsServerStreamHalfCloseSendOneByte(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendThenCloseWriteThenReceive(serverConn, 1, 1),
      receiveThenSend(clientConn, 1, 1),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsClientStreamHalfCloseSendOneByte(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendThenCloseWriteThenReceive(clientConn, 1, 1),
      receiveThenSend(serverConn, 1, 1),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsServerStreamHalfCloseSendOneChunk(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendThenCloseWriteThenReceive(serverConn, 1, SIZE_1MB),
      receiveThenSend(clientConn, 1, SIZE_1MB),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsClientStreamHalfCloseSendOneChunk(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendThenCloseWriteThenReceive(clientConn, 1, SIZE_1MB),
      receiveThenSend(serverConn, 1, SIZE_1MB),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsServerStreamHalfCloseSendManyBytes(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendThenCloseWriteThenReceive(serverConn, 100, 1),
      receiveThenSend(clientConn, 100, 1),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsClientStreamHalfCloseSendManyBytes(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendThenCloseWriteThenReceive(clientConn, 100, 1),
      receiveThenSend(serverConn, 100, 1),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsServerStreamHalfCloseSendManyChunks(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendThenCloseWriteThenReceive(serverConn, 100, SIZE_64KB),
      receiveThenSend(clientConn, 100, SIZE_64KB),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsClientStreamHalfCloseSendManyChunks(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendThenCloseWriteThenReceive(clientConn, 100, SIZE_64KB),
      receiveThenSend(serverConn, 100, SIZE_64KB),
    ]);
  },
);

async function sendAlotReceiveNothing(conn: Deno.Conn): Promise<void> {
  // Start receive op.
  const readBuf = new Uint8Array(1024);
  const readPromise = conn.read(readBuf);

  // Send 1 MB of data.
  const writeBuf = new Uint8Array(SIZE_1MB);
  writeBuf.fill(42);
  await conn.write(writeBuf);

  // Send EOF.
  await conn.closeWrite();

  // Close the connection.
  conn.close();

  // Read op should be canceled.
  await assertThrowsAsync(
    async () => await readPromise,
    Deno.errors.Interrupted,
  );
}

async function receiveAlotSendNothing(conn: Deno.Conn): Promise<void> {
  const readBuf = new Uint8Array(1024);
  let n: number | null;

  // Receive 1 MB of data.
  for (let nread = 0; nread < SIZE_1MB; nread += n!) {
    n = await conn.read(readBuf);
    assertStrictEquals(typeof n, "number");
    assert(n! > 0);
    assertStrictEquals(readBuf[0], 42);
  }

  // Close the connection, without sending anything at all.
  conn.close();
}

unitTest(
  { perms: { read: true, net: true } },
  async function tlsServerStreamCancelRead(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendAlotReceiveNothing(serverConn),
      receiveAlotSendNothing(clientConn),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsClientStreamCancelRead(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendAlotReceiveNothing(clientConn),
      receiveAlotSendNothing(serverConn),
    ]);
  },
);

async function sendReceiveEmptyBuf(conn: Deno.Conn): Promise<void> {
  const byteBuf = new Uint8Array([1]);
  const emptyBuf = new Uint8Array(0);
  let n: number | null;

  n = await conn.write(emptyBuf);
  assertStrictEquals(n, 0);

  n = await conn.read(emptyBuf);
  assertStrictEquals(n, 0);

  n = await conn.write(byteBuf);
  assertStrictEquals(n, 1);

  n = await conn.read(byteBuf);
  assertStrictEquals(n, 1);

  await conn.closeWrite();

  n = await conn.write(emptyBuf);
  assertStrictEquals(n, 0);

  await assertThrowsAsync(async () => {
    await conn.write(byteBuf);
  }, Deno.errors.BrokenPipe);

  n = await conn.write(emptyBuf);
  assertStrictEquals(n, 0);

  n = await conn.read(byteBuf);
  assertStrictEquals(n, null);

  conn.close();
}

unitTest(
  { perms: { read: true, net: true } },
  async function tlsStreamSendReceiveEmptyBuf(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      sendReceiveEmptyBuf(serverConn),
      sendReceiveEmptyBuf(clientConn),
    ]);
  },
);

function immediateClose(conn: Deno.Conn): Promise<void> {
  conn.close();
  return Promise.resolve();
}

async function closeWriteAndClose(conn: Deno.Conn): Promise<void> {
  await conn.closeWrite();

  if (await conn.read(new Uint8Array(1)) !== null) {
    throw new Error("did not expect to receive data on TLS stream");
  }

  conn.close();
}

unitTest(
  { perms: { read: true, net: true } },
  async function tlsServerStreamImmediateClose(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      immediateClose(serverConn),
      closeWriteAndClose(clientConn),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsClientStreamImmediateClose(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      closeWriteAndClose(serverConn),
      immediateClose(clientConn),
    ]);
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function tlsClientAndServerStreamImmediateClose(): Promise<void> {
    const [serverConn, clientConn] = await tlsPair();
    await Promise.all([
      immediateClose(serverConn),
      immediateClose(clientConn),
    ]);
  },
);

function createHttpsListener(port: number): Deno.Listener {
  // Query format: `curl --insecure https://localhost:8443/z/12345`
  // The server returns a response consisting of 12345 times the letter 'z'.
  const listener = Deno.listenTls({
    hostname: "localhost",
    port,
    certFile: "./cli/tests/tls/localhost.crt",
    keyFile: "./cli/tests/tls/localhost.key",
  });

  serve(listener);
  return listener;

  async function serve(listener: Deno.Listener) {
    for await (const conn of listener) {
      const EOL = "\r\n";

      // Read GET request plus headers.
      let req = "";
      const buf = new Uint8Array(0x1000);
      while (!req.endsWith(EOL + EOL)) {
        const n = await conn.read(buf);
        if (n === null) throw new Error("Unexpected EOF");
        req += [...buf.subarray(0, n)]
          .map((c) => String.fromCharCode(c))
          .join("");
      }

      // Parse GET request.
      const { filler, count, version } =
        /^GET \/(?<filler>[^\/]+)\/(?<count>\d+) HTTP\/(?<version>1\.\d)\r\n/
          .exec(req)!.groups as {
            filler: string;
            count: string;
            version: string;
          };

      // Generate response.
      const resBody = new TextEncoder().encode(filler.repeat(+count));
      let resHead = new TextEncoder().encode(
        [
          `HTTP/${version} 200 OK`,
          `Content-Length: ${resBody.length}`,
          "Content-Type: text/plain",
        ].join(EOL) + EOL + EOL,
      );

      // Send response.
      await conn.write(resHead);
      await conn.write(resBody);

      // Close TCP connection.
      conn.close();
    }
  }
}

async function curl(url: string): Promise<string> {
  const curl = Deno.run({
    cmd: ["curl", "--insecure", url],
    stdout: "piped",
  });

  try {
    const [status, output] = await Promise.all([curl.status(), curl.output()]);
    if (!status.success) {
      throw new Error(`curl ${url} failed: ${status.code}`);
    }
    return new TextDecoder().decode(output);
  } finally {
    curl.close();
  }
}

unitTest(
  { perms: { read: true, net: true, run: true } },
  async function curlFakeHttpsServer(): Promise<void> {
    const port = getPort();
    const listener = createHttpsListener(port);

    const res1 = await curl(`https://localhost:${port}/d/1`);
    assertStrictEquals(res1, "d");

    const res2 = await curl(`https://localhost:${port}/e/12345`);
    assertStrictEquals(res2, "e".repeat(12345));

    const count3 = 1 << 17; // 128 kB.
    const res3 = await curl(`https://localhost:${port}/n/${count3}`);
    assertStrictEquals(res3, "n".repeat(count3));

    const count4 = 12345678;
    const res4 = await curl(`https://localhost:${port}/o/${count4}`);
    assertStrictEquals(res4, "o".repeat(count4));

    listener.close();
  },
);

unitTest(
  { perms: { read: true, net: true } },
  async function startTls(): Promise<void> {
    const hostname = "smtp.gmail.com";
    const port = 587;
    const encoder = new TextEncoder();

    let conn = await Deno.connect({
      hostname,
      port,
    });

    let writer = new BufWriter(conn);
    let reader = new TextProtoReader(new BufReader(conn));

    let line: string | null = (await reader.readLine()) as string;
    assert(line.startsWith("220"));

    await writer.write(encoder.encode(`EHLO ${hostname}\r\n`));
    await writer.flush();

    while ((line = (await reader.readLine()) as string)) {
      assert(line.startsWith("250"));
      if (line.startsWith("250 ")) break;
    }

    await writer.write(encoder.encode("STARTTLS\r\n"));
    await writer.flush();

    line = await reader.readLine();

    // Received the message that the server is ready to establish TLS
    assertEquals(line, "220 2.0.0 Ready to start TLS");

    conn = await Deno.startTls(conn, { hostname });
    writer = new BufWriter(conn);
    reader = new TextProtoReader(new BufReader(conn));

    // After that use TLS communication again
    await writer.write(encoder.encode(`EHLO ${hostname}\r\n`));
    await writer.flush();

    while ((line = (await reader.readLine()) as string)) {
      assert(line.startsWith("250"));
      if (line.startsWith("250 ")) break;
    }

    conn.close();
  },
);
