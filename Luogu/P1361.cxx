#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

#define N 2005

using i8 = int8_t;
using i32 = int;
using i64 = long long;

constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 sum;
i32 n, m;
i32 t1, t2;
i32 s, t;
i32 totn;

struct edge {
    edge *nex, *opp;
    i32 to;
    i64 flow;
} graph[N * N << 1], *fir[N * N << 1], *cur[N * N << 1];
edge* tot = graph;

void add(i32 a, i32 b, i64 flow) {
    tot->to = b;
    tot->flow = flow;
    tot->nex = fir[a];
    tot->opp = (tot + 1);
    fir[a] = tot++;

    tot->to = a;
    tot->flow = 0;
    tot->nex = fir[b];
    tot->opp = (tot - 1);
    fir[b] = tot++;
}

i32 dep[N * N * 3], gap[N * N * 3];
void bfs() {
    dep[t] = 1;
    ++gap[dep[t]];
    std::queue<i32> q;
    q.emplace(t);
    while (!q.empty()) {
        i32 nod = q.front();
        q.pop();
        for (edge* e = fir[nod]; e; e = e->nex) {
            i32 to = e->to;
            if (!dep[to]) {
                dep[to] = dep[nod] + 1;
                ++gap[dep[to]];
                q.push(to);
            }
        }
    }
}

i64 dfs(i32 nod, i64 flow) {
    // cout << nod << ((flow == inf) ? " inf" : " ") << ((flow != inf) ? flow : 0) << '\n';
    if (nod == t) return flow;
    i64 hav = 0;
    for (edge* e = cur[nod]; e; e = e->nex) {
        cur[nod] = e;
        i32 to = e->to;
        if (dep[to] + 1 == dep[nod] && e->flow) {
            i64 res = dfs(to, std::min(flow, e->flow));
            if (res) {
                flow -= res;
                hav += res;
                e->flow -= res;
                e->opp->flow += res;
                if (!flow) return hav;
            }
        }
    }

    if (!--gap[dep[nod]]) dep[s] = totn * 2;
    ++gap[++dep[nod]];
    return hav;
}

i64 maxflow() {
    bfs();
    i64 res = 0;
    while (dep[s] < totn * 2) {
        memcpy(cur, fir, sizeof fir);
        res += dfs(s, inf);
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    s = 0;
    cin >> n;
    totn = n;
    t = ++totn;
    for (i32 i = 1; i <= n; ++i) {
        cin >> t1;
        sum += t1;
        add(s, i, t1);
    }

    for (i32 i = 1; i <= n; ++i) {
        cin >> t1;
        sum += t1;
        add(i, t, t1);
    }

    cin >> m;
    while (m--) {
        cin >> t2;
        ++totn;
        cin >> t1;
        sum += t1;
        add(s, totn, t1);
        cin >> t1;
        sum += t1;
        add(totn + 1, t, t1);
        while (t2--) {
            cin >> t1;
            add(totn, t1, inf);
            add(t1, totn + 1, inf);
        }
        ++totn;
    }

    cout << sum - maxflow();

    return 0;
}