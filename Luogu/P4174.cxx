#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

// 实际边数：(N->t + s->M + (A_i,B_i)*M)*2
// 实际点数：(N + M)

const i64 inf = 0x3f3f3f3f;

#define N 7005
#define M 70005

void add(i32, i32, i64);
i64 maxflow();

i32 n, m;
i32 s, t, a, b;
i64 p, c, sum;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    s = 0, t = n + m + 3;
    for (i32 i = 1; i <= n; ++i) {
        cin >> p;
        add(i, t, p);
    }
    for (i32 i = 1; i <= m; ++i) {
        cin >> a >> b >> c;
        sum += c;
        add(s, i + n, c);
        add(i + n, a, inf);
        add(i + n, b, c);
    }

    cout << sum - maxflow();

    return 0;
}

struct edge {
    edge *nex, *opp;
    i32 to;
    i64 flow;
} graph[(N + M + M) << 2], *fir[N + M << 1], *cur[N + M << 1];
edge* tot = graph;

void add(i32 u, i32 v, i64 flow) {
    tot->to = v;
    tot->nex = fir[u];
    tot->opp = (tot + 1);
    tot->flow = flow;
    fir[u] = tot++;

    tot->to = u;
    tot->nex = fir[v];
    tot->opp = (tot - 1);
    tot->flow = 0;
    fir[v] = tot++;
}

i32 dep[N + M], gap[N + M];

void bfs() {
    std::queue<i32> q;
    ++gap[dep[t] = 1];
    q.emplace(t);

    while (!q.empty()) {
        i32 nod = q.front();
        q.pop();
        for (edge* e = fir[nod]; e; e = e->nex) {
            i32 to = e->to;
            if (!dep[to]) {
                ++gap[dep[to] = dep[nod] + 1];
                q.emplace(to);
            }
        }
    }
}

i64 dfs(i32 nod, i64 flow) {
    if (nod == t) return flow;
    i64 res = 0;
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32& to = e->to;
        i64& f = e->flow;
        if (f && dep[to] == dep[nod] - 1) {
            i64 tmp = dfs(to, std::min(flow, f));
            if (tmp) {
                f -= tmp;
                e->opp->flow += tmp;
                flow -= tmp;
                res += tmp;
                if (!flow) return res;
            }
        }
    }

    if (!--gap[dep[nod]]) dep[s] = t + 3;
    ++gap[++dep[nod]];
    return res;
}

i64 maxflow() {
    bfs();
    i64 res = 0;
    while (dep[s] <= t) {
        memcpy(cur, fir, sizeof fir);
        res += dfs(s, inf);
    }
    return res;
}