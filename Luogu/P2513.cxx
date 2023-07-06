#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

#define endl '\n'
#define N 1514
#define K 1514
#define mod 10000

int f[N][K];
int sum;

int n, k;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;

    f[1][0] = 1;

    for (int i = 2; i <= n; ++i) {
        sum = 0;
        for (int j = 0; j <= k; ++j) {
            (sum += f[i - 1][j]) %= mod;
            f[i][j] = sum;
            if (j >= i - 1) sum = (sum - f[i - 1][j - i + 1] % mod + mod) % mod;
        }
    }

    cout << f[n][k];

    return 0;
}