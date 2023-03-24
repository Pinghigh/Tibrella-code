#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>

using std::bitset;
using std::cin;
using std::cout;
using std::min;

#define M 100005
#define N 20005

struct edge {
    edge *nex;
    int to;
} graph[M << 1];
edge *fir[N], *tot = graph;

void add(int a, int b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot;
    ++tot;
}
int dfn[N], low[N];
bitset<N> cut;
int id[N];
int tim;
int siz[N];
int root;
void tarjan(int nod) {
    dfn[nod] = low[nod] = ++tim;
    int cnt = 0;
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->to;
        if (!dfn[to]) {
            tarjan(to);
            low[nod] = min(low[nod], low[to]);
            if (low[to] >= dfn[nod]) {
                ++cnt;
                if (nod != root || cnt > 1) {
                    cut[nod] = 1;
                }
            }
        } else {
            low[nod] = min(low[nod], dfn[to]);
        }
    }
}

int n,m;
int t1,t2;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++ i) {
        cin >> t1 >> t2;
        add(t1,t2);
        add(t2,t1);
    }

    for (int i = 1; i <= n; ++ i) {
        if (!dfn[i]) {
            root = i;
            tarjan(root);
        }
    }

    cout << cut.count() << '\n';
    for (int i = 1; i <= n; ++ i) {
        if (cut[i]) cout << i << ' ';
    }

    return 0;
}