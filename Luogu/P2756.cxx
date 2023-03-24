#include <climits>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::queue;

#define endl '\n'
#define N 1100
#define E 11000000

struct edge {
    edge *nex, *opp;
    short int flag;  // LEFT:-1,RIGHT:1
    int to, w;
} graph[(E + N + N) << 1];

    edge *fir[N << 2], *tot = graph, *cur[N << 2];
    int depth[N << 2];
queue<int> q;
auto min = [](int a, int b) { return a < b ? a : b; };
int n, m, s, t;
int t1, t2;
int ans[N << 2];

void add(int a, int b, int c) {
    ++tot;
    tot->to = b;
    tot->w = c;
    tot->nex = fir[a];
    fir[a] = tot;
    tot->flag = -1;
    tot->opp = tot + 1;

    ++tot;
    tot->to = a;
    tot->w = 0;
    tot->nex = fir[b];
    fir[b] = tot;
    tot->flag = 1;
    tot->opp = tot - 1;
}

bool bfs() {
    while (q.size())
        q.pop();

    memset(depth, 0, sizeof depth);
    q.push(s);
    depth[s] = 1;
    cur[s] = fir[s];

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

    if (depth[t]) return true;
    return false;
}

int dfs(int nod, int val) {
    if (nod == t) return val;
    for (edge* e = fir[nod]; e; e = e->nex) {
        cur[nod] = e;
        if (depth[nod] + 1 == depth[e->to] && e->w) {
            int d = dfs(e->to, min(e->w, val));
            if (d > 0) {
                switch (e->flag) {
                    case (-1): ans[e->to] = ans[nod]; break;
                    case (1): ans[nod] = 0; break;
                }
                e->w -= d;
                e->opp->w += d;
                return d;
            }
        }
    }
    return 0;
}

int dinic() {
    int res = 0;
    while (bfs()) {
        while (int d = dfs(s, INT_MAX)) {
            res += d;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> m >> n;
    s = 0;
    t = n + 1;
    for (;;) {
        cin >> t1 >> t2;
        if (!~t1 && !~t1) break;
        add(t1, t2, 1);
    }
    for (int i = 1; i <= m; ++i) {
        add(s, i, 1);
    }
    for (int i = m + 1; i <= n; ++i) {
        add(i, t, 1);
    }

    cout << dinic() << '\n';
    for (int i = 1; i <= m; ++ i) {
        for (edge* e = fir[i]; e; e = e->nex) {
            if (!e->w && e->opp->w && e->to && e->to^t) {
                cout << i << ' ' << e->to << endl;
                break;  
            }
        }
    }

    return 0;
}
