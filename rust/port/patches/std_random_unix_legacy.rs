//! Random data from `/dev/urandom`
//!
//! Before `getentropy` was standardized in 2024, UNIX didn't have a standardized
//! way of getting random data, so systems just followed the precedent set by
//! Linux and exposed random devices at `/dev/random` and `/dev/urandom`. Thus,
//! for the few systems that support neither `arc4random_buf` nor `getentropy`
//! yet, we just read from the file.

use crate::fs::File;
use crate::io::{ErrorKind, Read};
use crate::sync::OnceLock;

static DEVICE: OnceLock<File> = OnceLock::new();

// QNX-6.5-port note: the `random` service's /dev/random can return EAGAIN
// (WouldBlock) before its entropy pool is primed, and there is no separate
// always-ready /dev/urandom. read_exact would fail; instead retry on WouldBlock
// (yielding while the daemon fills the pool) so HashMap seeding is robust.
pub fn fill_bytes(bytes: &mut [u8]) {
    let dev = DEVICE
        .get_or_try_init(|| File::open("/dev/urandom"))
        .expect("failed to open random device");
    let mut filled = 0;
    while filled < bytes.len() {
        match Read::read(&mut &*dev, &mut bytes[filled..]) {
            Ok(0) => panic!("random device returned EOF"),
            Ok(n) => filled += n,
            Err(e) if e.kind() == ErrorKind::Interrupted => continue,
            Err(e) if e.kind() == ErrorKind::WouldBlock => crate::thread::yield_now(),
            Err(e) => panic!("failed to generate random data: {e:?}"),
        }
    }
}
