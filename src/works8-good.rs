#![allow(unused_variables)]
#![allow(unused_mut)]
#![allow(dead_code)]

#[macro_use]
extern crate lazy_static;

extern crate owning_ref;

use owning_ref::OwningRefMut;
use std::marker::PhantomData;
use std::sync::Mutex;

struct Scope<'p, T>(PhantomData<&'p T>);

struct Enter<'a, T>(&'a T);

impl<'a, T> Enter<'a, T> {
  fn dispose(mut self) {}
}

impl<'a, 'p, T> Enter<'a, Scope<'p, T>> {
  fn new(scope: &'p mut Scope<'p, T>) -> Self {
    Enter(scope)
  }
}

impl<'p> Scope<'p, ()> {
  fn root() -> Self {
    unimplemented!()
  }
}

impl<'p, T> Scope<'p, T> {
  fn new2<'a>(e: &'p mut Enter<'a, T>) -> Self {
    Self(PhantomData)
  }

  fn borrow2<'a>(&'p mut self) -> Enter<'a, PhantomData<&'p T>> {
    Enter(&self.0)
  }

  fn dispose(mut self) {}
}

struct Local<'sc, T> {
  val: i32,
  owner: &'sc T,
}

impl<'sc, T> Local<'sc, T> {
  fn new2(e: &mut Enter<'sc, T>) -> Self {
    Self { val: 0, owner: e.0 }
  }

  fn live(&self) {}
}

fn main() {
  let mut l3;

  let mut s1_ = Scope::root();
  let mut s1 = Enter::new(&mut s1_);

  let mut l1a = Local::new2(&mut s1);
  let mut l1b = Local::new2(&mut s1);

  {
    let mut s2 = Scope::new2(&mut s1);
    let mut s2 = Enter::new(&mut s2);

    let mut l2a = Local::new2(&mut s2);
    let mut l2b = Local::new2(&mut s2);

    let mut _a = Scope::new2(&mut s1); // fail
    let mut _a = Local::new2(&mut s1); // fail

    {
      let mut s3_ = Scope::new2(&mut s2);

      let mut s3 = Enter::new(&mut s3_);
      l3 = Local::new2(&mut s3);

      let mut _a = Local::new2(&mut s1); // fail
      let mut _a = Local::new2(&mut s2); // fail

      l3.live();
      s3.dispose();
      s3_.dispose(); //Scope::dispose(s3);

      let mut l2c = Local::new2(&mut s2);
    }

    s2.dispose(); //Scope::dispose(s2); // Fail
    Local::new2(&mut s1); // fail
    l2a.live();
  }

  let mut l1c = Local::new2(&mut s1);

  l1a.live();

  s1_.dispose(); //Scope::dispose(s1); // fail
  l1a.live();

  //l3.live(); // fail
}
