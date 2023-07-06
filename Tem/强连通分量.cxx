#include <bitset>
#include <iostream>

using std::bitset;
using std::cin;
using std::cout;

#define endl '\n'
#define N 10010
#define M 50010

template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

int n, m;
struct edge {
    edge* nex;
    int u, v;
} graph[M];
edge* fir[N];
int dfn[N], low[N], tim;
int sta[N], top;
bitset<N> st;
edge* tot = graph;
int id[N], cnt, siz[N];
int outd[N];

void add(int u, int v) {
    ++tot;
    tot->u = u;
    tot->v = v;
    tot->nex = fir[u];
    fir[u] = tot;
}

void tarjan(int nod) {
    dfn[nod] = low[nod] = ++tim;
    sta[++top] = nod;
    st[nod] = true;
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->v;
        if (!dfn[to]) {
            tarjan(to);
            low[nod] = min(low[nod], low[to]);
        } else if (st[to])
            low[nod] = min(low[nod], dfn[to]);
    }

    if (dfn[nod] == low[nod]) {  // 当前点能到达的最高点就是自己，说明它是自己所在的强连通分量的最高点
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

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0)->tie(0);

    cin >> n >> m;
    while (m--) {
        int t1, t2;
        cin >> t1 >> t2;
        add(t1, t2);
    }

    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) tarjan(i);
    }

    for (int i = 1; i <= n; ++i) {
        for (edge* e = fir[i]; e; e = e->nex) {
            int to = e->v;
            if (id[i] != id[to]) ++outd[id[i]];
        }
    }

    int zero = 0;
    int sum = 0;

    for (int i = 1; i <= cnt; ++i) {
        if (!outd[i]) {
            ++zero;
            sum += siz[i];
            if (zero > 1) {
                sum = 0;
                break;
            }
        }
    }

    cout << sum << endl;

    return 0;
}