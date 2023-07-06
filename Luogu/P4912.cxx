#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::max;

using i32 = int;
using i64 = long long;

constexpr i32 mov = 2501;
constexpr i32 MIN = 0xc0c0c0c0;

#define N 55
#define M 5003

i32 a[N], b[N], w[N][N];
i32 f[N][M << 1];
i32 n, m;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(f, 0xc0, sizeof f);

    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i)
        cin >> a[i] >> b[i];
    for (i32 i = 1; i <= n; ++i)
        for (i32 j = 1; j <= n; ++j)
            cin >> w[i][j];

    f[0][mov] = 0;

    for (i32 i = 1; i <= n; ++i) {
        for (i32 j = a[i]; j < (mov << 1); ++j) {
            for (i32 k = 0; k < i; ++k) {
                if (f[k][j - a[i]] != MIN) {
                    f[i][j] = max(f[i][j], f[k][j - a[i]] + b[i] + w[k][i]);
                }
            }
        }
    }

    i32 ans = MIN;
    for (i32 i = 0; i <= n; ++i)
        ans = max(f[i][m + mov], ans);
    cout << (ans != MIN ? ans : -1);

    return 0;
}