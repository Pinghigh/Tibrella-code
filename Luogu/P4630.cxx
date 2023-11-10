#include <iostream>
#include <vector>

using i32 = int;
using i64 = long long;

using std::cin;
using std::cout;

template <typename T>
static void chkmin(T& a, const T& b) {
    if (a > b) a = b;
}

#define N 200001

i32 cnt;
i32 n, m;
std::vector<i32> g[N], yf[N<<1];
i32 w[N<<1];

i32 dfn[N], stk[N], low[N];
i32 tmpsiz;
void tarjan(const i32& u) {
    ++tmpsiz;
    static i32 top = 0, tim = 0;
    dfn[stk[++top] = u] = low[u] = ++tim;
    w[u] = -1;
    for (const auto& v : g[u]) 
        if (!dfn[v]) {
            tarjan(v); chkmin(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                ++w[++cnt]=1;
                do yf[cnt].emplace_back(stk[top]),
                   yf[stk[top]].emplace_back(cnt); while (++w[cnt], stk[top--] != v);
                yf[cnt].emplace_back(u); yf[u].emplace_back(cnt);
            }
        } else chkmin(low[u], dfn[v]);
}

i64 ans = 0;
i32 siz[N<<1];

void dfs(const i32& u, const i32& fa) {
    // cout << u << '\n';
    siz[u] = u <= n;
    for (const auto& v : yf[u]) 
        if (v != fa) {
            dfs(v, u);
            ans += siz[u] * 2ll * siz[v] * w[u];
            siz[u] += siz[v];
        }
    ans += siz[u] * 2ll * (tmpsiz-siz[u]) * w[u];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    cnt = n;
    for (i32 i = 1; i <= m; ++ i) {
        i32 u, v;
        cin >> u >> v;
        g[u].emplace_back(v); g[v].emplace_back(u);
    }
    for (i32 i = 1; i <= n; ++ i) if (!dfn[i]) tmpsiz=0, tarjan(i), dfs(i, 0);

    cout << ans << '\n';

    return 0;
}