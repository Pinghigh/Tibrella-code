#include <bitset>
#include <iomanip>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using i32 = int;
using f64 = double;

#define N 100005
#define M 200005

struct edge {
    edge* nex;
    i32 to;
    i32 w;
} graph[M], *fir[N];
edge* tot = graph;
i32 outd[N], ind[N];
void add(i32 a, i32 b, i32 w) {
    tot->to = b;
    tot->w = w;
    tot->nex = fir[a];
    ++ind[b];
    ++outd[a];
    fir[a] = tot++;
}

i32 n, m, u, v, w;
double f[N], g[N];

void topo() {
    std::queue<i32> q;
    q.push(1);
    f[1] = 0;
    g[1] = 1;
    while (q.size()) {
        int nod = q.front();
        q.pop();
        for (edge* e = fir[nod]; e; e = e->nex) {
            int to = e->to;
            --ind[to];
            g[to] += g[nod] / outd[nod];
            f[to] += (f[nod] + g[nod] * e->w) / outd[nod];
            if (!ind[to]) q.push(to);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v >> w;
        add(u, v, w);
    }

    topo();

    cout << std::fixed << std::setprecision(2) << f[n];

    return 0;
}