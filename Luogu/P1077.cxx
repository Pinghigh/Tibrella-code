#include <iostream>

using std::cin;
using std::cout;

#define endl '\n'
#define N 105

constexpr int mod = 1e6 + 7;

int a[N];
int f[N][N];
int n, m;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr)->tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            f[i][j] = f[i-1][j];
            for (int k = 1; k <= a[i] && k <= j; ++k) {
                f[i][j] += f[i - 1][j - k];
                f[i][j] %= mod;
            }
        }
    }
    cout << f[n][m] << endl;

    return 0;
}