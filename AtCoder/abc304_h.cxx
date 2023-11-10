#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <bitset>

using std::cin; using std::cout;

using i32 = int;
using i64 = long long;

#define N 200001

template <typename T>
static void chkmin(T& a, const T& b) {
    if (a > b) a = b;
}

std::vector<i32> g[N];
i32 ind[N];
i32 l[N], r[N];
std::bitset<N> vis;

void dfs(const i32& u) {
    vis[u] = true;
    for (const auto& v : g[u]) {
        if (!vis[v]) dfs(v);
        chkmin(r[u], r[v]-1);
    }
}

template<i32* v>
struct cmp {
    bool operator()(const i32& a, const i32& b) const& {
        return v[a] > v[b];
    }
};
i32 ans[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, m;
    cin >> n >> m;
    for (i32 i = 1; i <= m; ++ i) {
        i32 u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        ++ind[v];
    }
    for (i32 i = 1; i <= n; ++ i) cin >> l[i] >> r[i];  
    for (i32 i = 1; i <= n; ++ i) if (!vis[i]) dfs(i);
    std::priority_queue<i32, std::vector<i32>, cmp<r>> qa;
    std::priority_queue<i32, std::vector<i32>, cmp<l>> ql; // 当前还不能成为答案的点（l>idx）

    for (i32 i = 1; i <= n; ++ i) if (!ind[i]) ql.emplace(i);

    // cout << qa.size();
    for(;;) {
        static i32 idx = 0;
        ++idx;
        while (!ql.empty() && l[ql.top()] <= idx) {
            qa.emplace(ql.top());
            ql.pop();
        }
        if (qa.empty()) break;
        i32 u = qa.top();
        qa.pop();
        ans[u] = idx;
        if (ans[u] > r[u]) {cout << "No"; return 0;}
        for (const auto& v : g[u]) 
            if (!--ind[v]) ql.emplace(v);
    }
    for (i32 i = 1; i <= n; ++ i) if (!ans[i]) {cout << "No"; return 0;}
    
    cout << "Yes\n";
    for (i32 i = 1; i <= n; ++ i) cout << ans[i] << ' ';

    return 0;
}