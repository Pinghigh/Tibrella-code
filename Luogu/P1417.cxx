#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

#define N 100500

using i32 = int;
using i64 = long long;

i64 a[N], b[N], c[N];
i32 num[N];
i32 n, t;
i64 f[N];
i64 ans;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t >> n;
    memset(f, -1, sizeof f);
    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
        num[i] = i;
    }
    for (i32 i = 1; i <= n; ++i)
        cin >> b[i];
    for (i32 i = 1; i <= n; ++i)
        cin >> c[i];
    std::sort(num + 1, num + n + 1, [](i32& x, i32& y) -> bool { return c[x] * b[y] < c[y] * b[x]; });
    f[0] = 0;
    for (i32 it = 1, i = num[it]; it <= n; ++it, i = num[it]) {
        for (i32 j = t - c[i]; ~j; --j) {
            if (~f[j]) f[j + c[i]] = std::max(f[j + c[i]], f[j] + (a[i] - b[i] * (j + c[i])));
        }
    }
    for (int i = 0; i <= t; ++i)
        ans = std::max(f[i], ans);
    cout << ans;

    return 0;
}