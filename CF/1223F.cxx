#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <random>
#include <ctime>

using std::cin;
using std::cout;

std::mt19937 rng(time(0) ^ 118745747u);

using u32 = unsigned;
using u64 = unsigned long long;
using i32 = int;
using i64 = long long;

#define N 300005

u32 rl1[N], rl2[N];
using puu = std::pair<u32, u32>;

struct my_hash {
    u64 splitmix(u64 x) const {
        x = (x ^ ((x << ((x >> 63u) + 2)) ^ 0x3f3747f38ac8fbeull));
        x = (x ^ ((x >> ((x >> 62u) + 1)) ^ 0x7f83ab766f0823full));
        return x;
    }

    size_t operator()(puu p) const {
        static const u64 FIX = time(0) ^ 0x3f84327af86c2e4;
        return splitmix(p.first - FIX) ^ (splitmix(p.second + FIX) >> 1);
    }
};

u32 stk[N];
void solve() {
    std::unordered_map<puu, u32, my_hash> m;
    u32 top = 0;
    u32 n;
    cin >> n;
    u64 ans = 0;
    u32 h1=0, h2=0;
    m[{0,0}] = 1;
    while (n--) {
        u32 x;
        cin >> x;
        if (top && stk[top] == x) h1 ^= (rl1[top] * x), h2 += (rl2[top] ^ x), --top;
        else stk[++top] = x, h1 ^= (rl1[top] * x), h2 -= (rl2[top] ^ x);
        ans += m[{h1, h2}];
        ++m[{h1, h2}];
    }
    cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 1; i <= 300000; ++ i) rl1[i] = rng(), rl2[i] = rng();

    i32 t;
    cin >> t;
    while (t--) solve();

    return 0;
}