#include <cmath>
#include <iostream>
#include <iomanip>

using f64 = double;

constexpr f64 gold = 0.6180339;
constexpr f64 eps = 1e-6;

using i32 = int;
using i64 = long long;

using std::cin;
using std::cout;

#include <vector>

std::vector<f64> c;
i32 n;
f64 l, r;

f64 f(const f64& x) {
    f64 res = 0;
    for (const auto& c : ::c)
        res = res * x + c;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> l >> r;
    {
        f64 x;
        for (i32 i = 0; i <= n; ++i) {
            cin >> x;
            c.emplace_back(x);
        }
    }

    bool nl = 1, nr = 1;  // l/r is needed to calc?

    f64 fl, fr; // f(l), f(r)
    while (r - l > eps) {
        const f64& len = (r - l);
        f64 rdot = len*gold+l, ldot = len*(1-gold)+l;
        if (nl) fl = f(ldot);
        if (nr) fr = f(rdot);

        if (fl > fr) 
            r = rdot, fr = fl, nl = true, nr = false;
        else 
            l = ldot, fl = fr, nr = true, nl = false;
    }

    cout << std::setprecision(5) << std::fixed << r;

    return 0;
}