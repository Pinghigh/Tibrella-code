#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 1048580

constexpr i32 mod = 998244353;

i32 inv[N];

void init() {
    inv[1] = 1;
    for (i32 i = 2; i < N; ++ i) inv[i] = inv[mod % i] * 1ll * (mod - mod / i) % mod; 
}

#define popcnt(x) __builtin_popcount(x)

i32 con[N]; // connected
i32 siz[N], f[N];

template <typename T>
void chkmax(T& a, const T& b) {
    if (a < b) a = b;
}

void add(i32 &a, const i32& b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();

    i32 n, m;
    cin >> n >> m;
    i32 mxst = (1<<n) - 1;

    for (i32 i = 1; i <= n; ++ i) con[i] = 1 << (i-1), siz[1 << (i-1)] = 1;

    for (i32 i = 1; i <= m; ++ i) {
        i32 u, v;
        cin >> u >> v;
        con[u] |= 1 << (v-1);
        con[v] |= 1 << (u-1);
    }

    for (i32 s = 1; s <= mxst; ++ s)
        for (i32 i = 1; i <= n; ++ i)
            if (s & (1 << (i-1))) chkmax(siz[s], siz[s & (~con[i])] + 1);

    f[0] = 1;
    for (i32 s = 1; s <= mxst; ++ s) {
        for (i32 i = 1; i <= n; ++ i)
            if (s & (1 << (i-1)) && siz[s] == siz[s & (~con[i])]+1) 
                add(f[s], f[s & (~con[i])]);
        f[s] = f[s] * 1ll * inv[popcnt(s)] % mod;
    }

    cout << f[mxst];

    return 0;
}