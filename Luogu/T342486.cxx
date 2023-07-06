#include <cstring>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

#define N 100005

using i32 = int;
using f64 = double;
struct edge {
    edge* nex;
    i32 to;
} graph[N], *fir[N];
edge* tot = graph;

void add(i32 a, i32 b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

i32 n, a, b;

double ans;

i32 siz[N];

void dfs(i32 nod, i32 fa) {
    siz[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to != fa) {
            dfs(to, nod);
            siz[nod] += siz[to];
            ans += siz[to] * 1.0 * (n - siz[to]) * siz[to] * (n - siz[to]) / (n * (n - 1) / 2) / (n * (n - 1) / 2);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (cin >> n) {
        ans = 0;
        tot = graph;
        memset(fir, 0, sizeof(edge*) * (n + 5));
        for (int i = 1; i < n; ++i) {
            cin >> a >> b;
            add(a, b);
            add(b, a);
        }
        dfs(1, 0);
        cout << std::fixed << std::setprecision(6) << ans << '\n';
    }

    return 0;
}