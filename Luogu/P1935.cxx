#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

#define N 205

using i8 = int8_t;
using i32 = int;
using i64 = long long;

constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
constexpr i8 x[] = { 0, 1, 0, -1, 0 };
constexpr i8 y[] = { 0, 0, 1, 0, -1 };

i64 sum;
i32 n, m;
i32 t1;
i32 s, t;
i32 totn;

i32 table[N << 1][N << 1];

i32 hash(i32 x, i32 y) {
    if (!table[x][y]) table[x][y] = ++totn;
    return table[x][y];
}

struct edge {
    edge *nex, *opp;
    i32 to;
    i64 flow;
} graph[N * N * N], *fir[N * N * 3], *cur[N * N * 3];
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

i32 a[N][N], b[N][N], c[N][N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    s = 0;
    t = ++totn;
    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i) {
        for (i32 j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    for (i32 i = 1; i <= n; ++i) {
        for (i32 j = 1; j <= m; ++j) {
            cin >> b[i][j];
            sum += a[i][j] + b[i][j];
            if ((i + j) & 1) std::swap(a[i][j], b[i][j]);
            add(s, hash(i, j), a[i][j]);
            add(hash(i, j), t, b[i][j]);
        }
    }

    for (i32 i = 1; i <= n; ++i) {
        for (i32 j = 1; j <= m; ++j) {
            cin >> c[i][j];
            for (i32 k = 1; k < 5; ++k) {
                i32 xx = i + x[k], yy = j + y[k];
                if (xx <= n && xx >= 1 && yy <= m && yy >= 1) {
                    sum += c[i][j] * 2;
                    add(s, ++totn, c[i][j]);
                    add(++totn, t, c[i][j]);

                    add(totn - 1, hash(i, j), inf);
                    add(hash(i, j), totn, inf);

                    add(totn - 1, hash(xx, yy), inf);
                    add(hash(xx, yy), totn, inf);
                }
            }
        }
    }

    cout << sum - maxflow();

    return 0;
}