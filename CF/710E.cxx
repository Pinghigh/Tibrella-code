#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::min;

#define N 10000007

using i32 = int;
using i64 = long long;

i64 n, x, y;
i64 f[N << 1];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(f, 0x3f, sizeof f);

    cin >> n >> x >> y;
    f[0] = 0;
    i32 t = 6;
    for (int i = 1; i <= (n << 1); ++i) {
        f[i] = min(f[i], min(f[i - 1] + x, f[i + 1] + x));
        if ((i & 1)) {
            f[i] = min(f[i], f[(i + 1) >> 1] + y + x);
        } else {
            f[i] = min(f[i], f[i >> 1] + y);
        }
    }

    cout << f[n];

    return 0;
}