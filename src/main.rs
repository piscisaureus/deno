use std::any::{Any, TypeId};
use std::convert::From;
use std::error::Error;

#[allow(dead_code)]
pub type BoxError = Box<dyn AnyError>;
#[allow(dead_code)]
pub type DynError<'a> = &'a dyn AnyError;

pub trait AnyError: Error + Any + Send + 'static {}
impl<T> AnyError for T where T: Error + Any  + Send + Sized + 'static {}

pub trait SharedError: AnyError + Sync {}
impl<T> SharedError for T where T: AnyError + Sync {}

impl<T> From<T> for Box<dyn AnyError>
where
  T: AnyError + Sized,
{
  fn from(error: T) -> Self {
    Box::new(error)
  }
}

use std::ops::Deref;

pub trait DowncastError<S> where Self: Sized + Deref + Into<Box<S>>, <Self as Deref>::Target: 'static, S: AnyError + ?Sized {
  fn into_raw(b: Self) -> *mut 
  fn downcast<T>(self) -> Result<Box<T>, Self>
  where
    T: AnyError + Sized,
  {
    if Any::type_id(&*self) == TypeId::of::<T>() {
      let target = Box::into_raw(self.into()) as *mut T;
      let target = unsafe { Box::from_raw(target) };
      Ok(target)
    } else {
      Err(self)
    }
  }
}

impl DowncastError<dyn AnyError> for Box<dyn AnyError> {}
impl DowncastError<dyn SharedError> for Box<dyn SharedError> {}

/*
impl DowncastError for Box<dyn AnyError> {
  fn downcast<T>(self) -> Result<Box<T>, Self>
  where
    T: AnyError + Sized,
  {
    if Any::type_id(&*self) == TypeId::of::<T>() {
      let target = Box::into_raw(self) as *mut T;
      let target = unsafe { Box::from_raw(target) };
      Ok(target)
    } else {
      Err(self)
    }
  }
}*/

pub trait DowncastErrorRef: Sized {
  fn downcast_ref<T>(&self) -> Option<&T>
  where
    T: AnyError + Sized;
}

impl DowncastErrorRef for Box<dyn AnyError> {
  fn downcast_ref<T>(&self) -> Option<&T>
  where
    T: AnyError + Sized,
  {
    if Any::type_id(&**self) == TypeId::of::<T>() {
      let target = self as *const Self as *const &T;
      let target = unsafe { &(*target as &T) };
      Some(target)
    } else {
      None
    }
  }
}

impl DowncastErrorRef for &dyn AnyError {
  fn downcast_ref<T>(&self) -> Option<&T>
  where
    T: AnyError + Sized,
  {
    if Any::type_id(&**self) == TypeId::of::<T>() {
      let target = self as *const Self as *const &T;
      let target = unsafe { &(*target as &T) };
      Some(target)
    } else {
      None
    }
  }
}

fn main() {
    testing::test()
}

//#[cfg(never)]
#[allow(dead_code)]
mod testing {
  use super::*;
  use std::fmt::*;
  use std::fmt;
  use std::error::Error;

  #[derive(Debug, Default)]
  struct SomeError {}
  impl Display for SomeError {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
      write!(f, "{:?}", self)
    }
  }
  impl Error for SomeError {}

  #[derive(Debug, Default)]
  struct JSError {
    _v: i32,
  }
  impl Display for JSError {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
      write!(f, "{:?}", self)
    }
  }
  impl Error for JSError {}

  #[derive(Debug)]
  struct NoSyncError {
      _g: *mut u32
  }
  unsafe impl Send for NoSyncError {}
  impl Default for NoSyncError {
      fn default() -> Self {
          Self { _g: std::ptr::null_mut() }
      }
  }
  impl Display for NoSyncError     {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
      write!(f, "{:?}", self)
    }
  }
  impl Error for NoSyncError {}

  fn test_downcast_any<S: Default + Debug + SharedError, T: Default + Debug + AnyError>() {
      let s: S = Default::default();
      let s_: S = Default::default();
      let s__: S = Default::default();
      let bx: Box<dyn SharedError> = Box::new(s);
      let bx_: Box<dyn SharedError> = Box::new(s_);
      let t = bx.downcast::<T>();
      let desc = match t {
          Ok(_) =>  "YES",
          Err(_) =>  "-  "
      };
      let t_ref: T = Default::default();
      eprintln!("{} In {:?}  =>  Boxed {:?}  =>  Cast {:?}", desc, &s__, &bx_, &t);
  }

  pub fn test() {
    test_downcast_any::<SomeError, SomeError>();
    test_downcast_any::<SomeError, JSError>();
    test_downcast_any::<SomeError, NoSyncError>();
    test_downcast_any::<JSError, SomeError>();
    test_downcast_any::<JSError, JSError>();
    test_downcast_any::<JSError, NoSyncError>();
    //test_downcast_any::<NoSyncError, SomeError>();
    //test_downcast_any::<NoSyncError, JSError>();
    //test_downcast_any::<NoSyncError, NoSyncError>();
  }
}
