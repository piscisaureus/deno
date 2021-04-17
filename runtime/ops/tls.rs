// Copyright 2018-2021 the Deno authors. All rights reserved. MIT license.

pub use rustls;
pub use webpki;

use crate::ops::io::TcpStreamResource;
use crate::ops::io::TlsStreamResource;
use crate::ops::net::IpAddr;
use crate::ops::net::OpAddr;
use crate::ops::net::OpConn;
use crate::permissions::Permissions;
use crate::resolve_addr::resolve_addr;
use crate::resolve_addr::resolve_addr_sync;
use deno_core::error::bad_resource;
use deno_core::error::bad_resource_id;
use deno_core::error::custom_error;
use deno_core::error::generic_error;
use deno_core::error::AnyError;
use deno_core::futures::future::poll_fn;
use deno_core::futures::ready;
use deno_core::futures::task::noop_waker_ref;
use deno_core::futures::task::AtomicWaker;
use deno_core::futures::task::Context;
use deno_core::futures::task::Poll;
use deno_core::futures::task::RawWaker;
use deno_core::futures::task::RawWakerVTable;
use deno_core::futures::task::Waker;
use deno_core::AsyncRefCell;
use deno_core::CancelHandle;
use deno_core::CancelTryFuture;
use deno_core::OpState;
use deno_core::RcRef;
use deno_core::Resource;
use deno_core::ResourceId;
use deno_core::ZeroCopyBuf;
use io::Error;
use io::Read;
use io::Write;
use rustls::internal::pemfile::certs;
use rustls::internal::pemfile::pkcs8_private_keys;
use rustls::internal::pemfile::rsa_private_keys;
use rustls::Certificate;
use rustls::ClientConfig;
use rustls::ClientSession;
use rustls::NoClientAuth;
use rustls::PrivateKey;
use rustls::ServerConfig;
use rustls::ServerSession;
use rustls::Session;
use rustls::StoresClientSessions;
use serde::Deserialize;
use std::borrow::Cow;
use std::cell::RefCell;
use std::collections::HashMap;
use std::convert::From;
use std::fs::File;
use std::io;
use std::io::BufReader;
use std::io::ErrorKind;
use std::ops::Deref;
use std::ops::DerefMut;
use std::path::Path;
use std::pin::Pin;
use std::rc::Rc;
use std::sync::Arc;
use std::sync::Mutex;
use std::sync::Weak;
use tokio::io::AsyncRead;
use tokio::io::AsyncWrite;
use tokio::io::ReadBuf;
use tokio::net::TcpListener;
use tokio::net::TcpStream;
use tokio::task::spawn_local;
use webpki::DNSNameRef;

lazy_static::lazy_static! {
  static ref CLIENT_SESSION_MEMORY_CACHE: Arc<ClientSessionMemoryCache> =
    Arc::new(ClientSessionMemoryCache::default());
}

#[derive(Default)]
struct ClientSessionMemoryCache(Mutex<HashMap<Vec<u8>, Vec<u8>>>);

impl StoresClientSessions for ClientSessionMemoryCache {
  fn get(&self, key: &[u8]) -> Option<Vec<u8>> {
    self.0.lock().unwrap().get(key).cloned()
  }

  fn put(&self, key: Vec<u8>, value: Vec<u8>) -> bool {
    let mut sessions = self.0.lock().unwrap();
    // TODO(bnoordhuis) Evict sessions LRU-style instead of arbitrarily.
    while sessions.len() >= 1024 {
      let key = sessions.keys().next().unwrap().clone();
      sessions.remove(&key);
    }
    sessions.insert(key, value);
    true
  }
}

#[derive(Debug)]
enum TlsSession {
  Client(ClientSession),
  Server(ServerSession),
}

impl Deref for TlsSession {
  type Target = dyn Session;

  fn deref(&self) -> &Self::Target {
    match self {
      TlsSession::Client(client_session) => client_session,
      TlsSession::Server(server_session) => server_session,
    }
  }
}

impl DerefMut for TlsSession {
  fn deref_mut(&mut self) -> &mut Self::Target {
    match self {
      TlsSession::Client(client_session) => client_session,
      TlsSession::Server(server_session) => server_session,
    }
  }
}

impl From<ClientSession> for TlsSession {
  fn from(client_session: ClientSession) -> Self {
    TlsSession::Client(client_session)
  }
}

impl From<ServerSession> for TlsSession {
  fn from(server_session: ServerSession) -> Self {
    TlsSession::Server(server_session)
  }
}

#[derive(Copy, Clone, Debug, Eq, PartialEq)]
enum Flow {
  Read,
  Write,
}

#[allow(clippy::enum_variant_names)]
#[derive(Copy, Clone, Debug, PartialEq, Eq, PartialOrd, Ord)]
enum Shut {
  Open,
  Eof,
  TlsShut,
  TcpShut,
}

#[derive(Debug)]
pub struct TlsStream(Option<TlsStreamInner>);

impl TlsStream {
  fn new(tcp: TcpStream, tls: TlsSession) -> Self {
    let inner = TlsStreamInner {
      tcp,
      tls,
      rd_shut: Shut::Open,
      wr_shut: Shut::Open,
    };
    Self(Some(inner))
  }

  pub fn new_client_side(
    tcp: TcpStream,
    tls_config: &Arc<ClientConfig>,
    hostname: DNSNameRef,
  ) -> Self {
    let tls = TlsSession::Client(ClientSession::new(tls_config, hostname));
    Self::new(tcp, tls)
  }

  pub fn new_server_side(
    tcp: TcpStream,
    tls_config: &Arc<ServerConfig>,
  ) -> Self {
    let tls = TlsSession::Server(ServerSession::new(tls_config));
    Self::new(tcp, tls)
  }

  pub async fn handshake(&mut self) -> io::Result<()> {
    poll_fn(|cx| self.inner_mut().poll_io(cx, Flow::Write)).await
  }

  fn into_split(self) -> (ReadHalf, WriteHalf) {
    let shared = Shared::new(self);
    let rd = ReadHalf {
      shared: shared.clone(),
    };
    let wr = WriteHalf { shared };
    (rd, wr)
  }

  /// Tokio-rustls compatibility: returns a reference to the underlying TCP
  /// stream, and a reference to the Rustls `Session` object.
  pub fn get_ref(&self) -> (&TcpStream, &dyn Session) {
    let inner = self.0.as_ref().unwrap();
    (&inner.tcp, &*inner.tls)
  }

  fn inner_mut(&mut self) -> &mut TlsStreamInner {
    self.0.as_mut().unwrap()
  }
}

impl AsyncRead for TlsStream {
  fn poll_read(
    mut self: Pin<&mut Self>,
    cx: &mut Context<'_>,
    buf: &mut ReadBuf<'_>,
  ) -> Poll<io::Result<()>> {
    self.inner_mut().poll_read(cx, buf)
  }
}

impl AsyncWrite for TlsStream {
  fn poll_write(
    mut self: Pin<&mut Self>,
    cx: &mut Context<'_>,
    buf: &[u8],
  ) -> Poll<io::Result<usize>> {
    self.inner_mut().poll_write(cx, buf)
  }

  fn poll_flush(
    mut self: Pin<&mut Self>,
    cx: &mut Context<'_>,
  ) -> Poll<io::Result<()>> {
    self.inner_mut().poll_io(cx, Flow::Write)
    // The underlying TCP stream does not need to be flushed.
  }

  fn poll_shutdown(
    mut self: Pin<&mut Self>,
    cx: &mut Context<'_>,
  ) -> Poll<io::Result<()>> {
    self.inner_mut().poll_close(cx, false)
  }
}

impl Drop for TlsStream {
  fn drop(&mut self) {
    let mut inner = self.0.take().unwrap();

    let mut cx = Context::from_waker(noop_waker_ref());
    let use_linger_task = inner.poll_close(&mut cx, true).is_pending();

    if use_linger_task {
      spawn_local(poll_fn(move |cx| inner.poll_close(cx, true)));
    }
  }
}

#[derive(Debug)]
pub struct TlsStreamInner {
  tls: TlsSession,
  tcp: TcpStream,
  rd_shut: Shut,
  wr_shut: Shut,
}

impl TlsStreamInner {
  fn wants_rd_shut(&self) -> Shut {
    if self.rd_shut == Shut::Open {
      Shut::Open
    } else if self.wr_shut < Shut::TcpShut {
      Shut::TlsShut
    } else {
      Shut::TcpShut
    }
  }

  fn wants_wr_shut(&self) -> Shut {
    if self.wr_shut == Shut::Open {
      Shut::Open
    } else if self.rd_shut < Shut::TlsShut {
      Shut::TlsShut
    } else {
      Shut::TcpShut
    }
  }

  fn d(&mut self) {
    use std::os::unix::io::AsRawFd;
    eprintln!(
      "read {}: ready {:?}, want {:?}, eof {:?}, shut {:?}",
      self.tcp.as_raw_fd(),
      "?",
      self.tls.wants_read(),
      self.rd_shut,
      self.wants_rd_shut()
    );
    eprintln!(
      "write {}: ready {:?}, want {:?}, eof {:?}, shut {:?}",
      self.tcp.as_raw_fd(),
      "?",
      self.tls.wants_write(),
      self.wr_shut,
      self.wants_wr_shut()
    );
  }

  fn poll_io(
    &mut self,
    cx: &mut Context<'_>,
    flow: Flow,
  ) -> Poll<io::Result<()>> {
    // Initially, assume that the TCP stream is both readable and writable. If
    // this turns out not to be the case, `read_tls` or `write_tls()` will fail
    // with `WouldBlock`; only then do we arrange to be asynchronously notified
    // of read/write.
    let mut tcp_read_ready = true;
    let mut tcp_write_ready = true;

    loop {
      self.d();

      while self.wants_wr_shut() > self.wr_shut {
        match self.wr_shut {
          Shut::Open => unreachable!(),
          Shut::Eof => {
            self.tls.send_close_notify();
            self.wr_shut = Shut::TlsShut;
          }
          Shut::TlsShut => {
            ready!(Pin::new(&mut self.tcp).poll_shutdown(cx))?;
            self.wr_shut = Shut::TcpShut;
          }
          Shut::TcpShut => {}
        }
      }

      // This loop won't starve the runtime: `wants_write()` returns `false`
      // when all outbound data currently in Rustls' buffers has been processed.
      while tcp_write_ready && self.tls.wants_write() {
        let mut wrapper = ImplementWriteTrait(&mut self.tcp);
        match self.tls.write_tls(&mut wrapper) {
          Ok(0) => unreachable!(),
          Ok(_) => {}
          Err(err) if err.kind() == ErrorKind::WouldBlock => {
            tcp_write_ready = self.tcp.poll_write_ready(cx)?.is_ready();
          }
          Err(err) => return Poll::Ready(Err(err)),
        }
      }

      // This loop won't starve the runtime: `wants_read()` returns `false`
      // as soon as Rustls has cleartext for us to read.
      while tcp_read_ready
        && self.tls.wants_read()
        && self.wants_rd_shut() == Shut::Open
      {
        self.d();
        match self.tls.read(&mut []) {
          Ok(0) if self.wants_rd_shut() == Shut::Open => {}
          Ok(0) => {
            return Poll::Ready(Err(ErrorKind::ConnectionReset.into()));
          }
          Ok(_) => unreachable!(),
          Err(err) if err.kind() == ErrorKind::ConnectionAborted => {
            // `Session::read()` returns `ConnectionAborted` when a
            // 'CloseNotify' alert has been received, which indicates that
            // the remote peer wants to gracefully end the TLS session.
            if self.rd_shut < Shut::TlsShut {
              self.rd_shut = Shut::TlsShut;
            }
            if self.wants_rd_shut() < Shut::TcpShut {
              continue;
            }
          }
          Err(err) => return Poll::Ready(Err(err)),
        }

        let mut wrapper = ImplementReadTrait(&mut self.tcp);
        match self.tls.read_tls(&mut wrapper) {
          Ok(0) if self.tls.is_handshaking() => {
            let err = Error::new(ErrorKind::UnexpectedEof, "tls handshake eof");
            return Poll::Ready(Err(err));
          }
          Ok(0) => {
            self.rd_shut = Shut::TcpShut;
          }
          Ok(_) => match self.tls.process_new_packets() {
            // Do a zero-length plaintext read so we can detect the arrival of
            // 'CloseNotify' messages, even if only the write half is active.
            // Actually reading data from the socket is done in `poll_read()`.
            Ok(()) => {}
            Err(err) => {
              let err = Error::new(ErrorKind::InvalidData, err);
              return Poll::Ready(Err(err));
            }
          },
          Err(err) if err.kind() == ErrorKind::WouldBlock => {
            tcp_read_ready = self.tcp.poll_read_ready(cx)?.is_ready()
          }
          Err(err) => return Poll::Ready(Err(err)),
        }
      }

      if tcp_write_ready && self.tls.wants_write() {
        continue;
      }
      if self.wants_wr_shut() > self.wr_shut && self.wr_shut < Shut::TcpShut {
        continue;
      }

      let poll_again = match flow {
        _ if self.tls.is_handshaking() => true,
        _ if self.rd_shut == Shut::TcpShut && self.wr_shut == Shut::TcpShut => {
          false
        }
        Flow::Read => {
          self.tls.wants_read()
            && (self.wants_rd_shut() == Shut::Open
              || self.wants_rd_shut() > self.rd_shut)
        }
        Flow::Write => {
          self.tls.wants_write() || (self.wants_wr_shut() > self.wr_shut)
        }
      };
      return match poll_again {
        false => Poll::Ready(Ok(())),
        true => Poll::Pending,
      };
    }
  }

  fn poll_read(
    &mut self,
    cx: &mut Context<'_>,
    buf: &mut ReadBuf<'_>,
  ) -> Poll<io::Result<()>> {
    ready!(self.poll_io(cx, Flow::Read))?;

    if self.rd_shut == Shut::Open {
      let buf_slice =
        unsafe { &mut *(buf.unfilled_mut() as *mut [_] as *mut [u8]) };
      let bytes_read = self.tls.read(buf_slice)?;
      assert_ne!(bytes_read, 0);
      unsafe { buf.assume_init(bytes_read) };
      buf.advance(bytes_read);
    }

    Poll::Ready(Ok(()))
  }

  fn poll_write(
    &mut self,
    cx: &mut Context<'_>,
    buf: &[u8],
  ) -> Poll<io::Result<usize>> {
    if buf.is_empty() {
      // Tokio-rustls compatibility: a zero byte write always succeeds.
      Poll::Ready(Ok(0))
    } else if self.wr_shut != Shut::Open {
      // Bail out if stream has been shut down for writing.
      Poll::Ready(Err(ErrorKind::BrokenPipe.into()))
    } else {
      ready!(self.poll_io(cx, Flow::Write))?;

      let bytes_written = self.tls.write(buf)?;
      assert_ne!(bytes_written, 0);

      // We try to flush as much data as we can, but we have already handed off
      // at least some bytes to rustls, so we can't return `Poll::Pending()` any
      // more, as this would indicate to the caller that it should try again.
      let _ = self.poll_io(cx, Flow::Write)?;

      Poll::Ready(Ok(bytes_written))
    }
  }

  fn poll_close(
    &mut self,
    cx: &mut Context<'_>,
    wait_for_remote: bool,
  ) -> Poll<io::Result<()>> {
    // Schedule outbound 'CloseNotify', and set flag to disallow `write()`s.
    if self.wr_shut < Shut::Eof {
      self.tls.send_close_notify();
      self.wr_shut = Shut::Eof;
    }

    // Flush remaining bytes in Rustls' send buffer, plus 'CloseNotify' alert.
    if self.wr_shut < Shut::TlsShut {
      ready!(self.poll_io(cx, Flow::Write))?;
    }

    if wait_for_remote && self.rd_shut < Shut::TcpShut {
      if self.rd_shut == Shut::Open {
        self.rd_shut = Shut::Eof;
      }
      ready!(self.poll_io(cx, Flow::Read))?;
    }
    // Receive 'CloseNotify' alert from remote end.
    /*if wait_for_remote && self.rd_shut < Shut::TlsShut {
      ready!(self.poll_io(cx, Flow::Read))?;
      if self.rd_shut < Shut::TlsShut {
        // Apparently, instead of 'CloseNotify', we received more regular data.
        // Abort the TLS session instead of closing gracefully.
        return Poll::Ready(Err(ErrorKind::ConnectionReset.into()));
      }
    }

    // Shut down the underlying TCP socket, but only after the 'CloseNotify'
    // alert that was sent by the remote has been received.
    if self.wr_shut < Shut::TcpShut && self.rd_shut >= Shut::TlsShut {
      ready!(Pin::new(&mut self.tcp).poll_shutdown(cx))?;
      self.wr_shut = Shut::TcpShut;
    }

    // Wait for the remote end to gracefully close the TCP connection.
    // TODO(piscisaureus): this is unnecessary; remove when stable.
    if wait_for_remote && self.rd_shut < Shut::TcpShut {
      ready!(self.poll_io(cx, Flow::Read))?;
      if self.rd_shut < Shut::TcpShut {
        return Poll::Ready(Err(ErrorKind::ConnectionReset.into()));
      }
    }*/

    Poll::Ready(Ok(()))
  }
}

#[derive(Debug)]
pub struct ReadHalf {
  shared: Arc<Shared>,
}

impl ReadHalf {
  pub fn reunite(self, wr: WriteHalf) -> TlsStream {
    assert!(Arc::ptr_eq(&self.shared, &wr.shared));
    drop(wr); // Drop `wr`, so only one strong reference to `shared` remains.

    Arc::try_unwrap(self.shared)
      .unwrap_or_else(|_| panic!("Arc::<Shared>::try_unwrap() failed"))
      .tls_stream
      .into_inner()
      .unwrap()
  }
}

impl AsyncRead for ReadHalf {
  fn poll_read(
    self: Pin<&mut Self>,
    cx: &mut Context<'_>,
    buf: &mut ReadBuf<'_>,
  ) -> Poll<io::Result<()>> {
    self
      .shared
      .poll_flow_with(cx, Flow::Read, move |tls, cx| tls.poll_read(cx, buf))
  }
}

#[derive(Debug)]
pub struct WriteHalf {
  shared: Arc<Shared>,
}

impl AsyncWrite for WriteHalf {
  fn poll_write(
    self: Pin<&mut Self>,
    cx: &mut Context<'_>,
    buf: &[u8],
  ) -> Poll<io::Result<usize>> {
    self
      .shared
      .poll_flow_with(cx, Flow::Write, move |tls, cx| tls.poll_write(cx, buf))
  }

  fn poll_flush(
    self: Pin<&mut Self>,
    cx: &mut Context<'_>,
  ) -> Poll<io::Result<()>> {
    self
      .shared
      .poll_flow_with(cx, Flow::Write, |tls, cx| tls.poll_flush(cx))
  }

  fn poll_shutdown(
    self: Pin<&mut Self>,
    cx: &mut Context<'_>,
  ) -> Poll<io::Result<()>> {
    self
      .shared
      .poll_flow_with(cx, Flow::Write, |tls, cx| tls.poll_shutdown(cx))
  }
}

#[derive(Debug)]
struct Shared {
  tls_stream: Mutex<TlsStream>,
  rd_waker: AtomicWaker,
  wr_waker: AtomicWaker,
}

impl Shared {
  fn new(tls_stream: TlsStream) -> Arc<Self> {
    let self_ = Self {
      tls_stream: Mutex::new(tls_stream),
      rd_waker: AtomicWaker::new(),
      wr_waker: AtomicWaker::new(),
    };
    Arc::new(self_)
  }

  fn poll_flow_with<R>(
    self: &Arc<Self>,
    cx: &mut Context<'_>,
    flow: Flow,
    mut f: impl FnMut(Pin<&mut TlsStream>, &mut Context<'_>) -> R,
  ) -> R {
    match flow {
      Flow::Read => self.rd_waker.register(cx.waker()),
      Flow::Write => self.wr_waker.register(cx.waker()),
    }

    let shared_waker = self.new_waker();
    let mut cx = Context::from_waker(&shared_waker);

    let mut tls_stream = self.tls_stream.lock().unwrap();
    f(Pin::new(&mut tls_stream), &mut cx)
  }

  const WAKER_VTABLE: RawWakerVTable = RawWakerVTable::new(
    Self::clone_waker,
    Self::wake_waker,
    Self::wake_waker_by_ref,
    Self::drop_waker,
  );

  fn new_waker(self: &Arc<Self>) -> Waker {
    let self_weak = Arc::downgrade(self);
    let self_ptr = self_weak.into_raw() as *const ();
    let raw_waker = RawWaker::new(self_ptr, &Self::WAKER_VTABLE);
    unsafe { Waker::from_raw(raw_waker) }
  }

  fn clone_waker(self_ptr: *const ()) -> RawWaker {
    let self_weak = unsafe { Weak::from_raw(self_ptr as *const Self) };
    let ptr1 = self_weak.clone().into_raw();
    let ptr2 = self_weak.into_raw();
    assert!(ptr1 == ptr2);
    RawWaker::new(self_ptr, &Self::WAKER_VTABLE)
  }

  fn wake_waker(self_ptr: *const ()) {
    Self::wake_waker_by_ref(self_ptr);
    Self::drop_waker(self_ptr);
  }

  fn wake_waker_by_ref(self_ptr: *const ()) {
    let self_weak = unsafe { Weak::from_raw(self_ptr as *const Self) };
    if let Some(self_arc) = Weak::upgrade(&self_weak) {
      self_arc.rd_waker.wake();
      self_arc.wr_waker.wake();
    }
    self_weak.into_raw();
  }

  fn drop_waker(self_ptr: *const ()) {
    let _ = unsafe { Weak::from_raw(self_ptr as *const Self) };
  }
}

struct ImplementReadTrait<'a, T>(&'a mut T);

impl Read for ImplementReadTrait<'_, TcpStream> {
  fn read(&mut self, buf: &mut [u8]) -> io::Result<usize> {
    self.0.try_read(buf)
  }
}

struct ImplementWriteTrait<'a, T>(&'a mut T);

impl Write for ImplementWriteTrait<'_, TcpStream> {
  fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
    self.0.try_write(buf)
  }

  fn flush(&mut self) -> io::Result<()> {
    Ok(())
  }
}

pub fn init(rt: &mut deno_core::JsRuntime) {
  super::reg_async(rt, "op_start_tls", op_start_tls);
  super::reg_async(rt, "op_connect_tls", op_connect_tls);
  super::reg_sync(rt, "op_listen_tls", op_listen_tls);
  super::reg_async(rt, "op_accept_tls", op_accept_tls);
}

#[derive(Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct ConnectTlsArgs {
  transport: String,
  hostname: String,
  port: u16,
  cert_file: Option<String>,
}

#[derive(Deserialize)]
#[serde(rename_all = "camelCase")]
struct StartTlsArgs {
  rid: ResourceId,
  cert_file: Option<String>,
  hostname: String,
}

async fn op_start_tls(
  state: Rc<RefCell<OpState>>,
  args: StartTlsArgs,
  _zero_copy: Option<ZeroCopyBuf>,
) -> Result<OpConn, AnyError> {
  let rid = args.rid;
  let hostname = match &*args.hostname {
    "" => "localhost",
    n => n,
  };
  let cert_file = args.cert_file.as_deref();

  {
    super::check_unstable2(&state, "Deno.startTls");
    let mut s = state.borrow_mut();
    let permissions = s.borrow_mut::<Permissions>();
    permissions.net.check(&(hostname, Some(0)))?;
    if let Some(path) = cert_file {
      permissions.read.check(Path::new(path))?;
    }
  }

  let hostname_dns = DNSNameRef::try_from_ascii_str(hostname)
    .map_err(|_| invalid_hostname(hostname))?;

  let resource_rc = state
    .borrow_mut()
    .resource_table
    .take::<TcpStreamResource>(rid)
    .ok_or_else(bad_resource_id)?;
  let resource = Rc::try_unwrap(resource_rc)
    .expect("Only a single use of this resource should happen");
  let (read_half, write_half) = resource.into_inner();
  let tcp_stream = read_half.reunite(write_half)?;

  let local_addr = tcp_stream.local_addr()?;
  let remote_addr = tcp_stream.peer_addr()?;

  let mut tls_config = ClientConfig::new();
  tls_config.set_persistence(CLIENT_SESSION_MEMORY_CACHE.clone());
  tls_config
    .root_store
    .add_server_trust_anchors(&webpki_roots::TLS_SERVER_ROOTS);
  if let Some(path) = cert_file {
    let key_file = File::open(path)?;
    let reader = &mut BufReader::new(key_file);
    tls_config.root_store.add_pem_file(reader).unwrap();
  }
  let tls_config = Arc::new(tls_config);

  let tls_stream =
    TlsStream::new_client_side(tcp_stream, &tls_config, hostname_dns);

  let rid = {
    let mut state_ = state.borrow_mut();
    state_
      .resource_table
      .add(TlsStreamResource::new(tls_stream.into_split()))
  };

  Ok(OpConn {
    rid,
    local_addr: Some(OpAddr::Tcp(IpAddr {
      hostname: local_addr.ip().to_string(),
      port: local_addr.port(),
    })),
    remote_addr: Some(OpAddr::Tcp(IpAddr {
      hostname: remote_addr.ip().to_string(),
      port: remote_addr.port(),
    })),
  })
}

async fn op_connect_tls(
  state: Rc<RefCell<OpState>>,
  args: ConnectTlsArgs,
  _zero_copy: Option<ZeroCopyBuf>,
) -> Result<OpConn, AnyError> {
  assert_eq!(args.transport, "tcp");
  let hostname = match &*args.hostname {
    "" => "localhost",
    n => n,
  };
  let port = args.port;
  let cert_file = args.cert_file.as_deref();

  {
    let mut s = state.borrow_mut();
    let permissions = s.borrow_mut::<Permissions>();
    permissions.net.check(&(hostname, Some(port)))?;
    if let Some(path) = cert_file {
      permissions.read.check(Path::new(path))?;
    }
  }

  let hostname_dns = DNSNameRef::try_from_ascii_str(hostname)
    .map_err(|_| invalid_hostname(hostname))?;

  let connect_addr = resolve_addr(hostname, port)
    .await?
    .next()
    .ok_or_else(|| generic_error("No resolved address found"))?;
  let tcp_stream = TcpStream::connect(connect_addr).await?;
  let local_addr = tcp_stream.local_addr()?;
  let remote_addr = tcp_stream.peer_addr()?;

  let mut tls_config = ClientConfig::new();
  tls_config.set_persistence(CLIENT_SESSION_MEMORY_CACHE.clone());
  tls_config
    .root_store
    .add_server_trust_anchors(&webpki_roots::TLS_SERVER_ROOTS);
  if let Some(path) = cert_file {
    let key_file = File::open(path)?;
    let reader = &mut BufReader::new(key_file);
    tls_config.root_store.add_pem_file(reader).unwrap();
  }
  let tls_config = Arc::new(tls_config);

  let tls_stream =
    TlsStream::new_client_side(tcp_stream, &tls_config, hostname_dns);

  let rid = {
    let mut state_ = state.borrow_mut();
    state_
      .resource_table
      .add(TlsStreamResource::new(tls_stream.into_split()))
  };

  Ok(OpConn {
    rid,
    local_addr: Some(OpAddr::Tcp(IpAddr {
      hostname: local_addr.ip().to_string(),
      port: local_addr.port(),
    })),
    remote_addr: Some(OpAddr::Tcp(IpAddr {
      hostname: remote_addr.ip().to_string(),
      port: remote_addr.port(),
    })),
  })
}

fn load_certs(path: &str) -> Result<Vec<Certificate>, AnyError> {
  let cert_file = File::open(path)?;
  let reader = &mut BufReader::new(cert_file);

  let certs = certs(reader)
    .map_err(|_| custom_error("InvalidData", "Unable to decode certificate"))?;

  if certs.is_empty() {
    let e = custom_error("InvalidData", "No certificates found in cert file");
    return Err(e);
  }

  Ok(certs)
}

fn invalid_hostname(hostname: &str) -> AnyError {
  custom_error("TypeError", format!("invalid hostname: '{}'", hostname))
}

fn key_decode_err() -> AnyError {
  custom_error("InvalidData", "Unable to decode key")
}

fn key_not_found_err() -> AnyError {
  custom_error("InvalidData", "No keys found in key file")
}

/// Starts with -----BEGIN RSA PRIVATE KEY-----
fn load_rsa_keys(path: &str) -> Result<Vec<PrivateKey>, AnyError> {
  let key_file = File::open(path)?;
  let reader = &mut BufReader::new(key_file);
  let keys = rsa_private_keys(reader).map_err(|_| key_decode_err())?;
  Ok(keys)
}

/// Starts with -----BEGIN PRIVATE KEY-----
fn load_pkcs8_keys(path: &str) -> Result<Vec<PrivateKey>, AnyError> {
  let key_file = File::open(path)?;
  let reader = &mut BufReader::new(key_file);
  let keys = pkcs8_private_keys(reader).map_err(|_| key_decode_err())?;
  Ok(keys)
}

fn load_keys(path: &str) -> Result<Vec<PrivateKey>, AnyError> {
  let path = path.to_string();
  let mut keys = load_rsa_keys(&path)?;

  if keys.is_empty() {
    keys = load_pkcs8_keys(&path)?;
  }

  if keys.is_empty() {
    return Err(key_not_found_err());
  }

  Ok(keys)
}

pub struct TlsListenerResource {
  tcp_listener: AsyncRefCell<TcpListener>,
  tls_config: Arc<ServerConfig>,
  cancel_handle: CancelHandle,
}

impl Resource for TlsListenerResource {
  fn name(&self) -> Cow<str> {
    "tlsListener".into()
  }

  fn close(self: Rc<Self>) {
    self.cancel_handle.cancel();
  }
}

#[derive(Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct ListenTlsArgs {
  transport: String,
  hostname: String,
  port: u16,
  cert_file: String,
  key_file: String,
  alpn_protocols: Option<Vec<String>>,
}

fn op_listen_tls(
  state: &mut OpState,
  args: ListenTlsArgs,
  _zero_copy: Option<ZeroCopyBuf>,
) -> Result<OpConn, AnyError> {
  assert_eq!(args.transport, "tcp");
  let hostname = &*args.hostname;
  let port = args.port;
  let cert_file = &*args.cert_file;
  let key_file = &*args.key_file;

  {
    let permissions = state.borrow_mut::<Permissions>();
    permissions.net.check(&(hostname, Some(port)))?;
    permissions.read.check(Path::new(cert_file))?;
    permissions.read.check(Path::new(key_file))?;
  }

  let mut tls_config = ServerConfig::new(NoClientAuth::new());
  if let Some(alpn_protocols) = args.alpn_protocols {
    super::check_unstable(state, "Deno.listenTls#alpn_protocols");
    tls_config.alpn_protocols =
      alpn_protocols.into_iter().map(|s| s.into_bytes()).collect();
  }
  tls_config
    .set_single_cert(load_certs(cert_file)?, load_keys(key_file)?.remove(0))
    .expect("invalid key or certificate");

  let bind_addr = resolve_addr_sync(hostname, port)?
    .next()
    .ok_or_else(|| generic_error("No resolved address found"))?;
  let std_listener = std::net::TcpListener::bind(bind_addr)?;
  std_listener.set_nonblocking(true)?;
  let tcp_listener = TcpListener::from_std(std_listener)?;
  let local_addr = tcp_listener.local_addr()?;

  let tls_listener_resource = TlsListenerResource {
    tcp_listener: AsyncRefCell::new(tcp_listener),
    tls_config: Arc::new(tls_config),
    cancel_handle: Default::default(),
  };

  let rid = state.resource_table.add(tls_listener_resource);

  Ok(OpConn {
    rid,
    local_addr: Some(OpAddr::Tcp(IpAddr {
      hostname: local_addr.ip().to_string(),
      port: local_addr.port(),
    })),
    remote_addr: None,
  })
}

async fn op_accept_tls(
  state: Rc<RefCell<OpState>>,
  rid: ResourceId,
  _zero_copy: Option<ZeroCopyBuf>,
) -> Result<OpConn, AnyError> {
  let resource = state
    .borrow()
    .resource_table
    .get::<TlsListenerResource>(rid)
    .ok_or_else(|| bad_resource("Listener has been closed"))?;

  let cancel_handle = RcRef::map(&resource, |r| &r.cancel_handle);
  let tcp_listener = RcRef::map(&resource, |r| &r.tcp_listener)
    .try_borrow_mut()
    .ok_or_else(|| custom_error("Busy", "Another accept task is ongoing"))?;

  let (tcp_stream, remote_addr) =
    match tcp_listener.accept().try_or_cancel(&cancel_handle).await {
      Ok(tuple) => tuple,
      Err(err) if err.kind() == ErrorKind::Interrupted => {
        // FIXME(bartlomieju): compatibility with current JS implementation.
        return Err(bad_resource("Listener has been closed"));
      }
      Err(err) => return Err(err.into()),
    };

  let local_addr = tcp_stream.local_addr()?;

  let tls_stream = TlsStream::new_server_side(tcp_stream, &resource.tls_config);

  let rid = {
    let mut state_ = state.borrow_mut();
    state_
      .resource_table
      .add(TlsStreamResource::new(tls_stream.into_split()))
  };

  Ok(OpConn {
    rid,
    local_addr: Some(OpAddr::Tcp(IpAddr {
      hostname: local_addr.ip().to_string(),
      port: local_addr.port(),
    })),
    remote_addr: Some(OpAddr::Tcp(IpAddr {
      hostname: remote_addr.ip().to_string(),
      port: remote_addr.port(),
    })),
  })
}
