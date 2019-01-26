use std::marker;
use std::mem::{forget, size_of};
use std::ops::{Add, BitAnd, Deref, DerefMut, Not, Sub};
use std::slice;
use std::sync::atomic::Ordering;
use std::sync::Arc;

extern crate integer_atomics;
use integer_atomics::AtomicI32;

trait Align<T> {
    fn align(self, to: T) -> Self;
    fn is_aligned(self, to: T) -> bool;
}

impl<T> Align<T> for T
where
    T: Copy
        + From<u8>
        + PartialEq
        + Add<Output = T>
        + Sub<Output = T>
        + BitAnd<Output = T>
        + Not<Output = T>,
{
    fn align(self, to: T) -> Self {
        let mask = to - 1.into();
        (self + mask) & !mask
    }

    fn is_aligned(self, to: T) -> bool {
        self & (to - 1.into()) == 0.into()
    }
}

#[derive(Clone, Copy, Debug, Default)]
pub struct MsgRingCounters {
    pub message: usize,
    pub acquire: usize,
    pub release: usize,
    pub spin: usize,
    pub wait: usize,
    pub wake: usize,
    pub wrap: usize,
}

#[derive(Clone, Copy)]
pub enum FillDirection {
    TopDown,
    BottomUp,
}

struct FrameAllocation;
#[allow(non_upper_case_globals)]
impl FrameAllocation {
    pub const Alignment: usize = 8;
    pub const HeaderByteLength: usize = 8;
}

struct FrameHeader;
#[allow(non_upper_case_globals)]
impl FrameHeader {
    // Using i32 since that's what's used on the JS side.
    pub const None: i32 = 0x00000000;
    pub const ByteLengthMask: i32 = 0x00ffffff;
    pub const EpochMask: i32 = 0x03000000;
    pub const EpochInitSender: i32 = 0x00000000;
    pub const EpochInitReceiver: i32 = 0x01000000;
    pub const EpochIncrementPass: i32 = 0x01000000;
    pub const EpochIncrementWrap: i32 = 0x02000000;
    pub const HasMessageFlag: i32 = 0x04000000;
    pub const HasWaitersFlag: i32 = 0x08000000;
}

enum PointerOwned {
    NotOwned,
    Owned(*mut u8),
}

impl Drop for PointerOwned {
    fn drop(&mut self) {
        if let PointerOwned::Owned(ptr) = self {
            unsafe { Box::from_raw(ptr) };
        }
    }
}

pub struct MsgRingBuffer {
    ptr: *mut u8,
    byte_length: usize,
    owned: Arc<PointerOwned>,
}

unsafe impl marker::Send for MsgRingBuffer {}

impl MsgRingBuffer {
    pub fn new(byte_length: usize) -> Self {
        assert!(byte_length > 0);
        assert!(byte_length.is_aligned(FrameAllocation::Alignment));
        let mut vec: Vec<u8> = Vec::new();
        vec.resize(byte_length, 0);
        let ptr = vec.as_mut_ptr() as *mut u8;
        forget(vec);
        Self {
            ptr,
            byte_length,
            owned: Arc::new(PointerOwned::Owned(ptr)),
        }
    }

    pub unsafe fn from_raw(ptr: *mut u8, byte_length: usize) -> Self {
        assert!(byte_length.is_aligned(FrameAllocation::Alignment as usize));
        Self {
            ptr,
            byte_length,
            owned: Arc::new(PointerOwned::NotOwned),
        }
    }

    unsafe fn dup(&mut self) -> Self {
        Self {
            ptr: self.ptr,
            byte_length: self.byte_length,
            owned: self.owned.clone(),
        }
    }

    pub fn byte_length(&self) -> usize {
        return self.byte_length;
    }

    unsafe fn borrow_slice<'a>(&'a self, offset: usize, byte_length: usize) -> &'a [u8] {
        assert!(offset + byte_length <= self.byte_length);
        std::slice::from_raw_parts(self.ptr, byte_length)
    }

    unsafe fn borrow_slice_mut<'a>(
        &'a mut self,
        offset: usize,
        byte_length: usize,
    ) -> &'a mut [u8] {
        assert!(offset + byte_length <= self.byte_length);
        slice::from_raw_parts_mut(self.ptr, byte_length)
    }
}

#[derive(Clone, Copy)]
pub struct MsgRingConfig {
    pub fill_direction: FillDirection,
    pub spin_count: u32,
    pub spin_yield_cpu_time: u32,
}

impl Default for MsgRingConfig {
    fn default() -> Self {
        Self {
            fill_direction: FillDirection::TopDown,
            spin_count: 100,
            spin_yield_cpu_time: 0, // Disabled.
        }
    }
}

// TODO: probably should use builder pattern.
pub struct MsgRing {
    buffer: MsgRingBuffer,
    config: MsgRingConfig,
}

impl MsgRing {
    pub fn new_with(buffer: MsgRingBuffer, config: MsgRingConfig) -> Self {
        Self { buffer, config }
    }

    pub fn new(buffer: MsgRingBuffer) -> Self {
        Self {
            buffer,
            config: Default::default(),
        }
    }

    pub fn split(mut self) -> (MsgRingSender, MsgRingReceiver) {
        let sender = MsgRingSender::new(unsafe { self.buffer.dup() }, self.config);
        let receiver = MsgRingReceiver::new(self.buffer, self.config);
        (sender, receiver)
    }
}

struct Window {
    pub config: MsgRingConfig,
    pub counters: MsgRingCounters,

    pub buffer: MsgRingBuffer,
    pub epoch: i32,

    // Head and tail position are in bytes, but always starting at zero and
    // not adjusted for buffer fill direction (see TypeScript implementation).
    pub tail_position: usize,
    pub head_position: usize,

    pub fill_direction_base_adjustment: isize,
    pub fill_direction_offset_adjustment: isize,
}

impl Window {
    pub fn new(buffer: MsgRingBuffer, config: MsgRingConfig, epoch: i32) -> Self {
        let (fill_direction_base_adjustment, fill_direction_offset_adjustment) =
            match config.fill_direction {
                FillDirection::TopDown => (0, 1),
                FillDirection::BottomUp => (1, -1),
            };
        let mut this = Self {
            buffer,
            config,
            counters: MsgRingCounters {
                ..Default::default()
            },
            epoch,
            head_position: 0,
            tail_position: 0,
            fill_direction_base_adjustment,
            fill_direction_offset_adjustment,
        };
        this.init();
        this
    }

    #[inline]
    pub fn buffer_byte_length(&self) -> usize {
        return self.buffer.byte_length();
    }

    #[inline]
    pub fn byte_length(&self) -> usize {
        self.head_position - self.tail_position
    }

    #[inline]
    fn is_at_end_of_buffer(&self) -> bool {
        self.head_position == self.buffer_byte_length()
    }

    #[inline]
    fn header_ptr(&mut self, position: usize) -> *mut i32 {
        let byte_offset = self.fill_direction_base_adjustment
            * (self.buffer_byte_length() - FrameAllocation::HeaderByteLength) as isize
            + self.fill_direction_offset_adjustment * position as isize;
        let slice = unsafe {
            self.buffer
                .borrow_slice_mut(byte_offset as usize, size_of::<i32>())
        };
        slice.as_ptr() as *mut i32
    }

    fn init(&mut self) -> () {
        let header_ptr = self.header_ptr(0);
        let header_slot = unsafe { &mut *(header_ptr as *mut AtomicI32) };
        let target = self.buffer.byte_length() as i32;
        header_slot.compare_and_swap(0, target, Ordering::AcqRel);
    }

    pub fn acquire_frame(&mut self, wait: bool) -> i32 {
        if self.is_at_end_of_buffer() {
            assert!(self.byte_length() == 0);

            self.epoch = (self.epoch + FrameHeader::EpochIncrementWrap) & FrameHeader::EpochMask;

            self.head_position = 0;
            self.tail_position = 0;
            self.counters.wrap += 1;
        }

        let header_ptr = self.header_ptr(self.head_position);
        let header_slot = unsafe { &mut *(header_ptr as *mut AtomicI32) };
        let mut header = *header_slot.get_mut();

        let mut spin_count_remaining = self.config.spin_count;
        let mut sleep = false;

        // Note that operator precendece in Rust is different than in C and
        // JavaScript (& has higher precedence than ==), so this is correct.
        let mut f = false;
        while header & FrameHeader::EpochMask != self.epoch {
            if !f {
                eprintln!(
                    "  p={} h={:x} h.ep={:x} ; s.ep={:x}",
                    self.head_position,
                    header,
                    header & FrameHeader::EpochMask,
                    self.epoch,
                );
                f = true;
            }

            if !wait {
                return FrameHeader::None;
            }

            if spin_count_remaining == 0 {
                let expect = header;
                let target = header | FrameHeader::HasWaitersFlag;
                header = header_slot.compare_and_swap(expect, target, Ordering::AcqRel);
                if expect != header {
                    continue;
                }
                header = target;
                sleep = true;
                self.counters.wait += 1;
            } else {
                spin_count_remaining -= 1;
                self.counters.spin += 1;
            }

            if sleep && false {
                // TODO
                //Atomics.wait(this.i32, headerI32Offset, header, futexWaitTime) !==
                //  "timed-out"
            } else {
                header = header_slot.load(Ordering::Acquire);
            }
        }
        eprintln!(
            "= p={} ; h={:x} h.ep={:x} ; s.ep={:x}",
            self.head_position,
            header,
            header & FrameHeader::EpochMask,
            self.epoch,
        );

        let byte_length = header & FrameHeader::ByteLengthMask;
        let byte_length = byte_length as usize;
        assert!(byte_length <= self.buffer_byte_length() - self.head_position);

        self.head_position += byte_length;
        self.counters.acquire += 1;

        return header;
    }

    pub fn release_frame(&mut self, byte_length: usize, flags: i32) -> () {
        assert!(byte_length >= FrameAllocation::HeaderByteLength);
        assert!(byte_length <= self.byte_length());

        let tail_epoch = self.epoch + FrameHeader::EpochIncrementPass;
        let new_header = byte_length as i32 | flags | tail_epoch;

        let header_ptr = self.header_ptr(self.tail_position);
        let header_slot = unsafe { &mut *(header_ptr as *mut integer_atomics::AtomicI32) };
        let old_header = header_slot.swap(new_header, Ordering::AcqRel);
        eprintln!(
            "<= p={}  h={:x} h.ep={:x}  self.ep={:x}  found.ep={:x}",
            self.tail_position,
            new_header,
            new_header & FrameHeader::EpochMask,
            self.epoch,
            old_header & FrameHeader::EpochMask,
        );

        if old_header & FrameHeader::HasWaitersFlag != 0 {
            // TODO
            // Atomics.wake(this.i32, headerI32Offset, 1);
            self.counters.wake += 1;
        }

        self.tail_position += byte_length;
        self.counters.release += 1;
    }

    fn get_message_byte_range(&self, frame_byte_length: usize) -> (usize, usize) {
        let message_byte_length = (frame_byte_length - FrameAllocation::HeaderByteLength) as isize;
        let message_byte_offset = self.fill_direction_base_adjustment
            * (self.buffer_byte_length() as isize - message_byte_length)
            + self.fill_direction_offset_adjustment
                * (self.tail_position + FrameAllocation::HeaderByteLength) as isize;
        (message_byte_length as usize, message_byte_offset as usize)
    }

    pub fn get_message_slice(&self, frame_byte_length: usize) -> &[u8] {
        let (byte_offset, byte_length) = self.get_message_byte_range(frame_byte_length);
        unsafe { self.buffer.borrow_slice(byte_offset, byte_length) }
    }

    pub fn get_message_slice_mut(&mut self, frame_byte_length: usize) -> &mut [u8] {
        let (byte_offset, byte_length) = self.get_message_byte_range(frame_byte_length);
        unsafe { self.buffer.borrow_slice_mut(byte_offset, byte_length) }
    }
}

pub struct MsgRingSender {
    window: Window,
}

impl MsgRingSender {
    pub fn new(buffer: MsgRingBuffer, config: MsgRingConfig) -> Self {
        Self {
            window: Window::new(buffer, config, FrameHeader::EpochInitSender),
        }
    }

    pub fn compose<'msg>(&'msg mut self, byte_length: usize) -> Send<'msg> {
        Send::new(&mut self.window, byte_length)
    }

    pub fn counters(&self) -> MsgRingCounters {
        self.window.counters
    }
}

pub struct Send<'msg> {
    window: &'msg mut Window,
    allocation_byte_length: usize,
}

impl<'msg> Send<'msg> {
    fn new(window: &'msg mut Window, message_byte_length: usize) -> Self {
        let mut this = Self {
            window,
            allocation_byte_length: 0,
        };
        this.allocate(message_byte_length);
        this
    }

    pub fn resize(&mut self, message_byte_length: usize) {
        self.allocate(message_byte_length)
    }

    pub fn send(self) -> () {
        self.window.counters.message += 1;
        eprintln!("alloca = {}", self.allocation_byte_length);
        self.window
            .release_frame(self.allocation_byte_length, FrameHeader::HasMessageFlag);
        eprintln!(
            "alloca={} wnd={} tail={} head={}",
            self.allocation_byte_length,
            self.window.byte_length(),
            self.window.tail_position,
            self.window.head_position
        );
    }

    pub fn dispose(self) -> () {}

    fn allocate(&mut self, byte_length: usize) {
        self.allocation_byte_length = FrameAllocation::HeaderByteLength as usize
            + byte_length.align(FrameAllocation::Alignment as usize);
        assert!(self.allocation_byte_length <= FrameHeader::ByteLengthMask as usize);
        while self.window.byte_length() < self.allocation_byte_length {
            if self.window.is_at_end_of_buffer() && self.window.byte_length() > 0 {
                self.window
                    .release_frame(self.window.byte_length(), FrameHeader::None);
            }
            self.window.acquire_frame(true);
        }
    }
}

impl<'msg> Deref for Send<'msg> {
    type Target = [u8];

    fn deref(&self) -> &[u8] {
        self.window.get_message_slice(self.allocation_byte_length)
    }
}

impl<'msg> DerefMut for Send<'msg> {
    fn deref_mut(&mut self) -> &mut [u8] {
        self.window
            .get_message_slice_mut(self.allocation_byte_length)
    }
}

pub struct MsgRingReceiver {
    window: Window,
}

impl MsgRingReceiver {
    pub fn new(buffer: MsgRingBuffer, config: MsgRingConfig) -> Self {
        Self {
            window: Window::new(buffer, config, FrameHeader::EpochInitReceiver),
        }
    }

    pub fn receive<'msg>(&'msg mut self) -> Receive<'msg> {
        let r = Receive::new(&mut self.window);
        r
    }

    pub fn counters(&self) -> MsgRingCounters {
        self.window.counters
    }
}

pub struct Receive<'msg: 'msg> {
    window: &'msg mut Window,
}

impl<'msg> Receive<'msg> {
    fn new(window: &'msg mut Window) -> Self {
        let mut this = Self { window };
        this.acquire();
        this
    }

    fn acquire(&mut self) -> () {
        // Bug: what happens when previous frame not released?
        while self.window.acquire_frame(true) & FrameHeader::HasMessageFlag == 0 {
            self.window
                .release_frame(self.window.byte_length(), FrameHeader::None);
        }
        self.window.counters.message += 1;
    }

    fn release(&mut self) -> () {
        self.window
            .release_frame(self.window.byte_length(), FrameHeader::None);
    }

    pub fn dispose(mut self) -> () {
        self.release()
    }
}

impl<'msg> Deref for Receive<'msg> {
    type Target = [u8];

    fn deref(&self) -> &[u8] {
        self.window.get_message_slice(self.window.byte_length())
    }
}

//impl<'msg> Drop for Receive<'msg> {
//    fn drop(&mut self) -> () {
//        //self.release();
//    }
//}

#[cfg(test)]
#[macro_use]
extern crate lazy_static;

#[cfg(test)]
mod test {
    use super::{MsgRing, MsgRingBuffer};
    use std::sync::{Mutex, MutexGuard};
    use std::thread;
    use std::time::{Duration, Instant};

    const ROUNDS: usize = 10;
    const PER_ROUND: usize = 1e7 as usize;

    #[test] // TODO: use #[bench].
    fn uni_flow_benchmark() {
        let _guard = unparallelize_test();

        let buffer = MsgRingBuffer::new(1024);
        let ring = MsgRing::new(buffer);
        let (mut sender, mut receiver) = ring.split();

        let thread1 = thread::spawn(move || {
            benchmark_loop("sender", &mut sender, |sender| {
                let mut send = sender.compose(32);
                //send[1] = 2;
                send.send();
                eprintln!("S {:?}", sender.counters());
            });
        });

        let thread2 = thread::spawn(move || {
            benchmark_loop("receiver", &mut receiver, |receiver| {
                let m = receiver.receive();
                m.dispose();
                eprintln!("R {:?}", receiver.counters());
            });
        });

        thread1.join().unwrap();
        thread2.join().unwrap();
    }

    #[test] // TODO: use #[bench]
    fn ping_pong_benchmark() {
        let _guard = unparallelize_test();

        let (mut sender1, mut receiver1) = MsgRing::new(MsgRingBuffer::new(10240)).split();
        let (mut sender2, mut receiver2) = MsgRing::new(MsgRingBuffer::new(10240)).split();

        let thread1 = thread::spawn(move || {
            benchmark_loop(
                "send..recv",
                &mut (&mut sender1, &mut receiver2),
                |(sender, receiver)| {
                    sender.compose(32).send();
                    receiver.receive();
                },
            );
        });

        let thread2 = thread::spawn(move || {
            benchmark_loop(
                "recv..send",
                &mut (&mut sender2, &mut receiver1),
                |(sender, receiver)| {
                    receiver.receive();
                    sender.compose(32).send();
                },
            );
        });

        thread1.join().unwrap();
        thread2.join().unwrap();
    }

    fn unparallelize_test() -> MutexGuard<'static, ()> {
        lazy_static! {
            static ref m: Mutex<()> = Mutex::new(());
        };
        m.lock().unwrap()
    }

    fn benchmark_loop<A, F: Fn(&mut A) -> ()>(name: &str, a: &mut A, f: F) -> () {
        let tid = thread::current().id();

        for round in 0..ROUNDS {
            let start_time = Instant::now();

            for _ in 0..PER_ROUND {
                f(a);
            }

            let elapsed_time: Duration = Instant::now() - start_time;
            let elapsed_time = elapsed_time.as_millis() as f64 / 1000f64;
            let rate = (PER_ROUND as f64 / elapsed_time) as u64;
            eprintln!(
                "round {}, {:?}, {}, count: {}, rate: {} s\u{207b}\u{b9}",
                round, tid, name, PER_ROUND, rate
            );
        }
    }
}
