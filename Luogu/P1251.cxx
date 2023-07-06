#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>

using i32 = int;
using i64 = long long;

using std::cin;
using std::cout;

#define N 2010

const i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 r[N];
i64 d, fastd, fastc, slowd, slowc, p;
i32 totn;
i32 s, t;

struct edge {
    edge *nex, *opp;
    i32 to;
    i64 cost, flow;
} graph[N << 4], *fir[N << 1], *spath[N << 1];
edge* tot = graph;

void add(i32 a, i32 b, i64 flow, i64 cost) {
    // cout << a << ' ' << b << ' ' << cost << '\n';
    tot->to = b;
    tot->flow = flow;
    tot->cost = cost;
    tot->opp = (tot + 1);
    tot->nex = fir[a];
    fir[a] = tot++;

    tot->to = a;
    tot->flow = 0;
    tot->cost = -cost;
    tot->opp = (tot - 1);
    tot->nex = fir[b];
    fir[b] = tot++;
}

i64 dis[N << 1];

std::bitset<(N << 1)> vis;

struct node {
    i32 id;
    i64 dis;

    node() {}
    node(i32 a, i64 b) : id(a), dis(b) {}
};

bool operator<(const node& a, const node& b) {
    return a.dis < b.dis;
}
bool operator>(const node& a, const node& b) {
    return a.dis > b.dis;
}

i64 h[N << 1];

bool dijk() {
    memset(dis, 0x3f, sizeof dis);
    vis.reset();
    memset(spath, 0, sizeof spath);

    std::priority_queue<node, std::vector<node>, std::greater<node>> q;
    q.push({ s, 0 });
    dis[s] = 0;

    while (!q.empty()) {
        i32 nod = q.top().id;
        q.pop();
        if (vis[nod]) continue;
        vis[nod] = true;
        for (edge* e = fir[nod]; e; e = e->nex) {
            i32 to = e->to;
            if (dis[nod] + e->cost + h[nod] - h[to] < dis[to] && e->flow) {
                // cout << dis[nod] + e->cost + h[nod] - h[to] << '\n';
                spath[to] = e;
                dis[to] = dis[nod] + e->cost + h[nod] - h[to];
                q.push({ to, dis[to] });
            }
        }
    }

    return dis[t] < inf;
}

i64 mcmf() {
    i64 cost = 0;

    while (dijk()) {
        for (i32 nod = 0; nod <= totn; ++nod)
            h[nod] += dis[nod];
        i64 mn = inf;
        for (i32 nod = t; nod != s; nod = spath[nod]->opp->to)
            mn = std::min(mn, spath[nod]->flow);
        for (i32 nod = t; nod != s; nod = spath[nod]->opp->to)
            spath[nod]->flow -= mn, spath[nod]->opp->flow += mn;
        cost += mn * h[t];
        // for (int i = 0; i <= totn; ++i)
        //     cout << dis[i] << ' ';
        // cout << '\n';
        // cout << mn;
    }

    return cost;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    s = 0;
    cin >> d;
    for (i32 i = 1; i <= d; ++i) {
        cin >> r[i];
        add(s, i + d, r[i], 0);  // 每晚从起点得到当天所用数量的脏餐巾
    }
    cin >> p >> fastd >> fastc >> slowd >> slowc;
    totn = d * 2;
    // i32 fw = ++totn, sw = ++totn;
    for (i32 i = 1; i <= d; ++i)
        add(s, i, inf, p);  // 每天早上能从起点买无数条餐巾
    for (i32 i = 1; i < d; ++i)
        add(i + d, i + d + 1, inf, 0);  // 每天晚上能给第二天晚上提供不限量的脏餐巾，取决于当天有多少脏餐巾
    for (i32 i = 1; i + slowd <= d; ++i)
        add(i + d, i + slowd, inf, slowc);
    for (i32 i = 1; i + fastd <= d; ++i)
        add(i + d, i + fastd, inf, fastc);
    t = ++totn;
    for (i32 i = 1; i <= d; ++i)
        add(i, t, r[i], 0);

    cout << mcmf();

    return 0;
}