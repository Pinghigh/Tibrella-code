use std::io;

struct edge {
    fr: u32;
    to: u32;
    dis: u64;
}

impl edge {
    fn new();
}

fn solve() {
    let mut edge: Vec<i64> = Vec::new();
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut s = input.trim().split(' ');
    let mut t: u16 = s.next().unwrap().parse().unwrap();
    while t != 0 {
        solve();
        t -= 1;
    }
}
