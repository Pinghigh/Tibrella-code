#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

const i64 mod = 998244353;

#define N 300005

i64 fact[N], ifact[N];

i64 n, a, b, k;

void exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (!b) return x = 1, y = 0, void();
    exgcd(b, a % b, x, y);
    i64 tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}

i64 inv(i64 a) {
    i64 x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

i64 getC(i32 a, i32 b) {
    if (a < b) return 0;
    return fact[a] * ifact[b] % mod * ifact[a - b] % mod;
}

i64 res = 0;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> a >> b >> k;
    fact[0] = ifact[0] = 1;
    for (i32 i = 1; i <= n; ++i)
        fact[i] = fact[i - 1] * i % mod;
    ifact[n] = inv(fact[n]);
    for (i32 i = n - 1; i; --i)
        ifact[i] = ifact[i + 1] * (i + 1) % mod;

    for (i32 i = 0; i <= n; ++i) {
        if (a * 1ll * i > k) break;
        if (!((k - a * 1ll * i) % b)) {
            i32 j = (k - a * i) / b;
            res += getC(n, i) * getC(n, j) % mod;
            res %= mod;
        }
    }

    cout << res;

    return 0;
}