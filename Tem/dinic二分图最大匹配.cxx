#include <climits>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::queue;

#define endl '\n'
#define N 514
#define E 55140

struct edge {
    edge *nex, *opp;
    int to, w;
} graph[((E + N + N) << 2)];

edge *fir[N << 2], *tot = graph, *cur[N << 2];
int depth[N];
queue<int> q;
auto min = [](int a, int b) { return a < b ? a : b; };
int n, m, e;
int t1, t2;

void add(int a, int b, int c) {
    ++tot;
    tot->to = b;
    tot->w = c;
    tot->nex = fir[a];
    fir[a] = tot;
    tot->opp = tot + 1;

    ++tot;
    tot->to = a;
    tot->w = 0;
    tot->nex = fir[b];
    fir[b] = tot;
    tot->opp = tot - 1;
}

bool bfs() {
    while (q.size())
        q.pop();
    memset(depth, 0, sizeof depth);
    cur[0] = fir[0];
    depth[0] = 1;
    q.push(0);
    while (q.size()) {
        int idx = q.front();
        q.pop();
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (!depth[e->to] && e->w) {
                depth[e->to] = depth[idx] + 1;
                q.push(e->to);
                cur[e->to] = fir[e->to];
            }
        }
    }

    if (depth[n + m + 1]) return true;
    return false;
}

int dfs(int nod, int val) {
    if (nod == n + m + 1) return val;
    for (edge* e = cur[nod]; e; e = e->nex) {
        cur[nod] = e;

        if (depth[nod] + 1 == depth[e->to] && e->w) {
            int res = dfs(e->to, min(e->w, val));
            if (res > 0) {
                e->w -= res;
                e->opp->w += res;
                return res;
            }
        }
    }
    return 0;
}

int dinic() {
    int res = 0;
    while (bfs()) {
        while (int d = dfs(0, INT_MAX)) {
            res += d;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> e;
    for (int i = 0; i < e; ++i) {
        cin >> t1 >> t2;
        add(t1, n + t2, 1);
    }
    for (int i = 1; i <= n; ++i)
        add(0, i, 1);
    for (int i = n + 1; i <= m + n; ++i)
        add(i, n + m + 1, 1);

    cout << dinic() << endl;

    return 0;
}