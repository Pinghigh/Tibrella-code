#include <iostream>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 300005

std::vector<i32> g[N], dfn;

i32 f[N];
i32 cnt[N], fa[N];

void dfs(const i32& u, const i32& fa) {
    ::fa[u] = fa;
    dfn.emplace_back(u);
    cnt[u] = g[u].size() - 1;
    for (const auto& v : g[u]) if (v != fa) dfs(v, u);
}

static bool check(const i32& k) {
    for (const auto& u : dfn) f[u] = 0;
    for (const auto& u : dfn) {
        f[u] += cnt[u] - k;
        if (f[u] > 0) f[fa[u]] += f[u];
    }
    return f[1] <= 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    i32 n;
    cin >> n;
    for (i32 i = 1; i < n; ++ i) {
        i32 x, y;
        cin >> x >> y;
        g[x].emplace_back(y); g[y].emplace_back(x);
    }
    g[1].emplace_back(0);
    dfs(1, 0);
    std::reverse(dfn.begin(), dfn.end());

    i64 l = g[1].size() - 1, r = 0;
    for (i32 i = 1; i <= n; ++ i) r = std::max(r * 1ull, g[i].size() - 1ull);
    // cout << l << ' ' << r << '\n';
    while (l < r) {
        i64 mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';

    // cout << dfs(1, 0, 0, 2);

    return 0;
}