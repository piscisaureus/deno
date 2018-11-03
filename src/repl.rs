// Copyright 2018 the Deno authors. All rights reserved. MIT license.
extern crate rustyline;

use rustyline::error::ReadlineError::Interrupted;

use msg::ErrorKind;
use std::error::Error;

use deno_dir::DenoDir;
use errors::new as deno_error;
use errors::DenoResult;
use std::path::PathBuf;
use std::process::exit;

#[cfg(not(windows))]
use rustyline::Editor;

// Work around the issue that on Windows, `struct Editor` does not implement the
// `Send` trait, because it embeds a windows HANDLE which is a type alias for
// *mut c_void. This value isn't actually a pointer and there's nothing that
// can be mutated through it, so hack around it. TODO: a prettier solution.
#[cfg(windows)]
use std::ops::{Deref, DerefMut};

#[cfg(windows)]
struct Editor<T: rustyline::Helper> {
  inner: rustyline::Editor<T>,
}

#[cfg(windows)]
unsafe impl<T: rustyline::Helper> Send for Editor<T> {}

#[cfg(windows)]
impl<T: rustyline::Helper> Editor<T> {
  pub fn new() -> Editor<T> {
    Editor {
      inner: rustyline::Editor::<T>::new(),
    }
  }
}

#[cfg(windows)]
impl<T: rustyline::Helper> Deref for Editor<T> {
  type Target = rustyline::Editor<T>;

  fn deref(&self) -> &rustyline::Editor<T> {
    &self.inner
  }
}

#[cfg(windows)]
impl<T: rustyline::Helper> DerefMut for Editor<T> {
  fn deref_mut(&mut self) -> &mut rustyline::Editor<T> {
    &mut self.inner
  }
}

pub struct DenoRepl {
  pub name: String,
  editor: Editor<()>,
  history_file: PathBuf,
}

impl DenoRepl {
  pub fn new(name: &String, dir: &DenoDir) -> DenoRepl {
    let mut repl = DenoRepl {
      name: name.clone(),
      editor: Editor::<()>::new(),
      history_file: history_path(dir, name),
    };

    repl.load_history();
    repl
  }

  fn load_history(&mut self) -> () {
    debug!("Loading history file: {:?}", self.history_file);
    self
      .editor
      .load_history(&self.history_file.to_str().unwrap())
      .map_err(|e| debug!("Unable to load history file: {:?} {}", self.history_file, e))
      // ignore this error (e.g. it occurs on first load)
      .unwrap_or(())
  }

  fn save_history(&mut self) -> DenoResult<()> {
    self
      .editor
      .save_history(&self.history_file.to_str().unwrap())
      .map(|_| debug!("Saved history file to: {:?}", self.history_file))
      .map_err(|e| {
        eprintln!("Unable to save history file: {:?} {}", self.history_file, e);
        deno_error(ErrorKind::Other, e.description().to_string())
      })
  }

  pub fn readline(&mut self, prompt: &String) -> DenoResult<String> {
    self
      .editor
      .readline(&prompt)
      .map(|line| {
        self.editor.add_history_entry(line.as_ref());
        line
      }).map_err(|e| match e {
        Interrupted => {
          self.save_history().unwrap();
          exit(1)
        }
        e => deno_error(ErrorKind::Other, e.description().to_string()),
      })
  }
}

impl Drop for DenoRepl {
  fn drop(&mut self) {
    self.save_history().unwrap();
  }
}

fn history_path(dir: &DenoDir, name: &String) -> PathBuf {
  let mut p: PathBuf = dir.repl.clone();
  p.push(format!("{}_history.txt", name));
  p
}
