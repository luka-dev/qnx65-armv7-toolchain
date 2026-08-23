use std::collections::BTreeMap;
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let mut v = vec!["pear", "apple", "fig"];
    v.sort();
    println!("sorted: {}", v.join(" "));

    let total = Arc::new(Mutex::new(0u32));
    let mut hs = Vec::new();
    for i in 1..=8u32 {
        let t = Arc::clone(&total);
        hs.push(thread::spawn(move || { *t.lock().unwrap() += i * i; }));
    }
    for h in hs { h.join().unwrap(); }
    let sum = *total.lock().unwrap();
    println!("sum of squares 1..8 = {} (expect 204)", sum);

    let m: BTreeMap<&str, usize> = v.iter().map(|s| (*s, s.len())).collect();
    println!("map: apple={} fig={} pear={}", m["apple"], m["fig"], m["pear"]);
    std::process::exit(if sum == 204 { 0 } else { 1 });
}
