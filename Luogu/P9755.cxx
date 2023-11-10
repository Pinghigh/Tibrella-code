#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <bitset>
#include <ext/pb_ds/priority_queue.hpp>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;
using i128 = __int128;

template <typename T>
static void chkmin(T& a, const T& b) {
    if (a > b) a = b;
}

#define N 100001

i32 n;
std::vector<i32> g[N];
i64 a[N];
i32 b[N], c[N];

// 预处理 dfn 防止多次递归常数过大
std::vector<i32> dfn;
i32 fa[N];
void dfs(const i32& u, const i32& f) {
    dfn.emplace_back(u);
    fa[u] = f;
    for (const auto& v : g[u]) if (v != f) dfs(v, u);
}


static i128 calc(const i32& l, const i32& r, const i32& i) { // 从 l 开始，长到第 r 天的高度
    // const i32& l = d - len + 1;
    if (c[i] >= 0)
        return (r - l + 1) * (i128)b[i] + (l + r) * (i128)(r - l + 1) * c[i] / 2;
    else {
        const i32& p = (b[i]-1) / (-c[i]); // 最后一个 delta >= 0 的天
        if (l > p) return r-l+1;
        else if (r <= p) return (i128)(r - l + 1) * b[i] + (l + r) * (i128)(r - l + 1) * c[i] / 2;
        else return (i128)(p - l + 1) * b[i] + (i128)(l + p) * (p - l + 1) * c[i] / 2 + r - p; 
    }
}

i32 l[N]; // 最晚得在哪一天种下
i32 t[N];
struct cmp {
    bool operator()(const i32& a, const i32& b) const { return l[a] > l[b]; }
};
bool check(const i32& d) {
    // vis.reset();
    for (i32 i = 1; i <= n; ++ i) {
        i32 l = 1, r = d;
        while (l < r) {
            i32 mid = (1 + l + r) >> 1;
            if (calc(mid, d, i) >= a[i]) l = mid;
            else r = mid - 1;
        }
        ::l[i] = std::min(l, n);
        // cout << ::l[i] << ' ';
    }

    // 倒着扫一遍 dfs 序列，贡献到父亲上
    for (const auto& nod : dfn) {
        if (!l[nod]) return false; // 剪枝 
        chkmin(l[fa[nod]], l[nod] - 1);
    }
    for (i32 i = 0; i <= n; ++ i) t[i] = 0;
    for (i32 i = 1; i <= n; ++ i) ++t[l[i]];
    for (i32 i = 1; i <= n; ++ i) if ((t[i] += t[i-1]) > i) return false;
    return true;

    // 贪心模拟
    // __gnu_pbds::priority_queue<i32, cmp, __gnu_pbds::binary_heap_tag> q;
    // q.push(1);
    // i32 idx = 0;
    // while (q.size()) {
    //     i32 u = q.top();
    //     vis[u] = true;
    //     q.pop();
    //     if (++idx > l[u]) return false;
    //     for (const auto& v : g[u]) if (v != fa[u] && !vis[v]) q.push(v);
    // }

    // for (i32 i = 1; i <= n; ++ i) if (!vis[i]) return false;
    // return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++ i) cin >> a[i] >> b[i] >> c[i];
    for (i32 i = 1; i < n; ++ i) {
        i32 u, v;
        cin >> u >> v;
        g[u].emplace_back(v); g[v].emplace_back(u);
    }

    // 预处理 dfn
    dfs(1, 0);
    std::reverse(dfn.begin(), dfn.end());

    i32 l = 1, r = 1e9;
    while (r > l) {
        i32 mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
        // cout << l << ' ' << r << '\n';
    }
    cout << l << '\n';
    // cout << '\n' << check(5);
    // cout << calc(2, 4, 1);


    return 0;
}