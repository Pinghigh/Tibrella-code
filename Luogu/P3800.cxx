#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

#define N 4005

int f[N][N];
int q[N], hh, tt;
int v[N][N], n, m, k, t;
int t1, t2, t3;  // x, y, v

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> k >> t;
    for (int i = 1; i <= k; ++i) {
        cin >> t1 >> t2 >> t3;
        v[t1][t2] = t3;
    }

    for (int i = 1; i <= n; ++i) {
        // 直接往下走
        for (int j = 1; j <= m; ++j)
            f[i][j] = f[i - 1][j];
        tt = 0, hh = 1;
        for (int j = 1; j <= m; ++j) {
            if (hh <= tt && q[hh] + t < j) ++hh;
            while (hh <= tt && f[i - 1][j] >= f[i - 1][q[tt]])
                --tt;
            q[++tt] = j;
            f[i][j] = max(f[i - 1][q[hh]] + v[i][j], f[i][j]);
        }
        tt = 0, hh = 1;
        for (int j = m; j; --j) {
            if (hh <= tt && q[hh] - t > j) ++hh;
            while (hh <= tt && f[i - 1][j] >= f[i - 1][q[tt]])
                --tt;
            q[++tt] = j;
            f[i][j] = max(f[i - 1][q[hh]] + v[i][j], f[i][j]);
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; ++ i) ans = max(ans, f[n][i]);

    cout << ans << '\n';

    return 0;
}