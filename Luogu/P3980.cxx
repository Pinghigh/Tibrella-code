#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>

#define N 2010
#define M 20010

using i32 = int;
using i64 = long long;

using std::cin;
using std::cout;

const i64 inf = 0x3f3f3f3f3f3f3f3f;

i32 n, m;
i64 t1, t2, t3;
i32 s, t;

struct edge {
    edge *nex, *opp;
    i64 cost, flow;
    i32 to;
} graph[M << 1], *fir[N], *path[N];
edge* tot = graph;

void add(i32 a, i32 b, i64 flow, i64 cost) {
    tot->to = b;
    tot->flow = flow;
    tot->cost = cost;
    tot->nex = fir[a];
    tot->opp = tot + 1;
    fir[a] = tot++;

    tot->to = a;
    tot->flow = 0;
    tot->cost = -cost;
    tot->nex = fir[b];
    tot->opp = tot - 1;
    fir[b] = tot++;
}

i64 h[N], dis[N];
std::bitset<N> vis;

struct node {
    i32 id;
    i64 dis;
};

bool operator>(const node& a, const node& b) {
    return a.dis > b.dis;
}

bool dijk() {
    memset(dis, 0x3f, sizeof dis);
    vis.reset();

    std::priority_queue<node, std::vector<node>, std::greater<node>> q;
    dis[s] = 0;
    q.push({ s, 0 });

    while (!q.empty()) {
        i32 nod = q.top().id;
        q.pop();
        if (vis[nod]) continue;
        vis[nod] = true;
        for (edge* e = fir[nod]; e; e = e->nex) {
            i32 to = e->to;
            if (e->flow && dis[to] > dis[nod] + e->cost + h[nod] - h[to]) {
                dis[to] = dis[nod] + e->cost + h[nod] - h[to];
                q.push({ to, dis[to] });
                path[to] = e;
            }
        }
    }

    return dis[t] < inf;
}

i64 mcmf() {
    i64 cost = 0;
    while (dijk()) {
        i64 mn = inf;
        for (i32 i = s; i <= t; ++i)
            h[i] += dis[i];
        for (i32 nod = t; nod != s; nod = path[nod]->opp->to)
            mn = std::min(mn, path[nod]->flow);
        for (i32 nod = t; nod != s; nod = path[nod]->opp->to) {
            path[nod]->flow -= mn;
            path[nod]->opp->flow += mn;
        }
        cost += mn * h[t];
    }
    return cost;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i) {
        cin >> t1;
        add(i, i + 1, inf - t1, 0);
    }
    for (i32 i = 1; i <= m; ++i) {
        cin >> t1 >> t2 >> t3;
        add(t1, t2 + 1, inf, t3);
    }
    s = 0, t = n + 2;
    add(s, 1, inf, 0);
    add(n + 1, t, inf, 0);

    cout << mcmf();

    return 0;
}