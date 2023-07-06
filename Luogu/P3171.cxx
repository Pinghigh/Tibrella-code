#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 1005
#define M 200005

struct edg {
    i32 to;
    i64 dis;
};

const i64 INF = 0x3f3f3f3f3f3f3f3f;

std::vector<edg> e[N];
i64 dis[N];
std::bitset<N> vis;

struct edge {
    edge *nex, *opp;
    i32 to;
    i64 w;
} graph[M << 1], *fir[N], *cur[N];
edge* tot = graph;

i64 n, m, u, v, w;

void add(i32 a, i32 b, i32 d) {
    e[a].emplace_back((edg){ b, d });
    e[b].emplace_back((edg){ a, d });
}

void add_flow(i32 a, i32 b, i64 c) {
    tot->to = b;
    tot->nex = fir[a];
    tot->w = c;
    tot->opp = (tot + 1);
    fir[a] = tot++;

    tot->to = a;
    tot->nex = fir[b];
    tot->w = 0;
    tot->opp = (tot - 1);
    fir[b] = tot++;
}

struct node {
    i32 id;
    i64 dis;
};
bool operator>(const node& a, const node& b) {
    return a.dis > b.dis;
}

void dijk() {
    std::priority_queue<node, std::vector<node>, std::greater<node>> q;
    memset(dis, 0x3f, sizeof dis);

    q.push({ 1, 0 });
    dis[1] = 0;
    while (!q.empty()) {
        node nod = q.top();
        q.pop();
        if (vis[nod.id]) continue;
        vis[nod.id] = true;
        for (auto& ed : e[nod.id]) {
            if (!vis[ed.to] && dis[ed.to] > dis[nod.id] + ed.dis) {
                dis[ed.to] = dis[nod.id] + ed.dis;
                q.push((node){ ed.to, dis[ed.to] });
            }
        }
    }
}

void dfs(i32 nod) {
    vis[nod] = true;
    for (auto& ed : e[nod]) {
        if (!vis[ed.to]) dfs(ed.to);
        if (dis[ed.to] == dis[nod] + ed.dis) {
            // cout << nod << ' ' << ed.to << '\n';
            add_flow(nod + n, ed.to, INF);
        }
    }
}

i64 dep[N], gap[N];
i32 s, t;

void bfs() {
    std::queue<i32> q;
    q.push(t);
    dep[t] = 1;
    gap[1] = 1;

    while (!q.empty()) {
        i32 nod = q.front();
        q.pop();
        for (edge* e = fir[nod]; e; e = e->nex) {
            i32 to = e->to;
            if (!dep[to]) {
                dep[to] = dep[nod] + 1;
                q.push(to);
                ++gap[dep[to]];
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
        if (e->w && dep[to] == dep[nod] - 1) {
            i64 tmp = dfs(to, std::min(flow, e->w));
            if (tmp) {
                flow -= tmp;
                res += tmp;
                e->w -= tmp;
                e->opp->w += tmp;
            }
            if (!flow) return res;
        }
    }

    if (!--gap[dep[nod]]) dep[s] = n + n + 2;
    ++gap[++dep[nod]];
    return res;
}

i64 maxflow() {
    i64 ans = 0;
    bfs();
    while (dep[s] <= (n << 1)) {
        memcpy(cur, fir, sizeof(edge*) * (n * 2 + 5));
        ans += dfs(s, INF);
    }
    return ans;
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

    dijk();
    vis.reset();
    dfs(1);

    s = 1 + n, t = n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> w;
        add_flow(i, i + n, w);
    }

    cout << maxflow() << '\n';

    // for (i32 i = 1; i <= n * 2; ++i)
    //     cout << dep[i] << ' ';

    return 0;
}