use std::collections::{HashMap, BTreeMap, HashSet};
fn main() {
    println!("== tortst start ==");
    // getrandom-backed: HashMap RandomState seeding
    let mut m: HashMap<String,u32> = HashMap::new();
    for i in 0..1000 { m.insert(format!("k{}", i), i); }
    println!("T hashmap len={} get_k500={:?}", m.len(), m.get("k500"));
    let s: HashSet<u32> = (0..100).map(|x| x%7).collect();
    println!("T hashset distinct={}", s.len());
    let mut b = BTreeMap::new();
    for i in (0..10).rev() { b.insert(i, i*i); }
    println!("T btree first={:?} last={:?}", b.iter().next(), b.iter().last());
    // env
    println!("T env_PATH_present={}", std::env::var("PATH").is_ok());
    // stderr
    eprintln!("T stderr line");
    // format edge cases
    println!("T fmt {:>8.3} {:#x} {:08b} {:e}", 3.14159, 255u32, 5u8, 1234.5f64);
    // sort + dedup
    let mut v = vec![5,3,8,1,3,9,1,5]; v.sort(); v.dedup();
    println!("T sorted={:?}", v);
    println!("== tortst PASS ==");
}
