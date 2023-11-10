#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 100001

i32 f[N];
i64 g[N], s[N];
i32 q[N], hh, tt;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    for (i32 i = 1; i <= n; ++ i) cin >> s[i];
    std::reverse(s+1,s+n+1);
    for (i32 i = 1; i <= n; ++ i) s[i] += s[i-1]; // prefix sum

    hh = 1, tt = 0;
    q[++tt] = 0;
    for (i32 i = 1; i <= n; ++ i) {
        while (hh < tt && s[q[hh+1]] + g[q[hh+1]] <= s[i]) ++hh;
        f[i] = f[q[hh]] + 1; g[i] = s[i] - s[q[hh]];
        while (hh < tt && s[q[tt]] + g[q[tt]] >= s[i] + g[i]) --tt;
        q[++tt] = i;
    }
    cout << f[n] << '\n';

    return 0;
}