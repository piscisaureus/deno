use std::borrow::Borrow;
use std::cell::Ref;
use std::cell::RefCell;
use std::cell::RefMut;
use std::collections::HashSet;
use std::future::Future;
use std::hash::Hash;
use std::hash::Hasher;
use std::pin::Pin;
use std::rc::Rc;

use futures::future::Shared;
use futures::stream::FuturesUnordered;
use futures::FutureExt;
use futures::StreamExt;
use futures::TryFutureExt;
use rusty_v8 as v8;
use url::Url;

use crate::bindings::module_origin;
use crate::modules::ModuleSource as LegacyModuleSource;
use crate::ErrBox;
use crate::ModuleLoader;

pub enum ImportError {
  Rust(ErrBox),
  JS(v8::Global<v8::Value>),
}

pub type ImportResult<T> = Result<Rc<T>, Rc<ImportError>>;

#[derive(Clone)]
pub struct Module {
  // URL after resolving the import specifier to an absolute URL, but without
  // taking into any HTTP redirects.
  resolved_url: Url,
  source: ModuleSourceFuture,
  // Future that resolves to the global v8::Module handle of the module after
  // compiling the source code. This future becomes ready after the module
  // has just been compiled; it may not be instantiated or evaluated yet.
  handle: ModuleHandleFuture,
  // Future that resolves to a Vec<Url> containing the URLs of dependencies
  // imported by this module.
  deps_urls: ModuleDepsUrlsFuture,
  // Future that resolves when the source for all dependencies has been fetched
  // and compiled, so that their v8::Module handle is in the cache.
  deps_compiled_recursively: ModuleDepsCompiledRecursivelyFuture,
}

type ModuleSourceFuture =
  Shared<Pin<Box<dyn Future<Output = ImportResult<ModuleSource>>>>>;

type ModuleHandleFuture =
  Shared<Pin<Box<dyn Future<Output = ImportResult<v8::Global<v8::Module>>>>>>;

type ModuleDepsUrlsFuture =
  Shared<Pin<Box<dyn Future<Output = ImportResult<Vec<Url>>>>>>;

type ModuleDepsCompiledRecursivelyFuture =
  Shared<Pin<Box<dyn Future<Output = Result<(), Rc<ImportError>>>>>>;

impl Borrow<Url> for Module {
  fn borrow(&self) -> &Url {
    &self.resolved_url
  }
}

impl Eq for Module {}

impl PartialEq for Module {
  fn eq(&self, other: &Self) -> bool {
    self.resolved_url == other.resolved_url
  }
}

impl Hash for Module {
  fn hash<H: Hasher>(&self, state: &mut H) {
    self.resolved_url.hash(state)
  }
}

#[derive(Clone)]
pub struct ModuleSource {
  // URL that the source was actually loaded from, according to the loader. It
  // might differ from the specified URL for various reasons, e.g. because
  // an HTTP redirect happened while fetching from the specified URL.Future
  // If this module's source code contains import statements that specify
  // relative URLs, the fetched URL will be used as the basis for their
  // resolution.
  fetched_url: Url,
  // JavaScript source code that will be handle by V8.
  js_source_code: String,
}

impl From<LegacyModuleSource> for ModuleSource {
  fn from(v: LegacyModuleSource) -> Self {
    Self {
      fetched_url: Url::parse(&v.module_url_found).unwrap(),
      js_source_code: v.code,
    }
  }
}

pub struct ModuleImporterInner {
  loader: Rc<dyn ModuleLoader>,
  modules: HashSet<Module>,
}

#[derive(Clone)]
pub struct ModuleImporter(Rc<RefCell<ModuleImporterInner>>);

impl ModuleImporter {
  pub fn new(loader: Rc<dyn ModuleLoader>) -> Self {
    Self(Rc::new(RefCell::new(ModuleImporterInner {
      loader,
      modules: HashSet::new(),
    })))
  }

  // The `is_dyn_import` flag is forwarded to the module loader if the module's
  // source hasn't been loaded yet. If the module already exists in the module
  // set, it is ignored.
  pub fn get<'a>(
    &'a self,
    resolved_url: &Url,
    is_dyn_import: bool,
  ) -> Ref<'a, Module> {
    // Note: future versions of Rust will likely implement a method like
    // `get_or_insert_with()` or `get_or_insert_owned()` on HashSet. It would
    // be more efficient to use these when they become available.
    if self.modules().contains(resolved_url) {
      let module = self.new_module(resolved_url, is_dyn_import);
      self.modules().insert(module);
    }

    Ref::map(RefCell::borrow(&self.0), |inner| {
      inner.modules.get(resolved_url).unwrap()
    })
  }

  pub fn new_module(&self, resolved_url: &Url, is_dyn_import: bool) -> Module {
    let source = self.new_module_source_future(resolved_url, is_dyn_import);
    let handle = self.new_module_handle_future(&source);
    let deps_urls = self.new_module_deps_urls_future(&source, &handle);
    let deps_compiled_recursively =
      self.new_module_deps_compiled_recursively_future(&deps_urls);

    Module {
      resolved_url: resolved_url.clone(),
      source,
      handle,
      deps_urls,
      deps_compiled_recursively,
    }
  }

  fn loader(&self) -> Ref<Rc<dyn ModuleLoader>> {
    Ref::map(RefCell::borrow(&self.0), |inner| &inner.loader)
  }

  fn modules(&self) -> RefMut<HashSet<Module>> {
    RefMut::map(RefCell::borrow_mut(&self.0), |inner| &mut inner.modules)
  }

  fn new_module_source_future(
    &self,
    resolved_url: &Url,
    is_dyn_import: bool,
  ) -> ModuleSourceFuture {
    let module_specifier = resolved_url.clone().into();

    self
      .loader()
      .load(&module_specifier, None, is_dyn_import)
      .map_ok(ModuleSource::from)
      .map_ok(Rc::new)
      .map_err(ImportError::Rust)
      .map_err(Rc::new)
      .boxed_local()
      .shared()
  }

  fn new_module_handle_future(
    &self,
    source: &ModuleSourceFuture,
  ) -> ModuleHandleFuture {
    let cache = self.clone();
    let source = source.clone();

    async move {
      let source = source.await?;

      #[allow(clippy::transmute_ptr_to_ptr)]
      #[allow(mutable_transmutes)]
      let isolate: &mut v8::OwnedIsolate =
        unsafe { std::mem::transmute(cache.loader().get_isolate()) };

      let mut hs = v8::HandleScope::new(isolate);
      let scope = hs.enter();

      let resource_name =
        v8::String::new(scope, source.fetched_url.as_str()).unwrap();
      let js_source_code =
        v8::String::new(scope, &source.js_source_code).unwrap();

      let origin = module_origin(scope, resource_name);
      let source = v8::script_compiler::Source::new(js_source_code, &origin);

      let mut try_catch = v8::TryCatch::new(scope);
      let tc = try_catch.enter();

      v8::script_compiler::compile_module(scope, source)
        .map(|module| v8::Global::new_from(scope, module))
        .map(Rc::new)
        .ok_or_else(|| tc.exception().unwrap())
        .map_err(|exception| v8::Global::new_from(scope, exception))
        .map_err(ImportError::JS)
        .map_err(Rc::new)
    }
    .boxed_local()
    .shared()
  }

  fn new_module_deps_urls_future(
    &self,
    source: &ModuleSourceFuture,
    handle: &ModuleHandleFuture,
  ) -> ModuleDepsUrlsFuture {
    let cache = self.clone();
    let source = source.clone();
    let handle = handle.clone();

    async move {
      let handle = handle.await?;
      let source = source.await?;

      #[allow(clippy::transmute_ptr_to_ptr)]
      #[allow(mutable_transmutes)]
      let isolate: &mut v8::OwnedIsolate =
        unsafe { std::mem::transmute(cache.loader().get_isolate()) };

      let mut hs = v8::HandleScope::new(isolate);
      let scope = hs.enter();

      let handle = handle.get(scope).unwrap();
      let referrer = source.fetched_url.as_str();

      (0..handle.get_module_requests_length())
        .map(|i| {
          let specifier =
            handle.get_module_request(i).to_rust_string_lossy(scope);
          let url: Url =
            cache.loader().resolve(&specifier, referrer, false)?.into();
          Ok(url)
        })
        .collect::<Result<Vec<Url>, ErrBox>>()
        .map(Rc::new)
        .map_err(ImportError::Rust)
        .map_err(Rc::new)
    }
    .boxed_local()
    .shared()
  }

  fn new_module_deps_compiled_recursively_future(
    &self,
    deps_urls: &ModuleDepsUrlsFuture,
  ) -> ModuleDepsCompiledRecursivelyFuture {
    let cache = self.clone();
    deps_urls
      .clone()
      .and_then(move |dep_urls| {
        dep_urls
          .iter()
          .map(|dep_url| {
            cache
              .modules()
              .get(dep_url)
              .unwrap()
              .deps_compiled_recursively
              .clone()
          })
          .collect::<FuturesUnordered<_>>()
          .fold(Ok(()), |acc, r| async move { acc.and(r) })
      })
      .boxed_local()
      .shared()
  }
}
