#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>

using std::bitset;
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::queue;

#define N 300514

int dist[N];

struct graph {
    struct edge {
        int to;
        edge* nex;
    } es[N];
    edge* tot;
    int ind[N];
    edge* fir[N];
    void add(int u, int v) {
        ++tot;
        tot->to = v;
        tot->nex = fir[u];
        fir[u] = tot;
        ++ind[v];
    }
    graph() {
        tot = es;
    }
    // edge*& operator[](const int _x) const {
    //     return es[_x];
    // }
} ori, aft, rev;

int sta[N], top;
int id[N];
int dfn[N], low[N], tim;
int siz[N];
int cnt;
bitset<N> st;
int outd[N];

void spfa(int nod, graph& gra) {
    bitset<N> sta;
    queue<int> q;
    memset(dist, -1, sizeof dist);
    sta.reset();
    dist[nod] = siz[nod];
    q.push(nod);
    sta[nod] = 1;

    while (!q.empty()) {
        nod = q.front();
        q.pop();
        sta[nod] = 0;
        for (graph::edge* e = gra.fir[nod]; e; e = e->nex) {
            int to = e->to;
            if (dist[nod] + siz[to] > dist[to]) {
                dist[to] = dist[nod] + siz[to];
                if (!sta[to]) {
                    q.push(to);
                    sta[to] = 1;
                }
            }
        }
    }
}

void tarjan(int nod) {
    dfn[nod] = low[nod] = ++tim;
    sta[++top] = nod;
    st[nod] = true;
    for (graph::edge* e = ori.fir[nod]; e; e = e->nex) {
        int to = e->to;
        if (!dfn[to]) {
            tarjan(to);
            low[nod] = min(low[nod], low[to]);
        } else if (st[to]) {
            low[nod] = min(low[nod], low[to]);
        }
    }

    if (dfn[nod] == low[nod]) {
        ++cnt;
        int pop;
        do {
            pop = sta[top--];
            st[pop] = false;
            id[pop] = cnt;
            ++siz[cnt];
        } while (pop != nod);
    }
}

int n, m;
int t1, t2;
int f[N];

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        ori.add(t1, t2);
    }

    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);

    for (int i = 1; i <= n; ++i) {
        for (graph::edge* e = ori.fir[i]; e; e = e->nex) {
            if (id[i] != id[e->to]) {
                // cout << id[i] << ' ' << id[e->to] << endl;
                // cout << id[i] + n << ' ' << id[e->to] + n << endl;
                // cout << id[e->to] << ' ' << id[i] + n << endl;
                aft.add(id[i], id[e->to]);
                aft.add(id[i] + cnt, id[e->to] + cnt);
                aft.add(id[e->to], id[i] + cnt);
            }
        }
    }

    for (int i = 1; i <= cnt; ++i) {
        siz[i + cnt] = siz[i];
    }

    spfa(id[1], aft);

    cout << max(dist[id[1] + cnt]-siz[id[1]], siz[id[1]]) << endl;
    // for (int i = 1; i <= 2*cnt; ++ i)
    // cout << i << ' ' << dist[i] << endl;

    return 0;
}