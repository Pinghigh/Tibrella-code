#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using f64 = double;

#define N 500005

struct edge {
    edge* nex;
    i32 to;
    f64 p;
} graph[N << 1], *fir[N];
edge* tot = graph;
void add(i32 a, i32 b, i32 w) {
    tot->nex = fir[a];
    tot->to = b;
    tot->p = w / 100.0;
    fir[a] = tot++;
}

i32 n;
f64 f[N];
f64 q[N];
i32 t1, t2, t3;
f64 ans;

void dfs1(i32 nod, i32 fa) {
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to == fa) continue;
        dfs1(to, nod);
        f[nod] += (1 - f[nod]) * f[to] * e->p;
    }
}

void dfs2(i32 nod, i32 fa) {
    ans += f[nod];
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to == fa) continue;
        if (f[to] != 1.0) f[to] += (1 - f[to]) * e->p * (f[nod] - e->p * f[to]) / (1 - e->p * f[to]);
        dfs2(to, nod);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; ++i) {
        cin >> t1 >> t2 >> t3;
        add(t1, t2, t3);
        add(t2, t1, t3);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> q[i];
        q[i] /= 100;
        f[i] = q[i];
    }

    dfs1(1, 0);
    dfs2(1, 0);

    cout << std::fixed << std::setprecision(6) << ans;

    return 0;
}