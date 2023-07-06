#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>

using std::bitset;
using std::cin;
using std::cout;
using std::max;
using std::min;

const char endl = '\n';
const int N = 200500;

struct edge {
    edge *nex, *ori, *opp;
    int fr, to;
    bool cut, rev;
    char data;
} graph[N], aft[N];
edge *fir[N], *tot = graph;

void add(int& a, int& b) {
    tot->data = 'B';
    tot->fr = a;
    tot->to = b;
    tot->opp = tot + 1;
    tot->nex = fir[a];
    fir[a] = tot;
    ++tot;

    tot->fr = b;
    tot->to = a;
    tot->rev = true;
    tot->opp = tot - 1;
    tot->nex = fir[b];
    fir[b] = tot;
    ++tot;
}

void add(int& a, int& b, edge* e) {
    tot->data = 'B';
    tot->ori = e;
    tot->fr = a;
    tot->to = b;
    tot->opp = tot + 1;
    tot->nex = fir[a];
    fir[a] = tot;
    ++tot;

    tot->ori = e->opp;
    tot->fr = b;
    tot->to = a;
    tot->opp = tot - 1;
    tot->rev = true;
    tot->nex = fir[b];
    fir[b] = tot;
    ++tot;
}

int dfn[N], low[N], tim;
int id[N];
int ecc_cnt;

void tarjan(int nod, edge* edg) {
    dfn[nod] = low[nod] = ++tim;

    for (edge* e = fir[nod]; e; e = e->nex) {
        if (!dfn[e->to]) {
            tarjan(e->to, e);
            low[nod] = min(low[nod], low[e->to]);
            if (low[nod] < low[e->to]) {
                e->cut = e->opp->cut = true;
            }
        } else if (!edg || e != edg->opp) {
            low[nod] = min(low[nod], dfn[e->to]);
        }
    }
}

void add_up(int nod) {
    id[nod] = ecc_cnt;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (id[e->to] || e->cut) continue;
        add_up(e->to);
    }
}

int p[N];
bitset<N> vis;
void dfs(int nod, int fa) {
    vis[nod] = 1;
    int res = 0;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        dfs(e->to, nod);
        if (p[e->to] > 0) {
            if (e->rev) {
                e->ori->opp->data = 'R';
            } else {
                e->ori->data = 'L';
            }
        } else if (p[e->to] < 0) {
            if (e->rev) {
                e->ori->opp->data = 'L';
            } else {
                e->ori->data = 'R';
            }
        }
        res += p[e->to];
        // cout << p[e->to] << ' ' << e->fr << ' ' << e->to << ' ' << e->ori->fr << ' ' << e->ori->to << ' ' << e->rev << endl;
    }
    p[nod] += res;
}

void solve() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    tot = aft;
    memset(fir, 0, sizeof fir);
    for (edge* e = graph; e->to; ++e) {
        if (!e->rev && id[e->fr] != id[e->to]) add(id[e->fr], id[e->to], e);
    }
    for (int i = 1; i <= ecc_cnt; ++i)
        if (!vis[i]) dfs(i, 0);
    for (edge* e = graph; e->to; ++e)
        if (!e->rev) cout << e->data;
}

int n, m, t;
int t1, t2;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        add(t1, t2);
    }

    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i, 0);

    for (int i = 1; i <= n; ++i) {
        if (!id[i]) {
            ++ecc_cnt;
            add_up(i);
        }
    }

    // for (int i = 1; i <= n; ++ i) {
    //     cout << i << ' ' << id[i] << '\n';
    // }

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> t1 >> t2;
        ++p[id[t1]];
        --p[id[t2]];
    }
    solve();

    return 0;
}