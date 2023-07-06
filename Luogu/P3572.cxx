#include <cstring>
#include <iostream>

#define N 1000005

using i32 = int;
using i64 = long long;

using std::cin;
using std::cout;

i64 d[N];
i32 f[N];
i32 n, que, k;
i32 q[N], hh, tt;

void solve() {
    hh = 1, tt = 0;
    q[++tt] = 1;
    for (i32 i = 2; i <= n; ++i) {
        while (hh < tt && i - q[hh] > k)
            ++hh;
        f[i] = f[q[hh]] + (d[i] >= d[q[hh]]);
        while (hh < tt && ((f[i] < f[q[tt]]) || (f[i] == f[q[tt]] && d[i] >= d[q[tt]])))
            --tt;
        q[++tt] = i;
    }
    cout << f[n] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i)
        cin >> d[i];
    cin >> que;
    while (que--) {
        cin >> k;
        solve();
        if (que) memset(f, 0, sizeof f);
    }

    return 0;
}