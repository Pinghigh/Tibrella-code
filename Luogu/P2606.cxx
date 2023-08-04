#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

i64 mod;

#define N 6000005

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

i64 trueC(i32 a, i32 b) {
    if (a < b) return 0;
    return fact[a] * ifact[b] % mod * ifact[a - b] % mod;
}

i64 getC(i32 a, i32 b) {
    if (!b) return 1;
    return (getC(a / mod, b / mod) * trueC(a % mod, b % mod) % mod + mod) % mod;
}

i64 res = 0;
i64 f[N];
i32 siz[N];

void dfs(i32 u) {
    i32 lc = u << 1, rc = u << 1 | 1;
    siz[u] = 1;
    if (lc <= n) {
        dfs(lc);
        siz[u] += siz[lc];
    }
    if (rc <= n) {
        dfs(rc);
        siz[u] += siz[rc];
    }
    if (lc > n && rc > n)
        f[u] = 1;
    else
        f[u] = getC(siz[u] - 1, siz[lc]) * f[lc] % mod * (f[rc] ? f[rc] : 1) % mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> mod;

    i32 lim;
    lim = std::min(n, mod - 1);
    fact[0] = ifact[0] = 1;
    for (i32 i = 1; i <= lim; ++i)
        fact[i] = fact[i - 1] * i % mod;
    ifact[lim] = inv(fact[lim]);
    for (i32 i = lim - 1; i; --i)
        ifact[i] = ifact[i + 1] * (i + 1) % mod;

    dfs(1);

    cout << f[1];

    return 0;
}