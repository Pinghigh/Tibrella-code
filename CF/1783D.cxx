#include <iostream>

using std::cin;
using std::cout;

using i64 = long long;

#define N 305

const int mod = 998244353;
const int low = 90000;

i64 n;
i64 a[N];
i64 f[305][(low << 1) + 10];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    f[0][a[2] + low] = 1;
    for (int i = 0; i < n - 2; ++i) {
        for (int j = -low; j <= low; ++j) {
            if (!f[i][j + low]) continue;
            (f[i + 1][a[i + 3] + j + low] += f[i][j + low]) %= mod;
            if (j) (f[i + 1][a[i + 3] - j + low] += f[i][j + low]) %= mod;
        }
    }

    i64 res = 0;
    for (int i = 0; i <= (low << 1); ++i) {
        res += f[n - 2][i];
        res %= mod;
    }

    cout << res;

    return 0;
}