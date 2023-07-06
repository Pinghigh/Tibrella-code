#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <climits>

using std::cin;
using std::cout;
using std::max;

#define N 2005

#define int long long

int ap[N], bp[N], as[N], bs[N], f[N][N];
int n, maxp, w;

int q[N], hh, tt;

int calcA(int& i, int& k) {
    return f[i - w - 1][k] + k * ap[i];
}
int calcB(int& i, int& k) {
    return f[i - w - 1][k] + k * bp[i];
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> maxp >> w;

    for (int i = 1; i <= n; ++i)
        cin >> ap[i] >> bp[i] >> as[i] >> bs[i];

    memset(f, 128, sizeof f);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= as[i]; ++j)
            f[i][j] = -j * ap[i];
        for (int j = 0; j <= maxp; ++j)
            f[i][j] = max(f[i - 1][j], f[i][j]);
        if (i <= w) continue;
        tt = 0;
        hh = 1;
        // q[++tt] = 0;
        for (int j = 0; j <= maxp; ++j) {
            if (hh <= tt && j - q[hh] > as[i]) ++hh;
            if (hh <= tt) f[i][j] = max(f[i][j], calcA(i, q[hh]) - j * ap[i]);
            int tmp = calcA(i, j);
            while (hh <= tt && tmp >= calcA(i, q[tt]))
                --tt;
            q[++tt] = j;
        }
        tt = 0;
        hh = 1;
        // q[++tt] = 0;
        for (int j = maxp; ~j; --j) {
            if (hh <= tt && q[hh] > j + bs[i]) ++hh;
            if (hh <= tt) f[i][j] = max(f[i][j], calcB(i, q[hh]) - j * bp[i]);
            int tmp = calcB(i, j);
            while (hh <= tt && tmp >= calcB(i, q[tt]))
                --tt;
            q[++tt] = j;
        }
    }

    int ans = 0;
    for (int i = 0; i <= maxp; ++i)
        ans = max(ans, f[n][i]);

    cout << ans << '\n';

    return 0;
}