#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

const char endl = '\n';

using i32 = int;
using i64 = long long;

#define N 5003
#define M 50004

struct pair {
    i64 first, second;

    pair(){};
    pair(i64 a, i64 b) : first(a), second(b){};
};

bool operator<(const pair& a, const pair& b) {
    return a.second < b.second;
}

bool operator>(const pair& a, const pair& b) {
    return a.second > b.second;
}

struct edge {
    edge *nex, *opp;
    i32 fr, to;
    i64 w, c;
} graph[M << 1], *fir[N], *eptr[N];
edge* tot = graph;

void add(i32 a, i32 b, i32 w, i32 c) {
    tot->fr = a;
    tot->to = b;
    tot->w = w;
    tot->c = c;
    tot->opp = (tot + 1);
    tot->nex = fir[a];
    fir[a] = tot++;

    tot->fr = b;
    tot->to = a;
    tot->w = 0;
    tot->c = -c;
    tot->opp = (tot - 1);
    tot->nex = fir[b];
    fir[b] = tot++;
}

i32 n, m, s, t;
i32 t1, t2;
i64 t3, t4;

i64 dis[N], h[N];
std::bitset<N> vis;
bool dijk() {
    std::priority_queue<pair, std::vector<pair>, std::greater<pair>> q;
    memset(dis, 0x3f, sizeof(i64) * (n + 2));
    memset(eptr, 0, sizeof(edge*) * (n + 2));
    vis.reset();

    q.push(pair(s, 0));
    dis[s] = 0;

    while (!q.empty()) {
        i32 nod = q.top().first;
        q.pop();
        if (vis[nod]) continue;
        vis[nod] = true;

        for (edge* e = fir[nod]; e; e = e->nex) {
            i32 to = e->to;
            if (e->w && dis[to] > dis[nod] + e->c + h[nod] - h[to]) {
                dis[to] = dis[nod] + e->c + h[nod] - h[to];
                eptr[to] = e;
                q.push(pair(to, dis[to]));
            }
        }
    }
    return dis[t] != dis[0];
}

pair mcmf() {
    i64 flow = 0, cost = 0;
    while (dijk()) {
        for (i32 i = 1; i <= n; ++i)
            h[i] += dis[i];
        i64 mn = dis[0];
        for (i32 nod = t; nod != s; nod = eptr[nod]->fr)
            mn = std::min(eptr[nod]->w, mn);
        for (i32 nod = t; nod != s; nod = eptr[nod]->fr)
            eptr[nod]->w -= mn, eptr[nod]->opp->w += mn;

        flow += mn, cost += h[t] * mn;
    }
    return pair(flow, cost);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> s >> t;
    while (m) {
        --m;
        cin >> t1 >> t2 >> t3 >> t4;
        add(t1, t2, t3, t4);
    }

    pair ans = mcmf();

    cout << ans.first << ' ' << ans.second;

    return 0;
}