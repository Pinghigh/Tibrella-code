#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 3005

i64 f[N][N][2];
i32 n, m;

constexpr i64 mod = 1e9 + 7;

inline void add(i64& a, const i64& b) {
    a += b;
    if (a >= mod) a -= mod;
}

inline void add(i64& a, const i64& b, const i64& c) {
    if (b + c >= mod)
        add(a, b + c - mod);
    else
        add(a, b + c);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i32 i = 0; i <= n; ++i)
        f[0][i][i == 0] = 1;

    for (i32 i = 1; i <= m; ++i) {
        for (i32 j = 0; j <= n; ++j) {
            if (j) {
                // 先常规转移
                add(f[i][j][0], f[i - 1][j - 1][0]);
                add(f[i][j][1], f[i - 1][j - 1][1], f[i - 1][j][1]);
                add(j == 1 ? f[i][j][1] : f[i][j][0], f[i - 1][j][0]);  // j=1 的话算触底一次。
            }
            if (j < n) {
                add(f[i][j][1], f[i - 1][j + 1][1], f[i - 1][j][1]);
                if (j == 0)
                    add(f[i][j][1], f[i - 1][j + 1][0]);  // 触底
                else
                    add(f[i][j][0], f[i - 1][j + 1][0], f[i - 1][j][0]);
            }
        }
    }

    i64 ans = 0;
    for (i32 i = 0; i <= n; ++i)
        add(ans, f[m][i][1]);
    cout << ans;

    return 0;
}