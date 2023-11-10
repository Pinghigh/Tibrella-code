use std::io;

fn valid(pos: usize, i: usize, n: &usize, x: &usize) -> bool {
    ((i + pos + 1 - *x) <= *n && (i + pos + 1 - *x) > 0) as bool
}

fn main() {
    const MD: usize = 998244353;
    const N: usize = 205;
    const ST: usize = 600;
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut s = input.trim().split(' ');

    let n: usize = s.next().unwrap().parse().unwrap();
    let x: usize = s.next().unwrap().parse().unwrap();

    let mut f = [[[0; ST]; N]; N];

    let mxst: usize = (1 << ((x << 1) - 2 + 1)) - 1; // 区间长度本来是 (x << 1) - 2，但是还要包含 i 本身，所以 + 1

    f[0][0][0] = 1;
    for i in 1..=n {
        for j in 0..=i - 1 {
            for s in 0..=mxst {
                let ns: usize = s >> 1;
                f[i][j][ns] = (f[i][j][ns] + f[i - 1][j][s]) % MD;
                for p in 0..=(x << 1) - 2 {
                    if ((1 << p) & ns) == 0 && valid(p, i, &n, &x) {
                        f[i][j + 1][ns | (1 << p)] =
                            (f[i][j + 1][ns | (1 << p)] + f[i - 1][j][s]) % MD
                    }
                }
            }
        }
    }

    let mut fact = [0; N];
    fact[0] = 1;
    for i in 1..=n {
        fact[i] = fact[i - 1] * i % MD;
    }

    let mut ans: i64 = 0;
    for i in 0..=n {
        for s in 0..=mxst {
            if i & 1 == 1 {
                ans -= (f[n][i][s] * fact[n - i] % MD) as i64;
            } else {
                ans += (f[n][i][s] * fact[n - i] % MD) as i64;
            }
            ans %= MD as i64;
        }
    }
    ans = (ans % MD as i64 + MD as i64) % MD as i64;
    println!("{}", ans);
}
