#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define popcnt __builtin_popcount

constexpr i64 mod = 998244353;

#define ST ((1 << 10) + 10)
#define N 205

i64 f[N][N][ST];
i64 n, x;
i32 mxst;
i64 fact[N];

bool valid(i32 pos, i32 i) {
    return (i + pos + 1 - x) <= n && (i + pos + 1 - x) > 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> x;

    f[0][0][0] = 1;
    mxst = (1 << ((x << 1) - 2 + 1)) - 1;  // 为了保证可以理解，还是不改成 -1 了

    for (i32 i = 1; i <= n; ++i) {
        for (i32 j = 0; j < i; ++j) {
            for (i32 s = 0; s <= mxst; ++s) {
                i32 ns = s >> 1;  // next status
                f[i][j][ns] = (f[i][j][ns] + f[i - 1][j][s]) % mod;
                for (i32 p = 0; p <= (x << 1) - 2; ++p)
                    if (!((1 << p) & ns) && valid(p, i)) 
                    f[i][j + 1][ns | (1 << p)] = 
                    (f[i][j + 1][ns | (1 << p)] + f[i - 1][j][s]) % mod;
            }
        }
    }

    fact[0] = 1;
    for (i32 i = 1; i <= n; ++i)
        fact[i] = fact[i - 1] * i % mod;

    i64 ans = 0;
    for (i32 i = 0; i <= n; ++i)
        for (i32 s = 0; s <= mxst; ++s) {
            ans += f[n][i][s] * ((i & 1) ? -1 : 1) % mod * fact[n - i] % mod;
            ans %= mod;
        }

    ans = (ans + mod) % mod;

    cout << ans;

    return 0;
}