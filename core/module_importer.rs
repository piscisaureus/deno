use std::borrow::Borrow;
use std::collections::HashMap;
use std::collections::HashSet;
use std::future::Future;
use std::hash::Hash;
use std::hash::Hasher;
use std::pin::Pin;
use std::rc::Rc;

use futures::future::Shared;
use futures::future::TryFuture;
use futures::FutureExt;
use futures::TryFutureExt;
use rusty_v8 as v8;
use url::Url;

use crate::modules::ModuleSource as LegacyModuleSource;
use crate::ErrBox;
use crate::ModuleLoader as ModuleFetcher;
use crate::ModuleSpecifier;

pub struct Module {
  // URL after resolving the import specifier to an absolute URL, but without
  // taking into any HTTP redirects.
  resolved_url: Url,
  source:
    Shared<Pin<Box<dyn Future<Output = Rc<Result<ModuleSource, ErrBox>>>>>>,
}

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

pub struct ModuleSource {
  // URL that the source was actually loaded from, according to the loader. It
  // might differ from the specified URL for various reasons, e.g. because
  // an HTTP redirect happened while fetching from the specified URL.Future
  // If this module's source code contains import statements that specify
  // relative URLs, the fetched URL will be used as the basis for their
  // resolution.
  fetched_url: Url,
  // JavaScript source code that is compiled by V8.
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

pub struct ModuleImporter {
  fetcher: Rc<dyn ModuleFetcher>,
  modules: HashSet<Module>,
}

impl ModuleImporter {
  pub fn new(fetcher: Rc<dyn ModuleFetcher>) -> Self {
    Self {
      fetcher,
      modules: HashSet::new(),
    }
  }

  // The `is_dyn_import` flag is forwarded to the module loader if the module's
  // source hasn't been loaded yet. If the module already exists in the module
  // set, it is ignored.
  pub fn get(&mut self, resolved_url: &Url, is_dyn_import: bool) -> &Module {
    // Note: future versions of Rust will likely implement a method like
    // `get_or_insert_with()` or `get_or_insert_owned()` on HashSet. It would
    // be more efficient to use these when they become available.
    if !self.modules.contains(resolved_url) {
      let fetcher = self.fetcher.clone();
      let module_specifier = resolved_url.clone().into();
      let module = Module {
        resolved_url: resolved_url.clone(),
        source: async move {
          Rc::new(
            fetcher
              .load(&module_specifier, None, is_dyn_import)
              .map_ok(ModuleSource::from)
              .await,
          )
        }
        .boxed_local()
        .shared(),
      };
      self.modules.insert(module);
    }

    self.modules.get(resolved_url).unwrap()
  }
}
