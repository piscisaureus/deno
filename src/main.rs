extern crate integer_atomics;

use integer_atomics::AtomicI32;
use std::ops::{Deref, DerefMut};
use std::sync::atomic::Ordering;
use std::time::{Duration, Instant};

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
struct MsgRingCommon<'buf> {
    pub config: MsgRingConfig,
    pub counters: MsgRingCounters,

    pub buffer: &'buf [u8],
    pub epoch: i32,

    pub test_buf: [u8; 10],

    // Head and tail position are in bytes, but always starting at zero and
    // not adjusted for buffer fill direction (see TypeScript implementation).
    pub frame_tail_position: i32,
    pub frame_head_position: i32,

    pub fill_direction_base_adjustment: i32,
    pub fill_direction_offset_adjustment: i32,
}

impl<'buf> MsgRingCommon<'buf> {
    pub fn new(buffer: &'buf [u8], config: MsgRingConfig, epoch: i32) -> Self {
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
    pub fn frame_byte_length(&self) -> i32 {
        self.frame_head_position - self.frame_tail_position
    }

    #[inline]
    fn frame_is_at_end_of_buffer(&self) -> bool {
        self.frame_head_position == self.buffer_byte_length()
    }

    pub fn acquire_frame(&mut self) -> i32 {
        self.acquire_frame_impl(true)
    }

    #[allow(dead_code)]
    pub fn try_acquire_frame(&mut self) -> i32 {
        self.acquire_frame_impl(false)
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

    #[inline]
    fn acquire_frame_impl(&mut self, wait: bool) -> i32 {
        if self.frame_is_at_end_of_buffer() {
            assert!(self.frame_byte_length() == 0);

            self.epoch = (self.epoch + FrameHeader::EpochIncrementWrap) & FrameHeader::EpochMask;

            self.frame_head_position = 0;
            self.frame_tail_position = 0;
            self.counters.wrap += 1;
        }

        let header_ptr = self.header_ptr(self.frame_head_position);
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

            if sleep {
                // TODO
                //Atomics.wait(this.i32, headerI32Offset, header, futexWaitTime) !==
                //  "timed-out"
            } else {
                header = header_slot.load(Ordering::Acquire);
            }
        }

        let byte_length = header & FrameHeader::ByteLengthMask;
        assert!(byte_length <= self.buffer_byte_length() - self.frame_head_position);

        self.frame_head_position += byte_length;
        self.counters.acquire += 1;

        return header;
    }

    pub fn release_frame(&mut self, byte_length: i32, flags: i32) -> () {
        assert!(byte_length >= FrameAllocation::HeaderByteLength);
        assert!(byte_length <= self.frame_byte_length());

        let tail_epoch = self.epoch + FrameHeader::EpochIncrementPass;
        let new_header = byte_length | flags | tail_epoch;

        let header_ptr = self.header_ptr(self.frame_tail_position);
        let header_slot = unsafe { &mut *(header_ptr as *mut integer_atomics::AtomicI32) };
        let old_header = header_slot.swap(new_header, Ordering::AcqRel);

        if old_header & FrameHeader::HasWaitersFlag != 0 {
            // TODO
            // Atomics.wake(this.i32, headerI32Offset, 1);
            self.counters.wake += 1;
        }

        self.frame_tail_position += byte_length;
    }

    pub fn get_message_slice_impl<'a, 'b: 'buf>(&'a self, frame_byte_length: i32) -> &'b mut [u8] {
        let message_byte_length = frame_byte_length - FrameAllocation::HeaderByteLength;
        let message_byte_offset = self.fill_direction_base_adjustment
            * (self.buffer_byte_length() - message_byte_length)
            + self.fill_direction_offset_adjustment
                * (self.frame_tail_position + FrameAllocation::HeaderByteLength);
        let message_end = message_byte_offset + message_byte_length;
        let message_frame = &self.buffer[message_byte_offset as usize..message_end as usize];
        unsafe {
            // Although our synchronization mechanism ensures that there can
            // never be more than one reference to the returned message slice,
            // this transmute isn't pretty and appears to be un-idiomatic.
            // TODO: use more idiomatic rust.
            #[allow(mutable_transmutes)]
            std::mem::transmute::<&[u8], &'b mut [u8]>(message_frame)
        }
    }

    pub fn get_message_slice<'a, 'b: 'buf>(&'a self, frame_byte_length: i32) -> &'b [u8] {
        self.get_message_slice_impl(frame_byte_length)
    }

    pub fn get_message_slice_mut<'a, 'b: 'buf>(
        &'a mut self,
        frame_byte_length: i32,
    ) -> &'b mut [u8] {
        self.get_message_slice_impl(frame_byte_length)
    }
}

pub struct MsgRingSender<'buf> {
    common: MsgRingCommon<'buf>,
}

impl<'buf> MsgRingSender<'buf> {
    pub fn new(buffer: &'buf [u8], config: MsgRingConfig) -> Self {
        Self {
            common: MsgRingCommon::new(buffer, config, FrameHeader::EpochInitSender),
        }
    }

    pub fn begin_send<'a>(&'a mut self, byte_length: usize) -> Send<'a, 'buf> {
        Send::new(self, byte_length)
    }
}

pub struct Send<'a, 'buf: 'a> {
    sender: &'a mut MsgRingSender<'buf>,
    allocation_byte_length: i32,
}

impl<'a, 'buf> Send<'a, 'buf> {
    pub fn new(sender: &'a mut MsgRingSender<'buf>, message_byte_length: usize) -> Self {
        let mut this = Self {
            sender,
            allocation_byte_length: 0,
        };
        this.allocate(message_byte_length);
        this
    }

    pub fn resize(&mut self, message_byte_length: usize) {
        self.allocate(message_byte_length)
    }

    pub fn finish(self) -> () {
        self.sender
            .common
            .release_frame(self.allocation_byte_length, FrameHeader::HasMessageFlag);
    }

    pub fn abort(self) -> () {}

    fn allocate(&mut self, byte_length: usize) {
        let allocation_byte_length =
            FrameAllocation::HeaderByteLength as usize + FrameAllocation::align(byte_length);
        assert!(allocation_byte_length <= FrameHeader::ByteLengthMask as usize);
        self.allocation_byte_length = allocation_byte_length as i32;
        while self.sender.common.frame_byte_length() < self.allocation_byte_length {
            if self.sender.common.frame_is_at_end_of_buffer()
                && self.sender.common.frame_byte_length() > 0
            {
                self.sender
                    .common
                    .release_frame(self.sender.common.frame_byte_length(), FrameHeader::None);
            }
            self.sender.common.acquire_frame();
        }
    }
}

impl<'a, 'buf> Deref for Send<'a, 'buf> {
    type Target = [u8];

    fn deref(&self) -> &[u8] {
        self.sender
            .common
            .get_message_slice(self.allocation_byte_length)
    }
}

impl<'a, 'buf> DerefMut for Send<'a, 'buf> {
    fn deref_mut(&mut self) -> &mut [u8] {
        self.sender
            .common
            .get_message_slice_mut(self.allocation_byte_length)
    }
}

pub struct MsgRingReceiver<'buf> {
    common: MsgRingCommon<'buf>,
}

impl<'buf> MsgRingReceiver<'buf> {
    pub fn new(buffer: &'buf [u8], config: MsgRingConfig) -> Self {
        Self {
            common: MsgRingCommon::new(buffer, config, FrameHeader::EpochInitReceiver),
        }
    }

    pub fn receive<'a>(&'a mut self) -> Receive<'a, 'buf> {
        Receive::new(self)
    }
}

pub struct Receive<'a, 'buf: 'a> {
    receiver: &'a mut MsgRingReceiver<'buf>,
}

impl<'a, 'buf> Receive<'a, 'buf> {
    fn new(receiver: &'a mut MsgRingReceiver<'buf>) -> Self {
        let mut this = Self { receiver };
        this.acquire();
        this
    }

    fn acquire(&mut self) -> () {
        // Bug: what happens when previous frame not released?
        while self.receiver.common.acquire_frame() & FrameHeader::HasMessageFlag == 0 {
            self.receiver
                .common
                .release_frame(self.receiver.common.frame_byte_length(), FrameHeader::None);
        }
    }

    pub fn finish(self) -> () {
        self.receiver
            .common
            .release_frame(self.receiver.common.frame_byte_length(), FrameHeader::None);
    }

    pub fn abort(self) -> () {}
}

impl<'a, 'buf> Deref for Receive<'a, 'buf> {
    type Target = [u8];

    fn deref(&self) -> &[u8] {
        self.receiver
            .common
            .get_message_slice(self.receiver.common.frame_byte_length())
    }
}

const PER_ROUND: u64 = 1e7 as u64;
const PER_SUBROUND: usize = 1;

fn main() {
    let ab = [0u8; PER_SUBROUND * 100];
    let config = MsgRingConfig {
        ..Default::default()
    };
    let mut mq_in = MsgRingReceiver::new(&ab, config);
    let mut mq_out = MsgRingSender::new(&ab, config);

    let start = Instant::now();
    let mut received = 0;

    for round in 0..100 {
        eprintln!("====== single-thread round {} ======", round);
        for _ in (0..PER_ROUND).step_by(PER_SUBROUND) {
            let out_len = 32;
            for _ in 0..PER_SUBROUND {
                let mut sl = mq_out.begin_send(out_len);
                sl[3] = 4;
                sl.finish();
            }
            for _ in 0..PER_SUBROUND {
                let sl = mq_in.receive();
                sl.finish();
            }
        }
        received += PER_ROUND;
        eprintln!("messages processed: {}", received);
        let elapsed: Duration = Instant::now() - start;
        let elapsed = elapsed.as_millis() as f64 / 1000f64;
        eprintln!(
            "throughput (msg/sec): {}",
            (received as f64 / elapsed) as u64
        );
    }
}
