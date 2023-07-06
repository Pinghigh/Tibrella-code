#include <iostream>

using std::cin;
using std::cout;

#define N 50004

using i32 = int;
using i64 = long long;
using f64 = double;

i64 f[N];
i32 n, l, c[N];
i64 sum[N];

i64 q[N], hh, tt;

i64 a(i32 i) {
    return sum[i] + i;
}

i64 b(i32 i) {
    return sum[i] + i + l + 1;
}

double calc(i32 x, i32 y) {
    return (f[x] + b(x) * b(x) - f[y] - b(y) * 1.0 * b(y)) / (b(x) - b(y) * 1.0);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> l;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        sum[i] = sum[i - 1] + c[i];
    }

    hh = 1, tt = 0;
    q[++tt] = 0;
    for (int i = 1; i <= n; ++i) {
        while (tt > hh && 2 * a(i) > calc(q[hh], q[hh + 1]))
            ++hh;
        f[i] = f[q[hh]] + (a(i) - b(q[hh])) * (a(i) - b(q[hh]));
        while (tt > hh && calc(i, q[tt - 1]) < calc(q[tt - 1], q[tt]))
            --tt;
        q[++tt] = i;
    }
    cout << f[n];

    return 0;
}