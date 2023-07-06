#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using f64 = double;

#define N 100005

struct edge {
    edge* nex;
    i32 to;
} graph[N << 1], *fir[N];
edge* tot = graph;
i32 dep[N];

void dfs(i32 nod, i32 fa) {
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to == fa) continue;
        dep[to] = dep[nod] + 1;
        dfs(to, nod);
    }
}

void add(i32 u, i32 v) {
    tot->to = v;
    tot->nex = fir[u];
    fir[u] = tot++;
}

i32 n, t1, t2;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i < n; ++i) {
        cin >> t1 >> t2;
        add(t1, t2);
        add(t2, t1);
    }

    dep[1] = 1;
    dfs(1, 0);

    f64 ans = 0;
    for (i32 i = 1; i <= n; ++i) {
        ans += 1 * 1.0 / dep[i];
    }
    cout << std::fixed << ans;

    return 0;
}