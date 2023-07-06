#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i64 = long long;
using f64 = double;

#define N 100005

const f64 eps = 1e-5;

i64 n, p;
i64 a[N], b[N];
i64 sumW;

bool check(f64 tim) {
    f64 tmp = 0;
    for (int i = 1; i <= n; ++i) {
        tmp += std::max(tim * a[i] - b[i], 0.0);
    }
    return tmp <= p * tim;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> p;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
        sumW += a[i];
    }
    if (sumW <= p) {
        cout << "-1";
        return 0;
    }

    f64 l, r, mid;
    l = 0, r = 10000000000;
    while (r - l > eps) {
        mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid - eps;
    }
    cout << std::fixed << r;

    return 0;
}