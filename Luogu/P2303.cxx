#include <cmath>
#include <iostream>

using std::cin;
using std::cout;

namespace tkgs {
    using i32 = int;
    using i64 = long long;

    namespace math {
        i64 phi(i64 x) {
            i64 res = x;
            for (i64 i = 2; i * i <= x; ++i) {
                if (!(x % i)) {
                    res = res / i * (i - 1);
                    while (!(x % i))
                        x /= i;
                }
            }
            if (x > 1) res = res / x * (x - 1);
            return res;
        }

    }  // namespace math

    void main() {
        i64 n;
        cin >> n;

        i64 ans = 0;
        for (i64 i = 1, lim = sqrt(n); i <= lim; ++i) {
            if (!(n % i)) {
                ans += i * math::phi(n / i);
                if (n / i != i) ans += (n / i) * math::phi(i);
            }
        }

        cout << ans;
    }
}  // namespace tkgs

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    tkgs::main();

    return 0;
}