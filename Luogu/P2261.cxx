#include <iostream>

using std::cin;
using std::cout;

namespace kgs {
    using i32 = int;
    using i64 = long long;

    i64 n, k, ans;

    void main() {
        std::ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        cin >> n >> k;
        ans = n * k;
        for (i64 l = 1, r, x; l <= n && l <= k; l = r + 1) {
            x = (k / l);
            r = (k / x);
            if (r > n) r = n;
            ans -= (r - l + 1) * (l + r) * x >> 1;
        }
        cout << ans;
    }
}  // namespace kgs

int main() {
    kgs::main();

    return 0;
}