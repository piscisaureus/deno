#[macro_use]
extern crate integer_atomics;

use integer_atomics::AtomicI32;
use std::marker::PhantomData;
use std::mem::size_of;
use std::ops::{Deref, DerefMut};
use std::sync::atomic::{AtomicUsize, Ordering};

// Slice should not implement Copy.
pub struct Slice<'a, T> {
    inner: T,
    phantom: PhantomData<&'a i8>,
}

impl<'a, T> Slice<'a, T> {
    fn new(inner: T) -> Self {
        Self {
            inner,
            phantom: PhantomData,
        }
    }
}

impl<'a, T> Deref for Slice<'a, T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        &self.inner
    }
}

impl<'a, T> DerefMut for Slice<'a, T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.inner
    }
}

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
impl FrameAllocation {
    pub const None: i32 = 0;
    pub const Alignment: i32 = 8;
    pub const HeaderByteLength: i32 = 8;
}

struct FrameHeader;
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
    pub fillDirection: FillDirection,
    pub spinCount: u32,
    pub spinYieldCpuTime: u32,
}

impl Default for MsgRingConfig {
    fn default() -> Self {
        Self {
            fillDirection: FillDirection::TopDown,
            spinCount: 10,
            spinYieldCpuTime: 0, // Disabled.
        }
    }
}

#[derive(Default)]
struct MsgRingCommon<'buf> {
    pub config: MsgRingConfig,
    pub counters: MsgRingCounters,

    pub buffer: &'buf [u8],
    pub epoch: i32,

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
            match config.fillDirection {
                FillDirection::TopDown => (0, 1),
                FillDirection::BottomUp => (1, -1),
            };
        Self {
            config,
            buffer,
            epoch,
            fill_direction_base_adjustment,
            fill_direction_offset_adjustment,
            ..Default::default()
        }
    }

    #[inline]
    pub fn buffer_byte_length(&self) -> i32 {
        debug_assert!(self.buffer.len() < std::i32::MAX as usize);
        return self.buffer.len() as i32;
    }

    #[inline]
    pub fn frame_byte_length(&self) -> i32 {
        self.frame_tail_position - self.frame_head_position
    }

    #[inline]
    fn frame_is_at_end_of_buffer(&self) -> bool {
        self.frame_head_position == self.buffer_byte_length()
    }

    pub fn acquire_frame(&mut self) -> i32 {
        self.acquire_frame_impl(true)
    }

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

        let mut spin_count_remaining = self.config.spinCount;
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

        let header_ptr = self.header_ptr(self.frame_head_position);
        let header_slot = unsafe { &mut *(header_ptr as *mut integer_atomics::AtomicI32) };
        let old_header = header_slot.swap(new_header, Ordering::AcqRel);

        if old_header & FrameHeader::HasWaitersFlag != 0 {
            // TODO
            // Atomics.wake(this.i32, headerI32Offset, 1);
            self.counters.wake += 1;
        }
    }

    pub fn get_message_slice_mut(&self, frame_byte_length: i32) -> &'buf mut [u8] {
        let message_byte_length = frame_byte_length - FrameAllocation::HeaderByteLength;
        let message_byte_offset = self.fill_direction_base_adjustment
            * (self.buffer_byte_length() - message_byte_length)
            + self.fill_direction_offset_adjustment
                * (self.frame_tail_position + FrameAllocation::HeaderByteLength);
        let message_end = message_byte_offset + message_byte_length;
        eprintln!(
            "{}-{}={}",
            message_byte_offset, message_end, message_byte_length
        );
        let message_frame = &self.buffer[message_byte_offset as usize..message_end as usize];
        unsafe {
            // Although our synchronization mechanism ensures that there can
            // never be more than one reference to the returned message slice,
            // this transmute isn't pretty and appears to be un-idiomatic.
            // TODO: use more idiomatic rust.
            #[allow(mutable_transmutes)]
            std::mem::transmute::<&'buf [u8], &'buf mut [u8]>(message_frame)
        }
    }

    pub fn get_message_slice(&self, frame_byte_length: i32) -> &'buf [u8] {
        self.get_message_slice_mut(frame_byte_length)
    }
}

pub struct MsgRingSender<'buf> {
    common: MsgRingCommon<'buf>,
    allocation_byte_length: i32,
}

pub struct Stom {}

impl<'buf> MsgRingSender<'buf> {
    pub fn new(buffer: &'buf [u8], config: MsgRingConfig) -> Self {
        Self {
            common: MsgRingCommon::new(buffer, config, FrameHeader::EpochInitSender),
            allocation_byte_length: 0,
        }
    }

    pub fn begin_send(&mut self) -> Slice<&mut [u8]> {
        Slice::new(self.common.get_message_slice_mut(12))
    }

    pub fn begin_receive(&mut self) -> Slice<&[u8]> {
        Slice::new(self.common.get_message_slice(12))
    }

    pub fn end_send(&mut self, slice: Slice<&mut [u8]>) {}
}

/*
export class MsgRingSender extends MsgRingCommon {
  protected epoch: number = FrameHeader.EpochInitSender;

  // Number of bytes allocated by beginSend()/resizeSend(). It includes space
  // for the frame header and padding for alignment
  private allocationByteLength: number = FrameAllocation.None;

  // Note: byteLength will be rounded up to alignment.
  beginSend(messageByteLength: number): Slice {
    if (this.allocationByteLength !== FrameAllocation.None) {
      throw new Error("Already writing.");
    }
    this.allocate(messageByteLength);
    return this.getMessageSlice(this.allocationByteLength);
  }

  // Note: byteLength will be rounded up to alignment.
  // Noto: already-written data is discarded when buffer wraps.
  // TODO: copy bytes when allocation wraps.
  resizeSend(messageByteLength: number): Slice {
    if (this.allocationByteLength === FrameAllocation.None) {
      throw new Error("Not writing.");
    }
    this.allocate(messageByteLength);
    return this.getMessageSlice(this.allocationByteLength);
  }

  endSend(submit = true): void {
    if (this.allocationByteLength === FrameAllocation.None) {
      throw new Error("Not writing.");
    }
    if (submit) {
      // Release a frame that contains the header plus message.
      this.releaseFrame(this.allocationByteLength, FrameHeader.HasMessageFlag);
      this.messageCounter++;
    }
    this.allocationByteLength = FrameAllocation.None;
  }

  send(data: ArrayBufferView): void {
    // Convert `data` to an Uint8Array view if necessary.
    const u8data: Uint8Array =
      data instanceof Uint8Array
        ? data
        : new Uint8Array(data.buffer, data.byteOffset, data.byteLength);
    // Allocate space.
    const target = this.beginSend(data.byteLength);
    // Copy data.
    this.u8.set(u8data, target.byteOffset);
    // Close the send.
    this.endSend();
  }

  private allocate(messageByteLength: number): void {
    // Check whether messageByteLength is in range, and if so, store it.
    if (messageByteLength > this.maxMessageByteLength)
      throw new RangeError("Slice too big.");
    if (messageByteLength < 0)
      throw new RangeError("Slice must have positive byte length.");

    // Compute the total required length, including header and padding,
    this.allocationByteLength =
      FrameAllocation.HeaderByteLength + this.align(messageByteLength);

    while (this.frameByteLength < this.allocationByteLength) {
      // An allocation can't wrap around the end of the ring buffer.
      if (this.frameIsAtEndOfBuffer && this.frameByteLength > 0) {
        // Discard the allocation we've made so far. The allocation process will
        // restart at the beginning of the ring buffer.
        this.releaseFrame(this.frameByteLength);
      }
      // Consume the next frame to get closer to the target allocation length.
      this.acquireFrame();
    }
  }

  private align(byteCount: number): number {
    const alignmentMask = FrameAllocation.Alignment - 1;
    return (byteCount + alignmentMask) & ~alignmentMask;
  }
}
*/

fn main() {
    println!("Hello, world!");
}

#[test]
fn ttt() {
    let x = b"abcdefgh 0123";
    let config = MsgRingConfig {
        ..Default::default()
    };
    let muts: &mut [u8];
    let v: u8 = 0;
    {
        let mut sender = MsgRingSender::new(x, config);
        let mut slice = sender.begin_send();
        sender.end_send(slice);
        //muts = slice.deref_mut();
        //muts[0] += 1;
        //v = muts[0];
    }
    eprintln!("{}", v)
}
