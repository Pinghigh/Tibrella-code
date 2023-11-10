#include <iostream>
#include <cstring>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

constexpr i64 mod = 998244353;

#define N 202
#define M 4003

i64 f[N][N<<1], g[N][N];

i64 a[N][M], s[N];

i32 n, m;

i64 ans;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i32 i = 1; i <= n; ++ i) 
        for (i32 j = 1; j <= m; ++ j) {
            cin >> a[i][j];
            s[i] += a[i][j];
            s[i] %= mod;
        }

    for (i32 col = 1; col <= m; ++ col) {
        memset(f,0,sizeof f);
        f[0][n] = 1;
        for (i32 i = 1; i <= n; ++ i)
            for (i32 j = 1; j <= 2*n; ++ j) {
                f[i][j] = f[i-1][j] + f[i-1][j+1] * (s[i] - a[i][col]) % mod;
                f[i][j] %= mod; 
                if (j > 0) f[i][j] = (f[i][j] + f[i-1][j-1] * a[i][col] % mod) % mod; 
            }
        for (i32 i = n+1; i <= 2*n; ++ i) ans = (ans - f[n][i]) % mod;
    }   

    g[0][0] = 1;
    for (i32 i = 1; i <= n; ++ i) {
        for (i32 j = 0; j <= n; ++ j) {
            g[i][j] = g[i-1][j];
            if (j > 0) g[i][j] = (g[i][j] + g[i-1][j-1]*s[i] % mod) % mod;
        }
    }
    for (i32 i = 1; i <= n; ++ i) ans = (ans + g[n][i]) % mod;

    cout << (ans + mod) % mod;

    return 0;
}