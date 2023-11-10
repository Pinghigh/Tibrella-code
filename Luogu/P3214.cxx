#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

constexpr i64 mod = 1e8 + 7;

template <typename T>
T binpow(T a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p&1) res = res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}

#define N 1000006

i64 f[N], a[N];
i64 n, m;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    a[0] = 1, a[1] = (binpow(2ll,n) - 1) % mod;
    for (i64 i = 2; i <= m; ++ i) a[i] = a[i-1] * (a[1] - i + 1) % mod;

    f[0] = 1;
    for (i64 i = 2; i <= m; ++ i) {
        f[i] = a[i - 1];
        f[i] = (f[i] - f[i-1]) % mod;
        f[i] = (f[i] - f[i-2] * (i - 1) % mod * (a[1] - i + 2) % mod) % mod;
    }

    i64 fact = 1;
    for (i64 i = 2; i <= m; ++ i) fact = fact * i % mod;
    // cout << fact << ' ' << binpow(fact, mod - 2) << '\n';
    f[m] = (f[m] * binpow(fact, mod - 2) % mod + mod) % mod;

    cout << f[m];

    return 0;
}