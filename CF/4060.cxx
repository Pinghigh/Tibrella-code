#include <cstring>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

using f64 = double;
using i32 = int;

i32 t;
i32 n;
f64 p, q, f[10010][2];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> n >> p >> q;
        if (n > 100) n = 100;
        f[0][0] = 0;
        f[0][1] = 1;                    // 剩余 0，该 Bob 取，Alice 赢
        for (int i = 1; i <= n; ++i) {  // 滚动数组
            f64 pnow = p, qnow = q;
            if (f[i - 1][1] >= f[i - 1][0]) {  // 第 i 个留给 Bob 更好
                pnow = 1 - pnow;
                qnow = 1 - qnow;
            }
            f[i][0] = (pnow * (1 - qnow) * f[i - 1][0] + (1 - pnow) * f[i - 1][1]) / (1 - qnow * pnow);
            f[i][1] = (qnow * (1 - pnow) * f[i - 1][1] + (1 - qnow) * f[i - 1][0]) / (1 - pnow * qnow);
        }
        cout << std::fixed << std::setprecision(8) << f[n][0] << '\n';
    }

    return 0;
}