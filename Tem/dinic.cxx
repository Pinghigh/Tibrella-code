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

using llint = long long int;
struct edge {
    llint u, v;
    edge *nex, *opp;
    llint w;
} graph[M];
edge* tot = graph;
edge *fir[N], *cur[N];
llint depth[N];
llint n, m, s, t;
llint t1, t2, t3;
queue<llint> q;

auto min = [](llint a, llint b) { return a < b ? a : b; };

void add(llint a, llint b, llint c) {
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

bool bfs(llint start) {
    while (q.size())
        q.pop();
    // memset(depth, 0, sizeof depth);
    cur[start]=fir[start];
    for (int i = 1; i <= n; ++i)
        depth[i] = 0;

    depth[start] = 1;
    q.push(start);
    while (q.size()) {
        llint idx = q.front();
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

llint dfs(llint nod, llint val) {
    if (nod == t) return val;  // 边界即到达汇点

    for (edge* e = cur[nod]; e; e = e->nex) {
        cur[nod] = e;
        if (depth[nod] + 1 == depth[e->v] && e->w) {  // 第一个条件判断分层图，第二个条件判断边的残量
            llint res = dfs(e->v, min(val, e->w));
            if (res > 0) {                            // 找到增广路
                e->w -= res;
                e->opp->w += res;
                return res;
            }
        }
    }
    return 0;
}

llint dinic(llint start) {
    llint res = 0;
    llint d = 0;
    // cout << start << endl;
    while (bfs(start)) {
        while (llint d = dfs(start, (llint)LLONG_MAX)) {
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
    for (llint i = 1; i <= m; ++i) {
        cin >> t1 >> t2 >> t3;
        add(t1, t2, t3);
    }

    cout << dinic(s) << endl;

    return 0;
}