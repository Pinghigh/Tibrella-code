// P3366

#include <algorithm>
#include <bitset>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::sort;

#define PII pair<int, int>
#define N 51400
#define M 2005140

struct edge {
    int u, v, w;
    bool operator<(const edge& exa) { return w < exa.w; }
} gra[M];

int fa[N];
int ans;
int rk[N];
int n, m;
int cnt;
int t1, t2;  // tmp

int max(int a, int b) { return (a > b ? a : b); }
int min(int a, int b) { return (a < b ? a : b); }

int find(int a) {
    if (fa[a] != a) {
        fa[a] = find(fa[a]);
    }
    return fa[a];
}

void uni(int a, int b) {
    t1 = find(a);
    t2 = find(b);
    if (rk[t1] > rk[t2]) {
        fa[t2] = t1;
        rk[t1] = max(rk[t1], rk[t2] + 1);
    } else {
        fa[t1] = t2;
        rk[t2] = max(rk[t2], rk[t1] + 1);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        cin >> gra[i].u >> gra[i].v >> gra[i].w;
    }

    sort(gra + 1, gra + m);

    for (int i = 1; i <= m; ++i) {
        t1 = find(gra[i].u);
        t2 = find(gra[i].v);
        if (t1 == t2) {
            continue;
        }
        ans += gra[i].w;
        ++cnt;
        uni(gra[i].u, gra[i].v);
    }

    if (cnt == n - 1) {
        cout << ans << endl;
    } else {
        cout << "orz" << endl;
    }

    return 0;
}
