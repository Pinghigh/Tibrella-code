#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 6005
#define M 40005

constexpr i64 inf = 0x3f3f3f3f;

i32 s, t, n, m, q;

i32 c, a, b;

void add(i32, i32, i64, i64);
void bfs();
i64 dfs(i32 nod, i64 flow);
i64 maxflow();

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> q;
    s = 1, t = (n << 1) + 3;

    for (i32 i = 1; i <= m; ++i) {
        cin >> a >> b;
        // if (a == 1)
        //     add(a, b, inf, inf);
        // else
        add(a + n, b, inf, 0);
        add(b + n, a, inf, 0);
    }
    add(1, 1 + n, inf, 0);
    for (i32 i = 1; i <= q; ++i) {
        cin >> c;
        add(c, c + n, inf, 0);
        add(c + n, t, inf, 0);
    }
    for (i32 i = 2; i <= n; ++i)
        add(i, i + n, 1, 0);

    cout << maxflow();

    return 0;
}

struct edge {
    edge *nex, *opp;
    i32 to;
    i64 flow;
} graph[M << 2], *fir[N << 1], *cur[N << 1];
edge* tot = graph;
void add(i32 a, i32 b, i64 flow1, i64 flow2) {
    tot->to = b;
    tot->nex = fir[a];
    tot->opp = (tot + 1);
    tot->flow = flow1;
    fir[a] = tot++;

    tot->to = a;
    tot->nex = fir[b];
    tot->opp = (tot - 1);
    tot->flow = flow2;
    fir[b] = tot++;
}

i32 dep[N << 1], gap[N << 1];

void bfs() {
    std::queue<i32> q;
    dep[t] = 1;
    ++gap[dep[t]];
    q.emplace(t);

    while (!q.empty()) {
        i32 nod = q.front();
        // cout << nod << ' ';
        q.pop();
        for (edge* e = fir[nod]; e; e = e->nex) {
            i32 to = e->to;
            if (!dep[to]) {
                dep[to] = dep[nod] + 1;
                ++gap[dep[to]];
                q.emplace(to);
            }
        }
    }
}

i64 dfs(i32 nod, i64 flow) {
    if (nod == t) return flow;
    i64 res = 0;
    for (edge* e = cur[nod]; e; e = e->nex) {
        cur[nod] = e;
        i32 to = e->to;
        if (e->flow && dep[nod] == dep[to] + 1) {
            i64 tmp = dfs(to, std::min(flow, e->flow));
            if (tmp) {
                flow -= tmp;
                res += tmp;
                e->flow -= tmp;
                e->opp->flow += tmp;
                // cout << res;

                if (!flow) return res;
            }
        }
    }

    if (!--gap[dep[nod]]) dep[s] = t + 3;
    ++gap[++dep[nod]];

    return res;
}

i64 maxflow() {
    i64 res = 0;
    bfs();
    while (dep[s] <= t) {
        memcpy(cur, fir, sizeof fir);
        res += dfs(s, inf);
    }
    return res;
}