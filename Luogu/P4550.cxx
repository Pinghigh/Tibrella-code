#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

#define N 10005

using i32 = int;
using f64 = double;

f64 f[N], g[N];
i32 n;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        f[i + 1] = i * 1.0 / (n - i) + f[i] + 1;
        g[i + 1] = i * 2.0 / (n - i) * f[i + 1] + 1.0 * i / (n - i) + g[i] + 2 * f[i] + 1;
    }

    cout << std::fixed << std::setprecision(2) << (f[n] + g[n]) / 2;

    return 0;
}