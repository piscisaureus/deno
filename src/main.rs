extern crate integer_atomics;

use integer_atomics::AtomicI32;
use std::ops::{Deref, DerefMut};
use std::sync::atomic::Ordering;

#[derive(Clone, Copy, Default)]
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
    pub const Alignment: i32 = 8;
    pub const HeaderByteLength: i32 = 8;

    pub fn align<T: From<usize> + Into<usize>>(value: T) -> T {
        let alignment_mask = Self::Alignment as usize - 1;
        let aligned_value = (value.into() + alignment_mask) & !alignment_mask;
        aligned_value.into()
    }
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
            spin_count: 10,
            spin_yield_cpu_time: 0, // Disabled.
        }
    }
}

#[derive(Default)]
struct Window<'wnd> {
    pub config: MsgRingConfig,
    pub counters: MsgRingCounters,

    pub buffer: &'wnd [u8],
    pub epoch: i32,

    // Head and tail position are in bytes, but always starting at zero and
    // not adjusted for buffer fill direction (see TypeScript implementation).
    pub tail_position: i32,
    pub head_position: i32,

    pub fill_direction_base_adjustment: i32,
    pub fill_direction_offset_adjustment: i32,
}

impl<'wnd> Window<'wnd> {
    pub fn new(buffer: &'wnd [u8], config: MsgRingConfig, epoch: i32) -> Self {
        let (fill_direction_base_adjustment, fill_direction_offset_adjustment) =
            match config.fill_direction {
                FillDirection::TopDown => (0, 1),
                FillDirection::BottomUp => (1, -1),
            };
        let mut this = Self {
            config,
            buffer,
            epoch,
            fill_direction_base_adjustment,
            fill_direction_offset_adjustment,
            ..Default::default()
        };
        this.init();
        this
    }

    #[inline]
    pub fn buffer_byte_length(&self) -> i32 {
        debug_assert!(self.buffer.len() <= std::i32::MAX as usize);
        return self.buffer.len() as i32;
    }

    #[inline]
    pub fn byte_length(&self) -> i32 {
        self.head_position - self.tail_position
    }

    #[inline]
    fn is_at_end_of_buffer(&self) -> bool {
        self.head_position == self.buffer_byte_length()
    }

    #[inline]
    fn header_ptr(&self, position: i32) -> *mut i32 {
        let byte_offset = self.fill_direction_base_adjustment
            * (self.buffer_byte_length() - FrameAllocation::HeaderByteLength)
            + self.fill_direction_offset_adjustment * position;
        self.buffer[byte_offset as usize..].as_ptr() as *mut i32
    }

    fn init(&mut self) -> () {
        let header_ptr = self.header_ptr(0);
        let header_slot = unsafe { &mut *(header_ptr as *mut AtomicI32) };
        let target: i32 = self.buffer_byte_length();
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
        while header & FrameHeader::EpochMask != self.epoch {
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

        let byte_length = header & FrameHeader::ByteLengthMask;
        assert!(byte_length <= self.buffer_byte_length() - self.head_position);

        self.head_position += byte_length;
        self.counters.acquire += 1;

        return header;
    }

    pub fn release_frame(&mut self, byte_length: i32, flags: i32) -> () {
        assert!(byte_length >= FrameAllocation::HeaderByteLength);
        assert!(byte_length <= self.byte_length());

        let tail_epoch = self.epoch + FrameHeader::EpochIncrementPass;
        let new_header = byte_length | flags | tail_epoch;

        let header_ptr = self.header_ptr(self.tail_position);
        let header_slot = unsafe { &mut *(header_ptr as *mut integer_atomics::AtomicI32) };
        let old_header = header_slot.swap(new_header, Ordering::AcqRel);

        if old_header & FrameHeader::HasWaitersFlag != 0 {
            // TODO
            // Atomics.wake(this.i32, headerI32Offset, 1);
            self.counters.wake += 1;
        }

        self.tail_position += byte_length;
    }

    pub fn get_message_slice_impl(&self, frame_byte_length: i32) -> &mut [u8] {
        let message_byte_length = frame_byte_length - FrameAllocation::HeaderByteLength;
        let message_byte_offset = self.fill_direction_base_adjustment
            * (self.buffer_byte_length() - message_byte_length)
            + self.fill_direction_offset_adjustment
                * (self.tail_position + FrameAllocation::HeaderByteLength);
        let message_end = message_byte_offset + message_byte_length;
        let message_frame = &self.buffer[message_byte_offset as usize..message_end as usize];
        unsafe {
            // Although our synchronization mechanism ensures that there can
            // never be more than one reference to the returned message slice,
            // this transmute isn't pretty and appears to be un-idiomatic.
            // TODO: use more idiomatic rust.
            #[allow(mutable_transmutes)]
            std::mem::transmute::<&[u8], &mut [u8]>(message_frame)
        }
    }

    pub fn get_message_slice(&self, frame_byte_length: i32) -> &[u8] {
        self.get_message_slice_impl(frame_byte_length)
    }

    pub fn get_message_slice_mut(&mut self, frame_byte_length: i32) -> &mut [u8] {
        self.get_message_slice_impl(frame_byte_length)
    }
}

pub struct MsgRingSender<'wnd> {
    window: Window<'wnd>,
}

impl<'wnd> MsgRingSender<'wnd> {
    pub fn new(buffer: &'wnd [u8], config: MsgRingConfig) -> Self {
        Self {
            window: Window::new(buffer, config, FrameHeader::EpochInitSender),
        }
    }

    pub fn compose<'msg>(&'msg mut self, byte_length: usize) -> Send<'msg, 'wnd> {
        Send::new(&mut self.window, byte_length)
    }
}

pub struct Send<'msg, 'wnd: 'msg> {
    window: &'msg mut Window<'wnd>,
    allocation_byte_length: i32,
}

impl<'msg, 'wnd> Send<'msg, 'wnd> {
    fn new(window: &'msg mut Window<'wnd>, message_byte_length: usize) -> Self {
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
        self.window
            .release_frame(self.allocation_byte_length, FrameHeader::HasMessageFlag);
    }

    pub fn dispose(self) -> () {}

    fn allocate(&mut self, byte_length: usize) {
        let allocation_byte_length =
            FrameAllocation::HeaderByteLength as usize + FrameAllocation::align(byte_length);
        assert!(allocation_byte_length <= FrameHeader::ByteLengthMask as usize);
        self.allocation_byte_length = allocation_byte_length as i32;
        while self.window.byte_length() < self.allocation_byte_length {
            if self.window.is_at_end_of_buffer() && self.window.byte_length() > 0 {
                self.window
                    .release_frame(self.window.byte_length(), FrameHeader::None);
            }
            self.window.acquire_frame(true);
        }
    }
}

impl<'msg, 'wnd> Deref for Send<'msg, 'wnd> {
    type Target = [u8];

    fn deref(&self) -> &[u8] {
        self.window.get_message_slice(self.allocation_byte_length)
    }
}

impl<'msg, 'wnd> DerefMut for Send<'msg, 'wnd> {
    fn deref_mut(&mut self) -> &mut [u8] {
        self.window
            .get_message_slice_mut(self.allocation_byte_length)
    }
}

pub struct MsgRingReceiver<'wnd> {
    window: Window<'wnd>,
}

impl<'wnd> MsgRingReceiver<'wnd> {
    pub fn new(buffer: &'wnd [u8], config: MsgRingConfig) -> Self {
        Self {
            window: Window::new(buffer, config, FrameHeader::EpochInitReceiver),
        }
    }

    pub fn receive<'msg>(&'msg mut self) -> Receive<'msg, 'wnd> {
        Receive::new(&mut self.window)
    }
}

pub struct Receive<'msg, 'wnd: 'msg> {
    window: &'msg mut Window<'wnd>,
}

impl<'msg, 'wnd> Receive<'msg, 'wnd> {
    fn new(window: &'msg mut Window<'wnd>) -> Self {
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
    }

    fn release(&mut self) -> () {
        self.window
            .release_frame(self.window.byte_length(), FrameHeader::None);
    }

    pub fn dispose(mut self) -> () {
        self.release()
    }
}

impl<'msg, 'wnd> Deref for Receive<'msg, 'wnd> {
    type Target = [u8];

    fn deref(&self) -> &[u8] {
        self.window.get_message_slice(self.window.byte_length())
    }
}

impl<'msg, 'wnd> Drop for Receive<'msg, 'wnd> {
    fn drop(&mut self) -> () {
        self.release();
    }
}

#[cfg(test)]
#[macro_use]
extern crate lazy_static;

#[cfg(test)]
mod test {
    use super::{MsgRingConfig, MsgRingReceiver, MsgRingSender};
    use std::sync::{Mutex, MutexGuard};
    use std::thread;
    use std::time::{Duration, Instant};

    const ROUNDS: usize = 10;
    const PER_ROUND: usize = 1e7 as usize;

    #[test] // TODO: use #[bench].
    fn uni_flow_benchmark() {
        let _guard = unparallelize_test();

        static mut BUF: [u8; 10240] = [0; 10240];

        let config = MsgRingConfig {
            ..Default::default()
        };

        let th1 = thread::spawn(move || {
            let mut mrs = MsgRingSender::new(unsafe { &BUF }, config);
            benchmark_loop("sender", &mut mrs, |mrs| {
                let mut send = mrs.compose(32);
                send.send();
            });
        });

        let th2 = thread::spawn(move || {
            let mut mrr = MsgRingReceiver::new(unsafe { &BUF }, config);
            benchmark_loop("receiver", &mut mrr, |mrr| {
                mrr.receive();
            });
        });

        th1.join().unwrap();
        th2.join().unwrap();
    }

    #[test] // TODO: use #[bench]
    fn ping_pong_benchmark() {
        let _guard = unparallelize_test();

        static mut BUF1: [u8; 10240] = [0; 10240];
        static mut BUF2: [u8; 10240] = [0; 10240];

        let config = MsgRingConfig {
            ..Default::default()
        };

        let th1 = thread::spawn(move || {
            let mut mrs = MsgRingSender::new(unsafe { &BUF1 }, config);
            let mut mrr = MsgRingReceiver::new(unsafe { &BUF2 }, config);
            benchmark_loop("send..recv", &mut (&mut mrs, &mut mrr), |(mrs, mrr)| {
                mrs.compose(32).send();
                mrr.receive();
            });
        });

        let th2 = thread::spawn(move || {
            let mut mrs = MsgRingSender::new(unsafe { &BUF2 }, config);
            let mut mrr = MsgRingReceiver::new(unsafe { &BUF1 }, config);
            benchmark_loop("recv..send", &mut (&mut mrs, &mut mrr), |(mrs, mrr)| {
                mrr.receive();
                mrs.compose(32).send();
            });
        });

        th1.join().unwrap();
        th2.join().unwrap();
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

//fn main() {
//    let sl = [0u8; 23];
//    let a = &sl[..];
//    let b = Box::new(a.into_boxed_slice());
//    println!("size:{}", std::mem::size_of_val(&*b));
//}
