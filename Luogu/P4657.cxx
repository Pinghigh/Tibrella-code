#include <iostream>

using llint = long long int;

const llint M = 105, N = 100005, INF = 0x3f3f3f3f3f3f3f3f;
const char endl = '\n';
using std::cin;
using std::cout;

struct edge {
    edge* nex;
    llint to;
} graph[N << 1], *fir[N];
edge* tot = graph;
void add(llint a, llint b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

llint p[N];
llint f[N][M][2], g[N][M][2];
llint n, v, t1, t2;
llint ans;
llint val[N];  // 子节点权值和

auto max = [](auto a, auto b) { return a > b ? a : b; };

void dfs(llint nod, llint fa) {
    val[nod] = 0;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        dfs(e->to, nod);
        val[nod] += p[e->to];
    }
    f[nod][0][1] = g[nod][0][1] = -INF;  // 不合法方案，直接负无穷
    g[nod][1][1] = max(g[nod][1][1], val[nod] + p[fa]);

    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        llint mx1 = 0, mx2 = 0;
        for (llint j = v; ~j; --j) {
            mx1 = max(mx1, max(g[nod][v - j][0], g[nod][v - j][1]));
            mx2 = max(mx2, max(f[nod][v - j][0], f[nod][v - j][1] + p[fa] - p[e->to]));  // 如果当前节点有磁铁，那么再从子节点转移时会导致 p[son] 多算了一遍
            ans = max(max(ans, max(g[e->to][j][1], g[e->to][j][0]) + mx2), max(f[e->to][j][0], f[e->to][j][1]) + mx1);
        }
        for (llint j = 1; j <= v; ++j) {
            f[nod][j][0] = max(f[nod][j][0], max(f[e->to][j][0], f[e->to][j][1]));
            f[nod][j][1] = max(f[nod][j][1], max(f[e->to][j - 1][0], f[e->to][j - 1][1]) + val[nod]);
        }
        for (llint j = 1; j <= v; ++j) {
            g[nod][j][0] = max(g[nod][j][0], max(g[e->to][j][0], g[e->to][j][1]));
            g[nod][j][1] = max(g[nod][j][1], max(g[e->to][j - 1][0], g[e->to][j - 1][1]) + val[nod] + p[fa] - p[e->to]);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> v;
    for (llint i = 1; i <= n; ++i)
        cin >> p[i];
    for (llint i = 1; i < n; ++i) {
        cin >> t1 >> t2;
        add(t1, t2);
        add(t2, t1);
    }

    dfs(1, 0);

    cout << ans;

    return 0;
}