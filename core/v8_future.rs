// Copyright 2018-2020 the Deno authors. All rights reserved. MIT license.

use rusty_v8 as v8;
use v8::scope::Entered;

use futures::future::Future;
use std::pin::Pin;
use std::task::Context;
use std::task::Poll;

pub type V8PollScope<'a> = Entered<
  'a,
  v8::ContextScope,
  Entered<'a, v8::HandleScope, Entered<'a, v8::Locker>>,
>;

pub trait V8Future {
  type Output;

  fn v8_isolate(&self) -> *const v8::Isolate;
  fn v8_context(&self) -> &v8::Global<v8::Context>;

  fn v8_poll(
    self: Pin<&mut Self>,
    scope: &mut V8PollScope<'_>,
    cx: &mut Context<'_>,
  ) -> Poll<Self::Output>;

  fn v8_poll_unpin(
    &mut self,
    scope: &mut V8PollScope<'_>,
    cx: &mut Context<'_>,
  ) -> Poll<Self::Output>
  where
    Self: Unpin,
  {
    Self::v8_poll(Pin::new(self), scope, cx)
  }
}

impl<T> Future for Fut<T>
where
  T: V8Future,
{
  type Output = T::Output;

  fn poll(self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Self::Output> {
    let fut = unsafe { self.map_unchecked_mut(|wrap| &mut wrap.0) };

    let isolate = fut.v8_isolate();
    let context = fut.v8_context();

    let mut locker = v8::Locker::new(unsafe { &*isolate });
    let locker = locker.enter();

    let mut handle_scope = v8::HandleScope::new(locker);
    let handle_scope = handle_scope.enter();

    let context = context.get(handle_scope).unwrap();
    let mut context_scope = v8::ContextScope::new(handle_scope, context);
    let context_scope = context_scope.enter();

    fut.v8_poll(context_scope, cx)
  }
}

// The `Fut` wrapper and `AsFut` traits are unfortunate, but they're necessary
// because Rust won't let us write `impl<T> Future for T where T: V8Future {}`.

#[derive(Deref, DerefMut)]
#[repr(transparent)]
pub struct Fut<T>(T);

pub trait AsFut<F>
where
  F: Future,
{
  fn as_fut(self) -> F;
}

impl<'a, T> AsFut<&'a mut Fut<T>> for &'a mut T
where
  Fut<T>: Future + Unpin,
{
  fn as_fut(self) -> &'a mut Fut<T> {
    unsafe { &mut *(self as *mut T as *mut Fut<T>) }
  }
}

impl<'a, T> AsFut<Pin<&'a mut Fut<T>>> for Pin<&'a mut T>
where
  Fut<T>: Future,
{
  fn as_fut(self: Pin<&'a mut T>) -> Pin<&'a mut Fut<T>> {
    unsafe {
      self.map_unchecked_mut(|pin| &mut *(pin as *mut T as *mut Fut<T>))
    }
  }
}
