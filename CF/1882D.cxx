#include <algorithm>
#include <iostream>
#include <vector>

using i32 = int;
using i64 = long long;

using std::cin;
using std::cout;

#define N 200005

std::vector<i32> g[N];
i64 a[N], siz[N];
i64 p[N], f[N];
i32 n;

void dfs(i32 u, i32 fa) {
    siz[u] = 1;
    f[u] = p[u] = 0;
    for (const auto& v : g[u]) {
        if (v != fa) {
            dfs(v, u);
            p[u] += p[v];
            siz[u] += siz[v];
            p[u] += siz[v] * (a[v] ^ a[u]);
        }
    }
}

void get_ans(i32 u, i32 fa) {
    for (const auto& v : g[u]) {
        if (v != fa) {
            f[v] = f[u] - siz[v] * (a[u] ^ a[v]) + (n - siz[v]) * (a[u] ^ a[v]);
            get_ans(v, u);
        }
    }
}

static void solve() {
    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
        g[i].clear();
    }
    for (i32 i = 1; i < n; ++i) {
        i32 x, y;
        cin >> x >> y;
        g[x].emplace_back(y), g[y].emplace_back(x);
    }
    dfs(1, 0);
    f[1] = p[1];
    get_ans(1, 0);
    for (i32 i = 1; i <= n; ++i)
        cout << f[i] << ' ';
    cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}