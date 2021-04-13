// Copyright 2018-2021 the Deno authors. All rights reserved. MIT license.

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
use deno_core::futures::ready;
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
use io::Read;
use io::Write;
use serde::Deserialize;
use std::borrow::Cow;
use std::cell::RefCell;
use std::collections::HashMap;
use std::convert::From;
use std::fs::File;
use std::io;
use std::io::BufReader;
use std::io::ErrorKind;
use std::mem::transmute;
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
use tokio_rustls::rustls::{
  internal::pemfile::{certs, pkcs8_private_keys, rsa_private_keys},
  Certificate, ClientConfig, ClientSession, NoClientAuth, PrivateKey,
  ServerConfig, ServerSession, Session, StoresClientSessions,
};
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

#[allow(clippy::enum_variant_names)]
#[derive(Copy, Clone, Debug, Eq, PartialEq)]
enum Shut {
  Open,
  TlsShut,
  TcpShut,
}

pub struct TlsStream {
  tls: TlsSession,
  tcp: TcpStream,
  rd_shut: Shut,
  wr_shut: Shut,
}

impl TlsStream {
  fn new(tcp: TcpStream, tls: TlsSession) -> Self {
    Self {
      tcp,
      tls,
      rd_shut: Shut::Open,
      wr_shut: Shut::Open,
    }
  }

  fn new_client(
    tcp: TcpStream,
    tls_config: &Arc<ClientConfig>,
    hostname: DNSNameRef,
  ) -> Self {
    let tls = TlsSession::Client(ClientSession::new(tls_config, hostname));
    Self::new(tcp, tls)
  }

  fn new_server(tcp: TcpStream, tls_config: &Arc<ServerConfig>) -> Self {
    let tls = TlsSession::Server(ServerSession::new(tls_config));
    Self::new(tcp, tls)
  }

  pub fn into_split(self) -> (TlsStreamReader, TlsStreamWriter) {
    let shared = Shared::new(self);
    let rd = TlsStreamReader {
      shared: shared.clone(),
    };
    let wr = TlsStreamWriter { shared };
    (rd, wr)
  }

  fn poll_io(
    &mut self,
    cx: &mut Context<'_>,
    for_reading: bool,
    for_writing: bool,
  ) -> Poll<io::Result<()>> {
    assert!((for_reading && !for_writing) || (!for_reading && for_writing));

    // Initially, assume that the TCP stream is both readable and writable. If
    // this turns out not to be the case, `read_tls` or `write_tls()` will fail
    // with `WouldBlock`; only then do we arrange to be asynchronously notified
    // of read/write.
    let mut tcp_read_ready = true;
    let mut tcp_write_ready = true;

    loop {
      while tcp_write_ready && self.tls.wants_write() {
        let mut wrapper = ImplementWriteTrait(&mut self.tcp);
        match self.tls.write_tls(&mut wrapper) {
          Ok(_) => {}
          Err(err) if err.kind() == ErrorKind::WouldBlock => {
            match self.tcp.poll_write_ready(cx) {
              Poll::Ready(result) => result?,
              Poll::Pending => tcp_write_ready = false,
            }
          }
          Err(err) => return Poll::Ready(Err(err)),
        }
      }

      while tcp_read_ready
        && self.tls.wants_read()
        && self.rd_shut != Shut::TcpShut
      {
        let mut wrapper = ImplementReadTrait(&mut self.tcp);
        match self.tls.read_tls(&mut wrapper) {
          Ok(0) if self.tls.is_handshaking() => {
            let err =
              io::Error::new(ErrorKind::UnexpectedEof, "tls handshake eof");
            return Poll::Ready(Err(err));
          }
          Ok(0) => self.rd_shut = Shut::TcpShut,
          Ok(_) => match self.tls.process_new_packets() {
            Ok(_) => {}
            Err(err) => {
              let err = io::Error::new(ErrorKind::InvalidData, err);
              return Poll::Ready(Err(err));
            }
          },
          Err(err) if err.kind() == ErrorKind::WouldBlock => {
            match self.tcp.poll_read_ready(cx) {
              Poll::Ready(result) => result?,
              Poll::Pending => tcp_read_ready = false,
            }
          }
          Err(err) => return Poll::Ready(Err(err)),
        }
      }

      if tcp_write_ready && self.tls.wants_write() {
        continue;
      }

      if for_reading
        && !self.tls.is_handshaking()
        && (!self.tls.wants_read() || self.rd_shut == Shut::TcpShut)
      {
        return Poll::Ready(Ok(()));
      }
      if for_writing && !self.tls.is_handshaking() && !self.tls.wants_write() {
        return Poll::Ready(Ok(()));
      }

      return Poll::Pending;
    }
  }
}

impl AsyncRead for TlsStream {
  fn poll_read(
    mut self: Pin<&mut Self>,
    cx: &mut Context<'_>,
    buf: &mut ReadBuf<'_>,
  ) -> Poll<io::Result<()>> {
    ready!(self.poll_io(cx, true, false))?;

    let buf_slice: &mut [u8] = unsafe { transmute(buf.unfilled_mut()) };

    match self.tls.read(buf_slice) {
      Ok(bytes_read) => {
        unsafe { buf.assume_init(bytes_read) };
        buf.advance(bytes_read);
        Poll::Ready(Ok(()))
      }
      Err(err) if err.kind() == ErrorKind::ConnectionAborted => {
        // Rustls `read()` returns `ConnectionAborted` when it receives a
        // `CloseNotify` alert; this indicates that the other end of the line
        // has initiated a graceful shutdown at the TLS level.
        self.rd_shut = Shut::TlsShut;
        Poll::Ready(Ok(()))
      }
      Err(err) => Poll::Ready(Err(err)),
    }
  }
}

impl AsyncWrite for TlsStream {
  fn poll_write(
    mut self: Pin<&mut Self>,
    cx: &mut Context<'_>,
    buf: &[u8],
  ) -> Poll<io::Result<usize>> {
    ready!(self.poll_io(cx, false, true))?;

    match self.tls.write(buf) {
      Ok(0) => unreachable!(),
      Ok(bytes_written) => {
        // We try to flush as much as we can, but since we have already handed
        // off some bytes to rustls we can't return `Poll::Pending()` any more,
        // as this would indicate to the caller that it should try again.
        let _ = self.poll_io(cx, false, true)?;
        Poll::Ready(Ok(bytes_written))
      }
      Err(err) => Poll::Ready(Err(err)),
    }
  }

  fn poll_flush(
    mut self: Pin<&mut Self>,
    cx: &mut Context<'_>,
  ) -> Poll<io::Result<()>> {
    ready!(self.poll_io(cx, false, true))?;
    // The underlying TCP stream does not need to be flushed.
    Poll::Ready(Ok(()))
  }

  fn poll_shutdown(
    mut self: Pin<&mut Self>,
    cx: &mut Context<'_>,
  ) -> Poll<io::Result<()>> {
    loop {
      match self.wr_shut {
        Shut::Open => {
          ready!(self.poll_io(cx, false, true))?;
          self.tls.send_close_notify();
          self.wr_shut = Shut::TlsShut;
        }
        Shut::TlsShut => {
          ready!(self.poll_io(cx, false, true))?;
          ready!(Pin::new(&mut self.tcp).poll_shutdown(cx))?;
          self.wr_shut = Shut::TcpShut;
        }
        Shut::TcpShut => {
          return Poll::Ready(Ok(()));
        }
      }
    }
  }
}

pub struct TlsStreamReader {
  shared: Arc<Shared>,
}

impl TlsStreamReader {
  pub fn reunite(self, wr: TlsStreamWriter) -> TlsStream {
    assert!(Arc::ptr_eq(&self.shared, &wr.shared));
    let Self { shared } = self;
    drop(wr); // Drop `wr` so only 1 strong reference to `shared` remains.
    let Shared { tls_stream, .. } = Arc::try_unwrap(shared)
      .unwrap_or_else(|_| panic!("Arc::<Shared>::try_unwrap() failed"));
    Mutex::into_inner(tls_stream)
      .unwrap_or_else(|_| panic!("Mutex::<TlsStream>::into_inner() failed"))
  }
}

impl AsyncRead for TlsStreamReader {
  fn poll_read(
    self: Pin<&mut Self>,
    cx: &mut Context<'_>,
    buf: &mut ReadBuf<'_>,
  ) -> Poll<io::Result<()>> {
    self
      .shared
      .poll_rd_with(cx, move |tls_stream, cx| tls_stream.poll_read(cx, buf))
  }
}

pub struct TlsStreamWriter {
  shared: Arc<Shared>,
}

impl AsyncWrite for TlsStreamWriter {
  fn poll_write(
    self: Pin<&mut Self>,
    cx: &mut Context<'_>,
    buf: &[u8],
  ) -> Poll<io::Result<usize>> {
    self
      .shared
      .poll_wr_with(cx, move |tls_stream, cx| tls_stream.poll_write(cx, buf))
  }

  fn poll_flush(
    self: Pin<&mut Self>,
    cx: &mut Context<'_>,
  ) -> Poll<io::Result<()>> {
    self
      .shared
      .poll_wr_with(cx, |tls_stream, cx| tls_stream.poll_flush(cx))
  }

  fn poll_shutdown(
    self: Pin<&mut Self>,
    cx: &mut Context<'_>,
  ) -> Poll<io::Result<()>> {
    self
      .shared
      .poll_wr_with(cx, |tls_stream, cx| tls_stream.poll_shutdown(cx))
  }
}

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

  fn poll_rd_with<R>(
    self: &Arc<Self>,
    cx: &mut Context<'_>,
    mut f: impl FnMut(Pin<&mut TlsStream>, &mut Context<'_>) -> R,
  ) -> R {
    self.rd_waker.register(cx.waker());
    let shared_waker = self.new_waker();
    let mut cx = Context::from_waker(&shared_waker);
    let mut tls_stream = self.tls_stream.lock().unwrap();
    f(Pin::new(&mut tls_stream), &mut cx)
  }

  fn poll_wr_with<R>(
    self: &Arc<Self>,
    cx: &mut Context<'_>,
    mut f: impl FnMut(Pin<&mut TlsStream>, &mut Context<'_>) -> R,
  ) -> R {
    self.wr_waker.register(cx.waker());
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

  let tls_stream = TlsStream::new_client(tcp_stream, &tls_config, hostname_dns);

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

  let tls_stream = TlsStream::new_client(tcp_stream, &tls_config, hostname_dns);

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

  let tls_stream = TlsStream::new_server(tcp_stream, &resource.tls_config);

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
