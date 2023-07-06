#include <algorithm>
#include <iostream>

using i32 = int;
using i64 = long long;

using std::cin;
using std::cout;

#define N 500005

i32 f[N];
i32 n, m;

i32 q[N], hh, tt;
i32 ans = 0;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i) {
        cin >> f[i];
        f[i] += f[i - 1];
    }

    hh = 1, tt = 0;
    q[++tt] = 0;
    for (i32 i = 1; i <= n; ++i) {
        while (tt >= hh && i - q[hh] > m)
            ++hh;
        // cout << f[i] << ' ' << f[q[hh]] << '\n';
        ans = std::max(ans, f[i] - f[q[hh]]);
        while (tt >= hh && f[i] <= f[q[tt]])
            --tt;
        q[++tt] = i;
    }

    cout << ans;

    return 0;
}