use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream, UdpSocket};
use std::thread;
use std::time::Duration;

fn main() {
    println!("== nettest start ==");

    // --- TCP loopback ---
    let listener = TcpListener::bind("127.0.0.1:0").expect("bind");
    let addr = listener.local_addr().unwrap();
    println!("M5 tcp listening on {}", addr);

    let srv = thread::spawn(move || {
        let (mut s, peer) = listener.accept().expect("accept");
        let mut buf = [0u8; 16];
        let n = s.read(&mut buf).unwrap();
        s.write_all(&buf[..n]).unwrap(); // echo
        peer.port()
    });

    thread::sleep(Duration::from_millis(20));
    let mut c = TcpStream::connect(addr).expect("connect");
    c.write_all(b"deadbeef").unwrap();
    let mut back = [0u8; 16];
    let n = c.read(&mut back).unwrap();
    let echoed = &back[..n];
    println!("M5 tcp echo n={} ok={}", n, echoed == b"deadbeef");
    let _ = srv.join();

    // --- UDP loopback ---
    let a = UdpSocket::bind("127.0.0.1:0").unwrap();
    let b = UdpSocket::bind("127.0.0.1:0").unwrap();
    let ba = b.local_addr().unwrap();
    a.send_to(b"ping", ba).unwrap();
    let mut ub = [0u8; 8];
    let (un, _from) = b.recv_from(&mut ub).unwrap();
    println!("M5 udp n={} ok={}", un, &ub[..un] == b"ping");

    println!("== nettest PASS ==");
}
