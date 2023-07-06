#include <climits>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::queue;

#define endl '\n'
#define N 6600
#define M 601000

using i64 = long long int;
struct edge {
    i64 u, v;
    edge *nex, *opp;
    i64 w;
} graph[M];
edge* tot = graph;
edge *fir[N], *cur[N];
i64 depth[N];
i64 n, m, s, t;
i64 t1, t2, t3;
queue<i64> q;

auto min = [](i64 a, i64 b) { return a < b ? a : b; };

void add(i64 a, i64 b, i64 c) {
    ++tot;
    tot->u = a;
    tot->v = b;
    tot->w = c;
    tot->opp = tot + 1;
    tot->nex = fir[a];
    fir[a] = tot;

    // 反向边
    ++tot;
    tot->u = b;
    tot->v = a;
    tot->w = 0;
    tot->opp = tot - 1;
    tot->nex = fir[b];
    fir[b] = tot;
};

bool bfs(i64 start) {
    while (q.size())
        q.pop();
    // memset(depth, 0, sizeof depth);
    cur[start] = fir[start];
    for (int i = 1; i <= n; ++i)
        depth[i] = 0;

    depth[start] = 1;
    q.push(start);
    while (q.size()) {
        i64 idx = q.front();
        q.pop();
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (e->w > 0 && !depth[e->v]) {  // 该边容量大于零且还没有被设置深度
                depth[e->v] = depth[idx] + 1;
                q.push(e->v);
                cur[e->v] = fir[e->v];
            }
        }
    }

    if (!depth[t]) return false;
    return true;
}

i64 dfs(i64 nod, i64 val) {
    if (nod == t) return val;  // 边界即到达汇点

    i64 res = 0;
    for (edge* e = cur[nod]; e && val; e = e->nex) {
        cur[nod] = e;
        if (depth[nod] + 1 == depth[e->v] && e->w) {  // 第一个条件判断分层图，第二个条件判断边的残量
            i64 tmp = dfs(e->v, min(val, e->w));
            if (tmp > 0) {  // 找到增广路
                e->w -= tmp;
                e->opp->w += tmp;
                res += tmp;
                val -= tmp;
                // return res;
            }
        }
    }
    return 0;
}

i64 dinic(i64 start) {
    i64 res = 0;
    i64 d = 0;
    // cout << start << endl;
    while (bfs(start)) {
        while (i64 d = dfs(start, (i64)LLONG_MAX)) {
            res += d;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> s >> t;
    for (i64 i = 1; i <= m; ++i) {
        cin >> t1 >> t2 >> t3;
        add(t1, t2, t3);
    }

    cout << dinic(s) << endl;

    return 0;
}