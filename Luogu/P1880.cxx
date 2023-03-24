#include <climits>
#include <cstdio>
#include <iostream>


using std::cin;
using std::cout;
using std::endl;

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define N 514 // Koishi is BEST!!

int ori[N];  // original data
int pre[N], f[N][N];
int n;
int res;

int main() {
    // std::ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> ori[i];
        pre[i] = pre[i - 1] + ori[i];
    }
    for (int i = n + 1; i <= 2 * n; ++i) {
        pre[i] = pre[i - 1] + ori[i - n];
    }

    // for (int i = 1; i <= 2*n; ++ i)
    //     cout << "[pre] i:" << i << " val: " << pre[i] << endl;

    res = INT_MAX;
    for (int len = 2; len <= n; ++len) {          // 大区间长度
        for (int i = 1; i + len - 1 <= 2 * n; ++i) {  // 大区间左端点
            int j = i + len - 1;
            f[i][j] = INT_MAX;

            for (int pos = i; pos < j; ++pos) {
                // printf("[data] f[i][j] %d f[i][pos] %d f[pos + 1][j] %d pre[j] %d pre[i - 1] %d\n", f[i][j], f[i][pos], f[pos + 1][j], pre[j], pre[i - 1]);
                f[i][j] = min(f[i][j], f[i][pos] + f[pos + 1][j] + pre[j] - pre[i - 1]);
                // printf("[mov] %d to i: %d j: %d\n", f[i][j], i, j);
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        res = min(res, f[i][i + n - 1]);
    }
    cout << res << endl;

    res = INT_MIN;
    for (int len = 2; len <= n; ++len) {          // 大区间长度
        for (int i = 1; i + len - 1 <= 2 * n; ++i) {  // 大区间左端点
            int j = i + len - 1;
            f[i][j] = INT_MIN;

            for (int pos = i; pos < j; ++pos) {
                f[i][j] = max(f[i][j], f[i][pos] + f[pos + 1][j] + pre[j] - pre[i - 1]);
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        res = max(res, f[i][i + n - 1]);
    }
    cout << res;

    return 0;
}
