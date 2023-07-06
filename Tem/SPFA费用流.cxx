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
    i64 w, dis;
} graph[M];
edge* tot = graph;
edge *fir[N], *cur[N];
i64 depth[N];
i64 n, m, s, t;
i64 t1, t2, t3, t4;
queue<i64> q;

auto min = [](i64 a, i64 b) { return a < b ? a : b; };

void add(i64 a, i64 b, i64 c, i64 d) {
    tot->u = a;
    tot->v = b;
    tot->w = c;
    tot->dis = d;
    tot->opp = tot + 1;
    tot->nex = fir[a];
    fir[a] = tot++;

    // 反向边
    tot->u = b;
    tot->v = a;
    tot->w = 0;
    tot->dis = -d;
    tot->opp = tot - 1;
    tot->nex = fir[b];
    fir[b] = tot++;
};

#include <bitset>
std::bitset<N> inq;

bool bfs(i64 start) {
    q = queue<i64>();
    memset(depth, 0x3f, sizeof depth);
    memcpy(cur, fir, sizeof(fir));

    depth[start] = 0;
    q.push(start);
    inq[start] = 1;
    while (q.size()) {
        i64 idx = q.front();
        q.pop();
        inq[idx] = false;
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (e->w && depth[e->v] > depth[idx] + e->dis) {  // 该边容量大于零且还没有被设置深度
                depth[e->v] = depth[idx] + e->dis;
                if (!inq[e->v]) {
                    q.push(e->v);
                    inq[e->v] = true;
                }
            }
        }
    }
    return depth[t] != depth[0];
}

i64 cost;

std::bitset<N> vis;

i64 dfs(i64 nod, i64 val) {
    if (nod == t) return val;  // 边界即到达汇点
    vis[nod] = true;
    i64 res = 0;
    for (edge* e = cur[nod]; e && val; e = e->nex) {
        cur[nod] = e;
        if (!vis[e->v] && depth[nod] + e->dis == depth[e->v] && e->w) {  // 第一个条件判断分层图，第二个条件判断边的残量
            i64 tmp = dfs(e->v, min(val, e->w));
            if (tmp > 0) {  // 找到增广路
                cost += e->dis * tmp;
                e->w -= tmp;
                e->opp->w += tmp;
                res += tmp;
                val -= tmp;
                // return res;
            }
        }
    }
    vis[nod] = false;
    if (!res) depth[nod] = 0;
    return res;
}

i64 dinic(i64 start) {
    i64 res = 0;
    i64 d = 0;
    // cout << start << endl;
    while (bfs(start)) {
        while (d = dfs(start, (i64)LLONG_MAX)) {
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
        cin >> t1 >> t2 >> t3 >> t4;
        add(t1, t2, t3, t4);
    }

    cout << dinic(s) << ' ' << cost << endl;

    return 0;
}