#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using i32 = int;
using i64 = long long;

#define N 500005

constexpr i64 mod = 1e9 + 7;
i64 cnt[N + 100];
i64 n, m;
i64 fact[N + 100], ifact[N + 100];

void exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (!b) return x = 1, y = 0, void();
    exgcd(b, a % b, x, y);
    i64 tmp = x;
    x = y;
    y = tmp - a / b * y;
}

i64 inv(i64 a) {
    if (!ifact[a]) {
        i64 x, y;
        exgcd(fact[a], mod, x, y);
        ifact[a] = (x % mod + mod) % mod;
    }
    return ifact[a];
}

i64 getC(i32 a, i32 b) {
    if (a < b) return 0;
    return fact[a] * inv(b) % mod * inv(a - b) % mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    fact[0] = 1;
    for (int i = 1; i <= N + 96; ++i)
        fact[i] = fact[i - 1] * i % mod;

    i32 div = 0;
    for (int i = 2; i * i <= m; ++i) {
        if (!(m % i)) {
            ++div;
            do {
                ++cnt[div];
                m /= i;
            } while (!(m % i));
        }
    }
    if (m > 1) ++cnt[++div];

    i64 ans = 1;
    for (int i = 1; i <= div; ++i)
        ans = ans * getC(n + cnt[i] - 1, cnt[i]) % mod;

    // for (int i = 1; i <= 3; ++ i) cout << ifact[i] << ' ';

    cout << ans;

    return 0;
}