use std::io;

fn solution() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut lis = input.trim().split(' ');

    let mut n: usize = lis.next().unwrap().parse().unwrap();
    let p: f64 = lis.next().unwrap().parse().unwrap();
    let q: f64 = lis.next().unwrap().parse().unwrap();

    let mut f: [Vec<f64>; 2] = [Vec::new(), Vec::new()];

    if n > 100 {
        // 推到第 100 个石子就够了
        n = 100;
    }

    f[0].push(0.0);
    f[1].push(1.0);

    for i in 1..=n {
        let mut pnow = p;
        let mut qnow = q;
        if f[1][i - 1] > f[0][i - 1] {
            // 如果上一颗石子不应当让自己取
            // 这里取不取等号无所谓
            pnow = 1.0 - p;
            qnow = 1.0 - q;
        }
        f[0].push(
            (pnow * (1.0 - qnow) * f[0][i - 1] + (1.0 - pnow) * f[1][i - 1]) / (1.0 - pnow * qnow),
        );
        f[1].push(
            (qnow * (1.0 - pnow) * f[1][i - 1] + (1.0 - qnow) * f[0][i - 1]) / (1.0 - pnow * qnow),
        );
    }

    println!("{}", f[0][n]);
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut s = input.trim().split(' ');
    let mut t: i32 = s.next().unwrap().parse().unwrap();
    while t != 0 {
        solution();
        t -= 1;
    }
}