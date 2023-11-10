#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

#include <bitset>
#include <vector>

#define N 100005

using i32 = int;
using i64 = long long;
using pii = std::pair<int, int>;

std::vector<pii> g[N];
i32 oddcnt;

i32 dep[N], f[N][2];
i32 e[N];  // 边下放到点
std::bitset<N> vis, rt;

void dfs(i32 u) {
    vis[u] = true;
    for (const auto& to : g[u]) {
        const i32 &id = to.first, &v = to.second;
        if (id != e[u]) {
            if (vis[v]) {  // 返祖边
                if (dep[v] <= dep[u]) {
                    bool eve = (dep[u] - dep[v]) & 1;  // 环长是 dep[u]-dep[v]+1
                    ++f[u][eve], --f[v][eve];
                    if (!eve) ++oddcnt;
                }
            } else {
                e[v] = id;
                dep[v] = dep[u] + 1;
                dfs(v);
                f[u][0] += f[v][0], f[u][1] += f[v][1];
            }
        }
    }
}

int main() {
    i32 n, m;
    cin >> n >> m;
    for (i32 i = 1; i <= m; ++i) {
        i32 x, y;
        cin >> x >> y;
        g[x].emplace_back(i, y), g[y].emplace_back(i, x);
    }

    for (i32 i = 1; i <= n; ++i)
        if (!vis[i]) rt[i] = 1, dfs(i);

    i32 ans = 0;

    for (i32 i = 1; i <= n; ++i)
        ans += (f[i][0] == oddcnt && !f[i][1] && !rt[i]);

    ans += (oddcnt == 1);

    cout << ans;

    return 0;
}