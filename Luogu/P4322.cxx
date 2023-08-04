#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

using f128 = long double;
using i32 = int;
using i64 = long long;

#define N 2505

const f128 eps = 1e-4;

i32 k, n;
i64 s[N], p[N];
i32 fa[N], nex[N], son[N];

void add(i32 f, i32 s) {
    nex[s] = son[f];
    son[f] = s;
}

f128 f[N][N], val[N];
i32 siz[N];

void dfs(i32 nod) {
    // cout << nod << '\n';
    siz[nod] = 1;
    f[nod][0] = 0;
    f[nod][1] = val[nod];
    for (i32 to = son[nod]; to; to = nex[to]) {
        dfs(to);
        siz[nod] += siz[to];
        for (i32 i = std::min(siz[nod], k); i; --i)
            for (i32 j = 0, lim = std::min(siz[to], i - 1); j <= lim; ++j)
                f[nod][i] = std::max(f[nod][i], f[nod][i - j] + f[to][j]);
    }
}

bool check(f128 x) {
    memset(siz, 0, sizeof(i32) * (n + 1));

    for (i32 i = 1; i <= n; ++i)
        val[i] = p[i] - s[i] * x;

    for (i32 i = 0; i <= n; ++i)
        for (i32 j = 1; j <= k; ++j)
            f[i][j] = -1e20;

    dfs(0);

    return f[0][k] >= 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> k >> n;
    ++k;
    for (i32 i = 1; i <= n; ++i) {
        cin >> s[i] >> p[i] >> fa[i];
        add(fa[i], i);
    }

    f128 l = 0, r = 3;

    while (r - l > eps) {
        f128 mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }

    cout << std::fixed << std::setprecision(3) << l;

    return 0;
}