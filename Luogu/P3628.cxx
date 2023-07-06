#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 1000006

i64 a, b, c;
i64 sum[N];
i32 n;
i64 f[N], q[N], hh, tt;

i64 y(i64 x) {
    return f[x] + a * sum[x] * sum[x] - b * sum[x];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> a >> b >> c;
    for (i32 i = 1; i <= n; ++i) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }

    hh = 1;
    tt = 0;
    q[++tt] = 0;
    for (i32 i = 1; i <= n; ++i) {
        while (hh < tt && (y(q[hh + 1]) - y(q[hh])) > 2 * a * sum[i] * (sum[q[hh + 1]] - sum[q[hh]]))
            ++hh;
        f[i] = y(q[hh]) - 2 * a * sum[i] * sum[q[hh]] + b * sum[i] + c + a * sum[i] * sum[i];
        while (hh < tt && (y(q[tt]) - y(q[tt - 1])) * (sum[i] - sum[q[tt]]) < (y(i) - y(q[tt])) * (sum[q[tt]] - sum[q[tt - 1]]))
            --tt;
        q[++tt] = i;
    }

    cout << f[n];

    return 0;
}