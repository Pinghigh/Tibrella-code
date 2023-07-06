#include <algorithm>
#include <cmath>
#include <iostream>

using std::cin;
using std::cout;

#define N 1000006

using i32 = long long;

i32 n;
i32 a[N], c[N];
i32 sum;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    sum /= n;
    for (int i = 2; i <= n; ++i)
        c[i] = c[i - 1] + (sum - a[i - 1]);

    std::sort(c + 1, c + n + 1);

    i32 ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += abs(c[(n + 1) >> 1] - c[i]);

    cout << ans;

    return 0;
}