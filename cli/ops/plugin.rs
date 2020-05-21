// Copyright 2018-2020 the Deno authors. All rights reserved. MIT license.
use crate::fs::resolve_from_cwd;
use crate::op_error::OpError;
use crate::ops::dispatch_json::Deserialize;
use crate::ops::dispatch_json::JsonOp;
use crate::ops::dispatch_json::Value;
use crate::ops::json_op;
use crate::state::State;
use deno_core::plugin_api;
use deno_core::CoreIsolate;
use deno_core::Op;
use deno_core::OpAsyncFuture;
use deno_core::OpId;
use deno_core::Resource;
use deno_core::ResourceId;
use deno_core::ResourceTable;
use deno_core::ZeroCopyBuf;
use dlopen::symbor::Library;
use futures::prelude::*;
use std::cell::Ref;
use std::cell::RefMut;
use std::path::Path;
use std::pin::Pin;
use std::rc::Rc;
use std::task::Context;
use std::task::Poll;

pub fn init(i: &mut CoreIsolate, s: &State) {
  i.register_op(
    "op_open_plugin",
    s.core_op(json_op(s.stateful_op2(op_open_plugin))),
  );
}

#[derive(Deserialize)]
#[serde(rename_all = "camelCase")]
struct OpenPluginArgs {
  filename: String,
}

pub fn op_open_plugin(
  isolate: &mut CoreIsolate,
  state: &State,
  args: Value,
  _zero_copy: Option<ZeroCopyBuf>,
) -> Result<JsonOp, OpError> {
  state.check_unstable("Deno.openPlugin");
  let args: OpenPluginArgs = serde_json::from_value(args).unwrap();
  let filename = resolve_from_cwd(Path::new(&args.filename))?;

  state.check_plugin(&filename)?;

  debug!("Loading Plugin: {:#?}", filename);
  let plugin_lib = Library::open(filename)
    .map(Rc::new)
    .map_err(OpError::from)?;
  let plugin_resource = PluginResource::new(&plugin_lib);

  let mut resource_table = isolate.resource_table.borrow_mut();
  let rid = resource_table.add("plugin", Box::new(plugin_resource));
  let plugin_resource = resource_table.get::<PluginResource>(rid).unwrap();

  let deno_plugin_init = *unsafe {
    plugin_resource
      .lib
      .symbol::<plugin_api::InitFn>("deno_plugin_init")
  }
  .unwrap();
  drop(resource_table);

  let mut interface = PluginInterface::new(isolate, &plugin_lib);
  deno_plugin_init(&mut interface);

  Ok(JsonOp::Sync(json!(rid)))
}

/// A resource that stores a dynamically loaded plugin.
struct PluginResource {
  lib: Rc<Library>,
}

impl PluginResource {
  fn new(lib: &Rc<Library>) -> Self {
    Self { lib: lib.clone() }
  }
}

struct PluginInterface<'a> {
  isolate: &'a mut CoreIsolate,
  plugin_lib: &'a Rc<Library>,
}

impl<'a> PluginInterface<'a> {
  fn new(isolate: &'a mut CoreIsolate, plugin_lib: &'a Rc<Library>) -> Self {
    Self {
      isolate,
      plugin_lib,
    }
  }

  fn resource_table(&self) -> Ref<ResourceTable> {
    self.isolate.resource_table.borrow()
  }

  fn resource_table_mut(&mut self) -> RefMut<ResourceTable> {
    self.isolate.resource_table.borrow_mut()
  }
}

impl<'a> plugin_api::Interface for PluginInterface<'a> {
  /// Does the same as `core::Isolate::register_op()`, but additionally makes
  /// the registered op dispatcher, as well as the op futures created by it,
  /// keep reference to the plugin `Library` object, so that the plugin doesn't
  /// get unloaded before all its op registrations and the futures created by
  /// them are dropped.
  fn register_op(
    &mut self,
    name: &str,
    dispatch_op_fn: plugin_api::DispatchOpFn,
  ) -> OpId {
    let plugin_lib = self.plugin_lib.clone();
    self.isolate.op_registry.register(
      name,
      move |isolate, control, zero_copy| {
        let mut interface = PluginInterface::new(isolate, &plugin_lib);
        let op = dispatch_op_fn(&mut interface, control, zero_copy);
        match op {
          sync_op @ Op::Sync(..) => sync_op,
          Op::Async(fut) => {
            Op::Async(PluginOpAsyncFuture::new(&plugin_lib, fut))
          }
          Op::AsyncUnref(fut) => {
            Op::AsyncUnref(PluginOpAsyncFuture::new(&plugin_lib, fut))
          }
        }
      },
    )
  }

  fn resource_table(&mut self) -> &mut dyn plugin_api::ResourceTable {
    self
  }
}

struct PluginOpAsyncFuture {
  fut: Option<OpAsyncFuture>,
  _plugin_lib: Rc<Library>,
}

impl PluginOpAsyncFuture {
  fn new(plugin_lib: &Rc<Library>, fut: OpAsyncFuture) -> Pin<Box<Self>> {
    let wrapped_fut = Self {
      fut: Some(fut),
      _plugin_lib: plugin_lib.clone(),
    };
    Box::pin(wrapped_fut)
  }
}

impl Future for PluginOpAsyncFuture {
  type Output = <OpAsyncFuture as Future>::Output;
  fn poll(mut self: Pin<&mut Self>, ctx: &mut Context) -> Poll<Self::Output> {
    self.fut.as_mut().unwrap().poll_unpin(ctx)
  }
}

impl Drop for PluginOpAsyncFuture {
  fn drop(&mut self) {
    self.fut.take();
  }
}

/// A resource that has been inserted in the resource table by a dynamically
/// loaded plugin.
struct RefResource {
  inner: Box<dyn Resource>,
  _plugin_lib: Rc<Library>,
}

impl<'a> plugin_api::ResourceTable for PluginInterface<'a> {
  fn add(&mut self, name: &str, resource: Box<dyn Resource>) -> ResourceId {
    let ref_resource = RefResource {
      inner: resource,
      _plugin_lib: self.plugin_lib.clone(),
    };
    self.resource_table_mut().add(name, Box::new(ref_resource))
  }

  fn get(&self, rid: ResourceId) -> Option<Ref<dyn Resource>> {
    // Resources inserted by plugins are wrapped in a RefResource wrapper, so
    // we can ensure a reference to Rc<Library> is kept for as long as the
    // resource stays in the resource table.
    let table = self.resource_table();
    match table.get::<RefResource>(rid) {
      Some(_) => Some(Ref::map(table, |t| {
        &*t.get::<RefResource>(rid).unwrap().inner
      })),
      None => None,
    }
  }

  fn get_mut(&mut self, rid: ResourceId) -> Option<RefMut<dyn Resource>> {
    let mut table = self.resource_table_mut();
    match table.get_mut::<RefResource>(rid) {
      Some(_) => Some(RefMut::map(table, |t| {
        &mut *t.get_mut::<RefResource>(rid).unwrap().inner
      })),
      None => None,
    }
  }

  fn remove(&mut self, rid: ResourceId) -> Option<Box<dyn Resource>> {
    let mut table = self.resource_table_mut();
    match table.get_mut::<RefResource>(rid) {
      Some(_) => table.remove::<RefResource>(rid).map(|rc| rc.inner),
      None => None, // `rid` does not reference a RefResource, so leave it.
    }
  }
}
