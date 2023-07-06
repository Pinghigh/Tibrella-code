#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::swap;

#define N 300005

struct edge {
    edge* nex;
    int to;
} graph[(N << 1) + 5], *fir[N];
edge* tot = graph;
void add(int a, int b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

int dep[N], wson[N], fa[N], siz[N];
void get_wson(int nod, int f) {
    fa[nod] = f;
    siz[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->to;
        if (to == f) continue;
        dep[to] = dep[nod] + 1;
        get_wson(to, nod);
        siz[nod] += siz[to];
        if (siz[to] > siz[wson[nod]]) wson[nod] = to;
    }
}

int top[N];
void get_dfn(int nod, int f, int he) {
    top[nod] = he;
    if (wson[nod]) get_dfn(wson[nod], nod, he);
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->to;
        if (to == wson[nod] || to == f) continue;
        get_dfn(to, nod, to);
    }
}

int get_lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return ((dep[x] > dep[y]) ? y : x);
}

int val[N];

int n, a[N];
int t1, t2;
int ans[N];

#include <bitset>
std::bitset<N> st;

void add_up(int nod, int f) {
    st[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->to;
        if (to == f || st[to]) continue;
        add_up(to, nod);
        ans[nod] += ans[to];
    }
    ans[nod] += val[nod];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i < n; ++i) {
        cin >> t1 >> t2;
        add(t1, t2);
        add(t2, t1);
    }

    get_wson(1, 0);
    get_dfn(1, 0, 1);

    for (int i = 1; i < n; ++i) {
        int lca = get_lca(a[i], a[i + 1]);
        ++val[a[i]];
        ++val[a[i + 1]];
        --val[lca];
        --val[fa[lca]];
    }

    add_up(1, 0);
    for (int i = 2; i <= n; ++i) {
        --ans[a[i]];
    }
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << '\n';

    return 0;
}