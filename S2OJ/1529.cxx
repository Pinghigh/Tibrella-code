#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;
using f64 = double;

#define N 100005

i32 n, q;
i64 k[N], b[N];
i64 ans, x;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i)
        cin >> k[i] >> b[i];

    cin >> q;
    while (q--) {
        ans = -0x3f3f3f3f3f;
        cin >> x;
        for (i32 i = 1; i <= n; ++i)
            for (i32 j = 1; j <= n; ++j) {
                if (i != j) ans = std::max(ans, k[i] * (k[j] * x + b[j]) + b[i]);
            }
        cout << ans << '\n';
    }
    return 0;
}