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

using i32 = int;
using i64 = long long int;

constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;
struct edge {
    i64 u, v;
    edge *nex, *opp;
    i64 w;
} graph[M];
edge* tot = graph;
edge *fir[N], *cur[N];
i64 dep[N], gap[N];
i64 n, m, s, t;
i64 t1, t2, t3;
queue<i64> q;

auto min = [](i64 a, i64 b) { return a < b ? a : b; };

void add(i32 a, i32 b, i64 c) {
    // cout << a << ' ' << b << ' ' << c << '\n';
    tot->v = b;
    tot->nex = fir[a];
    tot->w = c;
    tot->opp = (tot + 1);
    fir[a] = tot++;

    tot->v = a;
    tot->nex = fir[b];
    tot->w = 0;
    tot->opp = (tot - 1);
    fir[b] = tot++;
}

i64 ans;

void bfs() {
    dep[t] = 1;
    gap[1] = 1;
    q = queue<i64>();
    q.push(t);  // 逆向 BFS
    while (q.size()) {
        int nod = q.front();
        q.pop();
        for (edge* e = fir[nod]; e; e = e->nex) {
            int to = e->v;
            if (!dep[to]) {
                q.push(to);
                dep[to] = dep[nod] + 1;
                ++gap[dep[to]];  // 统计深度对应点数
            }
        }
    }
}

i64 dfs(int nod, i64 flow) {
    // cout << nod << ' ' << flow << '\n';
    if (nod == t) return flow;
    i64 used = 0;
    for (edge* e = cur[nod]; e; e = e->nex) {
        cur[nod] = e;
        int to = e->v;
        // cout << nod << ' ' << to << ' ' << e->w << '\n';
        if (e->w && dep[nod] - 1 == dep[to]) {
            i64 res = dfs(to, min(e->w, flow - used));
            if (res) {
                e->w -= res;
                e->opp->w += res;
                used += res;
            }
            if (flow == used) return flow;
        }
    }

    --gap[dep[nod]];
    if (!gap[dep[nod]]) dep[s] = n * 2 + 2;
    ++dep[nod];
    ++gap[dep[nod]];
    return used;
}

void ISAP() {
    ans = 0;
    bfs();
    while (dep[s] < n * 2 + 1) {
        memcpy(cur, fir, (n * 2 + 2) * sizeof(edge*));
        ans += dfs(s, LLONG_MAX);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> s >> t;
    s += n;
    for (i64 i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        add(t1 + n, t2, INF);
        add(t2 + n, t1, INF);
    }
    for (i64 i = 1; i <= n; ++i)
        add(i, i + n, 1);

    ISAP();

    cout << ans << endl;
    // for (int i = 1; i <= n * 2; ++i)
    //     cout << dep[i] << ' ';

    return 0;
}