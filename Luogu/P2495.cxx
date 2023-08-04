#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define all(x) x.begin(), x.end()

i64 inf = 0x3f3f3f3f3f3f3f3f;

struct edge {
    i32 to;
    i64 cost;

    edge(i32 a, i32 b) : to(a), cost(b){};
};

#define N 250005

std::vector<edge> tree[N], vir[N];

void add(std::vector<edge>* g, i32 fr, i32 to, i64 cost) {
    g[fr].emplace_back(edge(to, cost));
    g[to].emplace_back(edge(fr, cost));
}

i32 n, m;
i32 t1, t2, t3;

i32 wson[N], fa[N], dep[N], siz[N];

/* --- --- --- */
/*    树剖     */

/* 常数小，跑不满，好想 */

void get_siz(i32 nod) {
    siz[nod] = 1;
    for (auto& e : tree[nod]) {
        if (e.to != fa[nod]) {
            fa[e.to] = nod;
            dep[e.to] = dep[nod] + 1;
            get_siz(e.to);
            siz[nod] += siz[e.to];
            if (siz[e.to] > siz[wson[nod]]) wson[nod] = e.to;
        }
    }
}

i32 dfn[N], tim, adfn[N], top[N];

void get_dfn(i32 nod, i32 tp) {
    dfn[nod] = ++tim;
    adfn[tim] = nod;
    top[nod] = tp;
    if (wson[nod]) get_dfn(wson[nod], tp);
    for (auto& e : tree[nod])
        if (e.to != fa[nod] && e.to != wson[nod]) get_dfn(e.to, e.to);
}

i32 get_lca(i32 a, i32 b) {  // 不知道为啥 c++ 头文件的东西都是蛇形命名法...
    if (a == b) return a;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) std::swap(a, b);
        a = fa[top[a]];
    }
    return dep[a] > dep[b] ? b : a;
}

/* --- --- --- */
/*   虚树部分   */

i64 min_edg[N];  // 到 1 号节点（根节点）的最小边权，显然这玩意设成虚树边权不会比答案更优
std::bitset<N> is_key;

std::vector<i32> key_node;

void build() {
    std::sort(all(key_node), [](const i32& a, const i32& b) -> bool { return dfn[a] < dfn[b]; });  // 按照 dfn 排序

    for (i32 i = 1; i < t1; ++i) {
        key_node.emplace_back(get_lca(key_node[i - 1], key_node[i]));
    }
    key_node.emplace_back(1);

    std::sort(all(key_node), [](const i32& a, const i32& b) -> bool { return dfn[a] < dfn[b]; });  // 按照 dfn 排序
    key_node.erase(std::unique(all(key_node)), key_node.end());                                    // 二次排序之后去重

    for (i32 i = 1; i < key_node.size(); ++i) {
        add(vir, get_lca(key_node[i - 1], key_node[i]), key_node[i], min_edg[key_node[i]]);
    }
}

void init(i32 nod) {  // min
    for (auto& e : tree[nod]) {
        if (e.to != fa[nod]) {
            min_edg[e.to] = std::min(e.cost, min_edg[nod]);
            init(e.to);
        }
    }
}

i64 f[N];

void dfs(i32 nod, i32 fa) {
    // cout << nod << ' ';
    if (is_key[nod]) {
        f[nod] = min_edg[nod];
    } else {
        i64 cost = 0;
        for (auto& e : vir[nod]) {
            if (e.to != fa) {
                dfs(e.to, nod);
                cost += f[e.to];
            }
        }
        f[nod] = std::min(min_edg[nod], cost);
    }
    // vir[nod].clear();
    // is_key[nod] = false;
    // vir[nod].shrink_to_fit();
}

int main() {
    // freopen("redirection/input", "r", stdin);
    // freopen("redirection/output", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i < n; ++i) {
        cin >> t1 >> t2 >> t3;
        add(tree, t1, t2, t3);
    }

    memset(min_edg, 0x3f, sizeof min_edg);
    memset(f, 0x3f, sizeof f);

    get_siz(1);
    get_dfn(1, 1);
    init(1);
    // min_edg[1] = 0;

    cin >> m;
    while (m--) {
        cin >> t1;
        for (auto& nod : key_node)
            is_key[nod] = false, vir[nod].clear();
        key_node.clear();
        for (i32 i = 1; i <= t1; ++i) {
            cin >> t2;
            is_key[t2] = true;
            key_node.emplace_back(t2);
        }
        build();
        dfs(1, 0);
        cout << f[1] << '\n';
    }

    return 0;
}