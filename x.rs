
use std::collections::HashMap;
use std::collections::HashSet;
use std::vec::Vec;

fn main() {
  let x: Option<u32> = Some(1u32);
  let y: Option<u32> = Some(0);//None;
  let z: Option<u32> = Some(2u32);
  let v = vec![x, y, z];
  let r = v.into_iter().map(|v| v.map(|v| v*2));
  println!("{:?}", r);
  let r = r.collect::<Option<Vec<_>>>();
  println!("{:?}", r);
}