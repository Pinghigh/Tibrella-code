#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

constexpr i64 mod = 1e9 + 7;

i64 binpow(i64 p) {
    i64 x = 2, res = 1;
    while (p) {
        if (p & 1) res = res * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return res;
}

#define N 100005

struct seg {
    i32 l, r;
} s[N];

i32 sum[N << 1];

i64 f[N];

i32 n;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> s[i].l >> s[i].r;
        ++sum[s[i].r];
    }
    for (i32 i = 1; i <= (n << 1); ++i)
        sum[i] += sum[i - 1];

    std::sort(s + 1, s + n + 1, [](const seg& a, const seg& b) -> bool { return a.l < b.l; });

    for (i32 i = 1; i <= n; ++i) 
        f[i] = ((f[i - 1] << 1) % mod + binpow(sum[s[i].l - 1])) % mod;
   
    cout << f[n];

    return 0;
}