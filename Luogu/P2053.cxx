#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;
using f64 = double;

void add(i32, i32, i64, i64);
i64 mnmf();

const i64 inf = 0x3f3f3f3f3f3f3f3f;

#define M 10
#define N 65

i32 m, n, s, t;
i32 tim[M][N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> m >> n;
    s = 0;
    t = n * m + n + 4;
    for (i32 j = 1; j <= n; ++j) {
        for (i32 i = 1; i <= m; ++i) {
            cin >> tim[i][j];
            add(i + (j - 1) * m, t, 1, 0);
        }
        add(s, j + n * m, 1, 0);
    }

    for (i32 k = 1; k <= n; ++k) {
        for (i32 i = 1; i <= m; ++i) {
            for (i32 j = 1; j <= n; ++j) {
                add(j + n * m, i + (k - 1) * m, 1, k * tim[i][j]);
            }
        }
    }

    cout << std::fixed << std::setprecision(2) << mnmf() * 1.0 / n;

    return 0;
}

struct edge {
    edge *nex, *opp;
    i32 fr, to;
    i64 flow, cost;
} graph[(N * M + N * N * M) << 1], *fir[N * M + N], *path[N * M + N];
edge* tot = graph;

void add(i32 a, i32 b, i64 flow, i64 cost) {
    // cout << a << ' ' << b << ' ' << flow << '\n';
    tot->fr = a;
    tot->to = b;
    tot->nex = fir[a];
    tot->flow = flow;
    tot->cost = cost;
    tot->opp = tot + 1;
    fir[a] = tot++;

    tot->fr = b;
    tot->to = a;
    tot->nex = fir[b];
    tot->flow = 0;
    tot->cost = -cost;
    tot->opp = tot - 1;
    fir[b] = tot++;
}

i64 h[N * M + N], dis[N * M + N];

struct node {
    i32 id;
    i64 dis;

    bool operator>(const node& b) const {
        return dis > b.dis;
    }
};

#include <bitset>

std::bitset<N * M + N> vis;

bool dijk() {
    vis.reset();
    memset(dis, 0x3f, sizeof dis);
    std::priority_queue<node, std::vector<node>, std::greater<node>> q;
    dis[s] = 0;
    q.emplace((node){ s, 0 });

    while (!q.empty()) {
        i32 nod = q.top().id;
        q.pop();
        if (vis[nod]) continue;
        vis[nod] = true;
        for (edge* e = fir[nod]; e; e = e->nex) {
            i32 to = e->to;
            if (e->flow && dis[to] > dis[nod] + e->cost + h[nod] - h[to]) {
                dis[to] = dis[nod] + e->cost + h[nod] - h[to];
                q.push((node){ to, dis[to] });
                path[to] = e;
            }
        }
    }

    return dis[t] != inf;
}

i64 mnmf() {
    i64 res = 0;
    while (dijk()) {
        for (i32 i = s; i <= t; ++i)
            h[i] += dis[i];
        i64 mn = inf;
        for (i32 nod = t; nod != s; nod = path[nod]->fr)
            mn = std::min(mn, path[nod]->flow);
        for (i32 nod = t; nod != s; nod = path[nod]->fr) {
            path[nod]->flow -= mn;
            path[nod]->opp->flow += mn;
        }
        res += mn * h[t];
    }
    return res;
}
