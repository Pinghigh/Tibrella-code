use std::io;

#[derive(Copy, Clone, Debug, Eq, Ord, PartialEq, PartialOrd)]
pub struct Group {
    a: i64,
    b: i64,
    c: i64,
}

impl Group {
    pub fn read(&mut self) {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let mut s = input.trim().split(' ');
        self.a = s.next().unwrap().parse().unwrap();
        self.b = s.next().unwrap().parse().unwrap();
        self.c = s.next().unwrap().parse().unwrap();
    }
}

fn solution() {
    let mut input = String::new();

    io::stdin().read_line(&mut input).unwrap();
    let mut s = input.trim().split(' ');

    let n: i64 = s.next().unwrap().parse().unwrap();
    let m: i64 = s.next().unwrap().parse().unwrap();

    let mut ans: i64 = -9329324981;
    let mut shop: Vec<Group> = vec![Group { a: 0, b: 0, c: 0 }; n as usize];

    for i in 0..=n - 1 {
        shop[i as usize].read();
    }

    let mut tot = 0;
    
    let sign = [-1, 1];

    for i in sign.iter() {
        for j in sign.iter() {
            for k in sign.iter() {
                tot = 0;
                shop.sort_unstable_by(|a, b| {
                    (b.a * i + b.b * j + b.c * k).cmp(&(a.a * i + a.b * j + a.c * k))
                });
                for it in 0..=m - 1 {
                    tot +=
                        shop[it as usize].a * i + shop[it as usize].b * j + shop[it as usize].c * k;
                }
                ans = std::cmp::max(ans, tot);
            }
        }
    }
    println!("{}\n", ans);
}

fn main() {
    solution();
}
