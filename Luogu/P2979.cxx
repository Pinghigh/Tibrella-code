#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

template <typename T>
static inline void chkmax(T& a, const T& b) {
    if (a < b) a = b;
}

#define T 1001
#define N 101

i32 f[N][T];
i32 h[N], v[N], ch[N] /* compressed height */ ;
 
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, t, k;
    cin >> n >> t >> k;

    for (i32 i = 1; i <= n; ++i) {cin >> v[i] >> h[i]; ch[i] = h[i]/5<<2;}

    for (i32 i = 1; i <= n; ++i)
        for (i32 j = h[i]; j <= t; ++j)
            f[i][j] = std::max(f[i-1][j], f[i][j-h[i]] + v[i]);
    i32 res = f[n][t];
    for (i32 x = 1; x <= n; ++x) {
        if (h[x] >= k) {
            for (i32 i = 1; i <= n; ++i) {
                for (i32 j = 0; j <= t-h[x]; ++j) {
                    f[i][j] = f[i-1][j];
                    if (j >= ch[i]) chkmax(f[i][j], f[i][j-ch[i]] + v[i]);
                }
            }
            chkmax(res, f[n][t-h[x]]+v[x]);
        }
    }

    cout << res;

    return 0;
}