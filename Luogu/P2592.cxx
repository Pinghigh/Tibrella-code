#include <iostream>

using std::cin;
using std::cout;

const char endl = '\n';
const int N = 200;
const int K = 30;
const int mod = 12345678;
int f[N][N][K][K];  // m,f,m-f,f-m
int m, n, k;
auto max = [](auto a, auto b) { return a > b ? a : b; };

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> k;

    f[0][0][0][0] = 1;  // 什么都不放是一种方案
    for (int i = 0; i <= n; ++i) { // 需要带等号，不带等号只能推出 f[n-1][m] 和 f[n][m-1]
        for (int j = 0; j <= m; ++j) {
            for (int x = 0; x <= k; ++x) {
                for (int y = 0; y <= k; ++y) {
                    f[i + 1][j][x + 1][max(0, y - 1)] += f[i][j][x][y] %= mod;
                    f[i][j + 1][max(0, x - 1)][y + 1] += f[i][j][x][y] %= mod;
                }
            }
        }
    }

    int res = 0;
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= k; ++j) {
            res += f[n][m][i][j] %= mod;
        }
    }
    cout << res % mod << endl;

    return 0;
}