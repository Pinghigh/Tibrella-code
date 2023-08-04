#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <numeric>
#include <vector>

using std::cin;
using std::cout;

using u8 = unsigned char;
using u32 = int;
using u64 = long long;

u64 mod = 1e9;

u32 n, m, k;
u64 ans;
u8 st = 2;  // 这是 (1,1) 的状态，如果未知，则需要枚举
u32 x, y, z;

#define N 400005
std::bitset<N * 4> vis;
u64 binpow(u32 cnt) {
    u64 res = 1, x = 2;
    while (cnt) {
        if (cnt & 1) (res *= x) %= mod;
        (x *= x) %= mod;
        cnt >>= 1;
    }
    return res;
}

u32 op[N * 4];

u32 opp(u32 id) {
    return op[id];
}

bool isEven(u32 x) {  // 如果 x 是偶数，返回真
    return !(x & 1);
}

u32 fa[N * 4], rk[N * 4];

u32 find(u32 x) {
    return (fa[x] == x) ? fa[x] : fa[x] = find(fa[x]);
}

void merge(u32 x, u32 y) {
    fa[x] = y;
}

inline void failed() {
    cout.put('0');
    exit(0);
}

void calc(u32 x, u32 y, bool st) {
    x = find(x), y = find(y);
    if (st) {
        if (x == opp(y))
            return;
        else if (x == y)
            failed();
        merge(x, opp(y)), merge(opp(x), y);
    } else {
        if (x == opp(y))
            failed();
        else if (x == y)
            return;
        merge(x, y), merge(opp(x), opp(y));
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> k;
    for (u32 i = 1; i <= n + m; ++i)
        fa[i] = op[i + n + m] = i, fa[i + n + m] = op[i] = i + n + m;
    // std::iota(fa + 1, fa + (n + m) * 2, 1);
    for (u32 i = 0; i < k; ++i) {
        cin >> x >> y >> z;
        if (isEven(x + 1) && isEven(y + 1)) z ^= 1;
        y += n;
        calc(x, y, z);
    }

    {  // 局部变量，尽早失效。
        u32 f = find(1);
        vis[f] = vis[opp(f)] = true;
        for (u32 i = 2; i <= n + m; ++i) {
            f = find(i);
            if (!vis[f]) ++ans;
            vis[f] = vis[opp(f)] = true;
        }
    }

    cout << binpow(ans);

    return 0;
}