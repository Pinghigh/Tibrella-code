#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 500001

i32 q[N], tt, hh;
i64 f[N], s[N], x[N];
i32 n, d, k;

bool check(const i64& g) {
    for (i32 i = 1; i <= n; ++ i) f[i] = s[i];
    f[0] = 0;
    tt = 0, hh = 1;
    const i64 &l = d-g, &r = d+g;
    for (i32 i = n, cur = n; i >= 0; --i) {
        // cout << cur << '\n';
        // cout << hh << ' ' << tt << '\n';
        // cout << q[hh] << '\n';
        while (tt >= hh && x[q[hh]] > x[i] + r) ++hh;
        while (cur > i && x[cur] > x[i] + r) --cur;
        while (cur > i && x[cur] >= x[i] + l) {
            // cout << cur << ' ' << (x[cur] >= x[i] + l) << '\n';
            if (f[cur] <= 0) {--cur; continue;}
            while (tt >= hh && f[q[tt]] <= f[cur]) --tt;
            q[++tt] = cur--;
        }
        if (tt >= hh) f[i] += f[q[hh]];
        // cout << f[i] << '\n';
    }
    return f[0] >= k;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> d >> k;
    for (i32 i = 1; i <= n; ++ i) cin >> x[i] >> s[i];
    {
        i64 sum = 0;
        for (i32 i = 1; i <= n; ++ i) if (s[i] >= 0) sum += s[i];
        if (sum < k) {
            cout << "-1\n";
            return 0;
        }
        // cout << sum << '\n';
    }
    i64 l = 0, r = 1e12;
    while (r > l) {
        i64 mid = (l + r) >> 1;
        // cout << l << ' ' << mid << ' ' << r << '\n';
        if (check(mid)) 
            r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';

    // cout << check(100000000) << ' ' << f[0] << '\n';
    // for (i32 i = 0; i <= 20; ++ i) cout << f[i] << ' ';

    return 0;
}