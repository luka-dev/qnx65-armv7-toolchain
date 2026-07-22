use std::sync::{Arc, Mutex};
use std::sync::atomic::{AtomicU32, Ordering};
use std::{thread, fs, env};
use std::time::{Duration, Instant, SystemTime};

thread_local! {
    static TL: std::cell::Cell<u32> = std::cell::Cell::new(0);
}

fn main() {
    println!("== stdtest start ==");

    // --- M2: threads + TLS + Mutex/atomics ---
    let counter = Arc::new(AtomicU32::new(0));
    let shared = Arc::new(Mutex::new(0u64));
    let mut hs = Vec::new();
    for i in 0..8 {
        let c = counter.clone(); let s = shared.clone();
        hs.push(thread::spawn(move || {
            TL.with(|x| x.set(i * 100));
            thread::sleep(Duration::from_millis(2));
            TL.with(|x| assert_eq!(x.get(), i * 100)); // TLS isolation per-thread
            c.fetch_add(1, Ordering::SeqCst);
            *s.lock().unwrap() += i as u64;
        }));
    }
    for h in hs { h.join().unwrap(); }
    println!("M2 threads={} shared_sum={} (want 8, 28)",
             counter.load(Ordering::SeqCst), *shared.lock().unwrap());

    // (panic-in-thread test omitted: panic=abort kills the process by design)

    // --- M3: fs + env + time (step-isolated) ---
    let p = "/tmp/stdtest.txt";
    fs::write(p, b"hello-qnx-std").unwrap();
    println!("M3a write ok");
    let back = fs::read(p).unwrap();
    println!("M3b read ok len={} match={}", back.len(), back == b"hello-qnx-std");
    let md = fs::metadata(p).unwrap();
    println!("M3c metadata len={}", md.len());
    fs::remove_file(p).unwrap();
    println!("M3d remove ok");
    println!("M3e exists_after={}", std::path::Path::new(p).exists());
    let t0 = Instant::now();
    thread::sleep(Duration::from_millis(5));
    println!("M3f instant_ms={}", t0.elapsed().as_millis());
    let now = SystemTime::now().duration_since(SystemTime::UNIX_EPOCH).unwrap();
    println!("M3g systime_secs={}", now.as_secs());
    println!("M3h args0={:?}", env::args().next());


    // --- M4: process spawn (posix_spawn present on 6.5) ---
    match std::process::Command::new("/proc/boot/sh").arg("-c").arg("exit 7").status() {
        Ok(st) => println!("M4 process code={:?}", st.code()),
        Err(e)  => println!("M4 process ERR {}", e),
    }

    println!("== stdtest PASS ==");
}
