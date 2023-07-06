#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

auto max = [](auto a, auto b) { return a > b ? a : b; };
auto min = [](auto a, auto b) { return a < b ? a : b; };

const int N = 100005;
const double eps = 1e-5;

int n;
double l, r;
int m[N], f[N];
double c[N], lm[N], rm[N];

bool check(double val) {
    for (int i = 1; i <= n; ++i) {
        c[i] = val * i - f[i];
    }
    lm[1] = c[1];
    for (int i = 2; i < n; ++i) {
        lm[i] = max(lm[i - 1], c[i]);
    }
    rm[n] = c[n] - c[n - 1];
    for (int i = n - 1; i; --i) {
        rm[i] = max(rm[i + 1], c[n] - c[i - 1]);
    }

    for (int i = 2; i + 2 < n; ++i) {
        if (lm[i] + rm[i + 2] > 0) return true;
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> m[i];
        f[i] = f[i - 1] + m[i];
    }

    double l = 2, r = f[n] * 1.0 / n;
    double mid;
    while (r - l > eps) {
        mid = (r + l) / 2;
        // cout << mid << '\n';
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + eps;
        }
    }

    // int tmp = 0;
    // for (int i = 2; i <= n; ++i) {
    //     tmp = max(tmp, m[i]);
    // }

    cout << std::fixed << std::setprecision(3) << l << '\n';

    return 0;
}