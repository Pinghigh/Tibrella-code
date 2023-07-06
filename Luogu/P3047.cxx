#include <iostream>


using std::cin;
using std::cout;

#define N 100005
#define endl '\n'
#define K 25

int n, k, t1, t2;

struct edge {
    edge* nex;
    int to;
} graph[N << 1], *fir[N];
edge* tot = graph;
void add(int a, int b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

int f[N][K], c[N], dep[N];

void init(int nod, int fa) {
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        dep[e->to] = dep[nod] + 1;
        init(e->to, nod);
        for (int i = k; i; --i) {
            f[nod][i] += f[e->to][i - 1];
        }
    }
}

void dfs(int nod, int fa) {
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        for (int j = k; j > 1; --j)
            f[e->to][j] -= f[e->to][j - 2];
        for (int j = 1; j <= k; ++j)
            f[e->to][j] += f[nod][j - 1];
        dfs(e->to, nod);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        cin >> t1 >> t2;
        add(t1, t2);
        add(t2, t1);
    }
    for (int i = 1; i <= n; ++i)
        cin >> f[i][0];

    init(1, 0);
    dfs(1, 0);

    for (int i = 1; i <= n; ++i) {
        int ans = f[i][0];
        for (int j = 1; j <= k; ++ j) ans += f[i][j];
        cout << ans << endl;
    }

    return 0;
}