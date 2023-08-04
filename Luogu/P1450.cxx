#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

#define N 1000005

using i32 = int;
using i64 = long long;

i64 f[N];
i64 c[5], d[5], n, s;

namespace tikogasa {
    void solve() {
        for (i32 i = 1; i < 5; ++i)
            cin >> d[i];
        cin >> s;

        i64 ans = f[s];
        for (i32 sx = 1; sx < (1 << 4); ++sx) {
            i32 st = sx;
            i32 id = 1, cst = 0;
            while (st) {
                if (st & 1) cst += c[id] * (d[id] + 1);
                ++id;
                st >>= 1;
            }
            i64 x = 1;
            if (__builtin_popcount(sx) & 1) x = -1;

            if (s - cst >= 0) ans += f[s - cst] * x;
        }
        cout << ans << '\n';
    }
}  // namespace tikogasa

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (i32 i = 1; i < 5; ++i)
        cin >> c[i];
    cin >> n;

    f[0] = 1;
    for (i32 i = 1; i < 5; ++i)
        for (i32 j = c[i]; j <= 100000; ++j)
            f[j] += f[j - c[i]];

    while (n--) {
        tikogasa::solve();
    }

    return 0;
}