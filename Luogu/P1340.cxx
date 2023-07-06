#include <iostream>
#include <set>

using std::cin;
using std::cout;
using std::multiset;

using i32 = int;

struct edge {
    i32 fr, to, w;
    bool operator<(const edge& b) const {
        return w < b.w;
    }
};
multiset<edge> s;
#define N 205
#define W 6005

i32 fa[N], siz[N];

i32 find(i32 nod) {
    if (fa[nod] != nod) fa[nod] = find(fa[nod]);
    return fa[nod];
}

void merge(i32 x, i32 y) {
    i32 fx = find(x), fy = find(y);
    if (x != y) {
        if (siz[fx] >= siz[fy]) {
            fa[fy] = fx;
            siz[fx] += siz[fy];
        } else {
            fa[fx] = fy;
            siz[fy] += siz[fx];
        }
    }
}

i32 n, w;

i32 kruskal() {
    for (int i = 1; i <= n; ++i)
        fa[i] = i, siz[i] = 1;
    i32 res = 0;
    for (auto& e : s) {
        if (find(e.fr) != find(e.to)) {
            res += e.w;
            merge(e.fr, e.to);
            if (siz[find(1)] >= n) return res;
        }
        // cout << siz[find(1)] << ' ';
    }
    return -1;
}

i32 t1, t2, t3;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> w;
    for (int i = 1; i <= w; ++i) {
        cin >> t1 >> t2 >> t3;
        s.insert({ t1, t2, t3 });
        cout << kruskal() << '\n';
    }

    return 0;
}