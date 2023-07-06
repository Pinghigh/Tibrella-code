#include <bitset>
#include <iostream>

using std::bitset;
using std::cin;
using std::cout;
#define endl '\n'

constexpr int N = 5e5 + 514;
constexpr int LOG = 19;

int n, m, s;
int x, y;
int a, b;
int fa[N];
int logn[N];
int f[LOG][N];
int dep[N];
bitset<N> st;

template <typename T>
T max(T exa1, T exa2) {
    return exa1 > exa2 ? exa1 : exa2;
}

struct edge {
    int u, v;
    edge* nex;
} tree[N << 1];
edge* tot = tree;
edge* fir[N];

void add(int fr, int to) {
    ++tot;
    tot->u = fr;
    tot->v = to;
    tot->nex = fir[fr];
    fir[fr] = tot;
}

void init_log() {
    logn[1] = 0;
    logn[2] = 1;
    for (int i = 3; i <= N; ++i) {
        logn[i] = logn[i >> 1] + 1;
        // cout << logn[i] << endl;
    }
}

int get_lca(int fir, int sec) {
    while (dep[fir] > dep[sec]) {
        fir = f[logn[dep[fir] - dep[sec]]][fir];
    }
    while (dep[sec] > dep[fir]) {
        sec = f[logn[dep[sec] - dep[fir]]][sec];
        // cout << 1;
    }
    if (fir == sec) {
        return sec;
    }
    for (int i = logn[dep[fir]]; i >= 0; --i) {
        if (f[i][fir] != f[i][sec]) {
            fir = f[i][fir];
            sec = f[i][sec];
        }
    }
    return f[0][fir];
}

void dfs(int nod, int fat) {
    f[0][nod] = fat;
    dep[nod] = dep[fat] + 1; // 需要更新深度数组

    for (int i = 1; i <= logn[dep[nod]]; ++i) {
        f[i][nod] = f[i - 1][f[i - 1][nod]]; // 更新 f 数组
    }

    st[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (!st[e->v]) {
            dfs(e->v, nod);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    init_log();

    cin >> n >> m >> s;
    fa[s] = s;
    for (int i = 1; i < n; ++i) {
        cin >> x >> y;
        fa[x] = y;
        add(x, y);
        add(y, x);
    }

    dfs(s, 0);

    while (m--) {
        cin >> a >> b;
        if (dep[a] < dep[b]) {
            x = a;
            a = b;
            b = x;
        } // 保证 a 是深度更深的点
        cout << get_lca(a, b) << endl;
    }

    return 0;
}