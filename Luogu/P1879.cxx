#include <cstdint>
#include <iostream>

using std::cin;
using std::cout;

using u64 = uint_fast64_t;
using u32 = uint_fast32_t;
using u16 = uint_fast16_t;

constexpr u32 mod = 1e8;
const char endl = '\n';

#define N 12+1
#define ST (1 << 12)

#include <bitset>
#include <vector>

u64 st[N];
std::vector<u64> could[ST + 10], hefa;  // 存储一个状态能被什么状态转移过来；不相邻的合法的状态
u64 f[N][ST + 10];
u16 m, n, t1;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (u16 i = 1; i <= n; ++i)
        for (u16 j = 0; j < m; ++j) {
            cin >> t1;
            st[i] = (st[i] << 1) + t1;
        }

    u64 max_status = (1 << m) - 1;

    for (u64 i = 0; i <= max_status; ++i) {
        if (!(i & (i << 1)) && !(i & (i >> 1))) hefa.emplace_back(i);
        for (u64 j = 0; j <= max_status; ++j)
            if (!(i & j) && !(i & (i << 1)) && !(i & (i >> 1)) && !(j & (j << 1)) && !(j & (j >> 1))) could[i].emplace_back(j);
    }

    for (auto s1 : hefa) {
        if ((s1 & st[1]) == s1) f[1][s1] = 1;
    }

    for (u16 i = 2; i <= n; ++i) {
        for (auto s1 : hefa) {
            if ((s1 & st[i]) == s1) {  // 取与之后不变，说明被包含，即该状态合法
                for (auto s2 : could[s1]) {
                    f[i][s1] += f[i - 1][s2];
                    f[i][s1] %= mod;
                }
            }
        }
    }

    u64 ans = 0;
    for (auto s : hefa)
        (ans += f[n][s]) %= mod;

    cout << ans << endl;

    return 0;
}