#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

#define N 300005

using i32 = int;
using i64 = long long;

i64 t[N], c[N], f[N];
i64 q[N], hh, tt;
i64 sumt[N], sumc[N];
i32 n, s;

i64 bin_search(i64 k) {
    if (hh == tt) return q[hh];
    i32 l = hh, r = tt;
    while (l < r) {
        i32 mid = (l + r) >> 1;
        if (f[q[mid + 1]] - f[q[mid]] <= k * (sumc[q[mid + 1]] - sumc[q[mid]]))
            l = mid + 1;
        else
            r = mid;
    }
    return q[l];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(f, 0x3f, sizeof f);

    cin >> n >> s;
    for (i32 i = 1; i <= n; ++i) {
        cin >> t[i] >> c[i];
        sumt[i] = sumt[i - 1] + t[i];
        sumc[i] = sumc[i - 1] + c[i];
    }

    f[0] = 0;
    hh = 1, tt = 0;
    q[++tt] = 0;
    for (i64 i = 1; i <= n; ++i) {
        i64 j = bin_search(s + sumt[i]);
        f[i] = f[j] - (s + sumt[i]) * sumc[j] + sumt[i] * sumc[i] + s * sumc[n];
        while (hh < tt && (f[q[tt]] - f[q[tt - 1]]) * (sumc[i] - sumc[q[tt]]) >= (f[i] - f[q[tt]]) * (sumc[q[tt]] - sumc[q[tt - 1]]))
            --tt;
        q[++tt] = i;
    }

    cout << f[n];

    return 0;
}