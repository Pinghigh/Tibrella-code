#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 201
#define M 2001

struct edge {
    edge *nxt, *opp;
    i32 v, w;
} graph[M<<1], *fir[N], *cur[N];
edge* tot = graph;

static void add(const i32& u, const i32& v, const i32& w) {
    *tot = {fir[u], tot + 1, v, w};
    fir[u] = tot++;
    *tot = {fir[v], tot - 1, u, 0};
    fir[v] = tot++;
}

i32 n, m, s = 1, t, x;

namespace isap {
    i32 dep[N], gap[N];
    i64 dfs(const i32& u, const i64& f) {
        if (u == t) return f;
        i64 hav = 0;
        for (edge* e = fir[u]; e; e = e->nxt) {
            const auto &v = e->v, &w = e->w;
            if (w && dep[u] - 1 == dep[v]) {
                i64 res = dfs(v, std::min((i64)w, f - hav));
                if (res) {
                    hav += res;
                    e->w -= res;
                    e->opp->w += res;
                    if (hav == f) return f;
                }
            }            
        }
        if (!--gap[dep[u]]) dep[s] = n+5;
        ++gap[++dep[u]];

        return hav;
    }
    bool bfs() {
        std::queue<i32> q;
        q.emplace(t);
        gap[dep[t] = 1] = 1;
        while (!q.empty()) {
            i32 u = q.front();
            // cout << u << ' ' << dep[u] << '\n';
            q.pop();
            for (edge* e = fir[u]; e; e = e->nxt) 
                if (!dep[e->v]) ++gap[dep[e->v] = dep[u] + 1], q.emplace(e->v);
        }
        // cout << '\n' << dep[s] << '\n';
        return dep[s] > 0;
    }
    i64 main() {
        i64 res = 0;
        if (bfs()) while (dep[s] <= n) {memcpy(cur, fir, sizeof fir); res += dfs(s, 0x3f3f3f3f);}
        return res;
    }

}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> x;
    t = n;
    for (i32 i = 1; i <= m; ++ i) {
        i32 u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    i64 res = isap::main();
    if (res) cout << res << ' ' << (x+res-1) / res;
    else cout << "Orz Ni Jinan Saint Cow!";

    return 0;
}