// 圆方树

#include <iostream>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 500001

template <typename T>
static void chkmin(T& a, const T& b) {
    if (a > b) a = b;
}

std::vector<i32> g[N], yf[N << 1];

i32 n, m, cnt;

i32 dfn[N], low[N];
i32 stk[N];

void tarjan(const i32& u) {
    static i32 top = 0, tim = 0;
    dfn[stk[++top] = u] = low[u] = ++tim;
    
    for (const auto& v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            chkmin(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                ++cnt;
                do yf[cnt].emplace_back(stk[top]), yf[stk[top]].emplace_back(cnt); while (stk[top--] != v);
                yf[u].emplace_back(cnt); yf[cnt].emplace_back(u);
            }
        } else chkmin(low[u], dfn[v]); 
    }
}

i32 fa[N];

void dfs(const i32& u, const i32& fa) {
    ::fa[u] = fa;
    for (const auto& v : yf[u]) if (v != fa) dfs(v, u);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    cnt = n;
    i32 u, v;
    cin >> u >> v;
    while (u && v) {
        g[u].emplace_back(v); g[v].emplace_back(u);
        cin >> u >> v;
    }
    cin >> u >> v;
    tarjan(1);
    dfs(u, 0);
    // for (i32 i = 1; i <= cnt; ++ i) cout << fa[i] << ' ' << i << '\n';
    // cout << "FUCK" << std::endl;
    i32 ans = 0x3f3f3f3f;
    while (fa[v] != u) if ((v = fa[v]) <= n)chkmin(ans, v);    
    if (ans == 0x3f3f3f3f) cout << "No solution";
    else cout << ans << '\n';

    return 0;
}