#include <algorithm>
#include <iostream>

#define N 500005

using std::cin;
using std::cout;
using std::swap;
using u32 = unsigned int;
using i32 = int;
using i64 = long long;

struct edge {
    edge* nex;
    u32 to;
} graph[N], *fir[N];
edge* tot = graph;
void add(u32 a, u32 b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

u32 fa[N], dep[N], siz[N], wson[N];
void get_wson(u32 nod) {
    siz[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        u32 to = e->to;
        dep[to] = dep[nod] + 1;
        get_wson(to);
        siz[nod] += siz[to];
        if (siz[wson[nod]] < siz[to]) wson[nod] = to;
    }
}

u32 top[N], tim, dfn[N], adfn[N];
void get_top(u32 nod, u32 he) {
    top[nod] = he;
    dfn[nod] = ++tim;
    adfn[tim] = nod;
    if (wson[nod]) get_top(wson[nod], he);
    for (edge* e = fir[nod]; e; e = e->nex) {
        u32 to = e->to;
        if (to == wson[nod]) continue;
        get_top(to, to);
    }
}

u32 n, q, s;

inline u32 get(u32 x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return s = x;
}

u32 root;
u32 t1;
i64 ans, res;

u32 sol(u32 x, u32 k) {
    // u32 d = dep[x] - k;
    // while (dep[top[x]] > d)
    //     x = fa[top[x]];
    // d = dep[x] - d;
    // return adfn[dfn[x] - d];

    while (dep[x] - dep[fa[top[x]]] <= k) {
        k -= dep[x] - dep[fa[top[x]]];
        x = fa[top[x]];
    }
    return adfn[dfn[x] - k];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> q >> s;
    for (u32 i = 1; i <= n; ++i) {
        cin >> fa[i];
        if (!fa[i])
            root = i;
        else
            add(fa[i], i);
    }

    dep[root] = 1;
    get_wson(root);
    get_top(root, root);

    for (u32 i = 1; i <= q; ++i) {
        int nod = (get(s) ^ ans) % n + 1;
        int k = (get(s) ^ ans) % dep[nod];
        ans = sol(nod, k);
        res ^= i * ans;
    }

    cout << res << '\n';

    return 0;
}