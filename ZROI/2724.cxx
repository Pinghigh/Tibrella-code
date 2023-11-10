#include <cstdint>
#include <iostream>
#include <string>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

using std::cin;
using std::cout;

u64 seed = 0;
u64 next() {
    seed ^= seed << 13;
    seed ^= seed >> 7;
    seed ^= seed << 17;
    return seed;
}

#define N 5001

u32 a[N][N], r[N], c[N];
u32 pow17[N], pow19[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    u32 n, m, q;
    cin >> n >> m >> q >> seed;
    for (u32 i = 0; i < n; ++i) {
        for (u32 j = 0; j < m; ++j) {
            a[i][j] = i * m + j;
        }
    }
    for (u32 i = 0; i < n; ++i)
        r[i] = i;
    for (u32 i = 0; i < m; ++i)
        c[i] = i;
    std::string opt;
    cin >> opt;
    for (const auto& op : opt) {
        switch (op) {
            case ('r'): std::swap(r[next() % n], r[next() % n]); break;
            case ('c'): std::swap(c[next() % m], c[next() % m]); break;
            default: std::swap(a[r[next() % n]][c[next() % m]], a[r[next() % n]][c[next() % m]]);
        }
    }

    pow17[0] = pow19[0] = 1;
    constexpr u32 mod = 998244353;
    for (u32 i = 1, lim = std::max(n, m); i <= lim; ++i)
        pow17[i] = pow17[i - 1] * 17ll % mod, pow19[i] = pow19[i - 1] * 19ll % mod;

    u32 res = 0;
    for (u32 i = 0; i < n; ++i) {
        for (u32 j = 0; j < m; ++j) {
            res = (res + a[r[i]][c[j]] % mod * 1ll * pow17[i] % mod * pow19[j] % mod);
            if (res >= mod) res -= mod;
            // cout << a[r[i]][c[j]] << ' ';
        }
        // cout << '\n';
    }

    cout << res;

    return 0;
}