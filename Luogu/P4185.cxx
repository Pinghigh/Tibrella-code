#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 100001

i32 fa[N], siz[N];
i32 find(i32 x) {
    return (fa[fa[x]] == fa[x]) ? fa[x] : fa[x] = find(fa[x]);
}
void merge(i32 x, i32 y) {
    // cout << x << ' ' << y << '\n';
    x = find(x), y = find(y);
    if (x != y) {
        if (siz[x] > siz[y])
            fa[y] = x, siz[x] += siz[y];
        else
            fa[x] = y, siz[y] += siz[x];
    }
}

struct edge_t {
    i32 u, v, w;

    bool operator>(const edge_t& b) const& {
        return w > b.w;
    }

    void read() {
        cin >> u >> v >> w;
    }
} edge[N];

struct query_t {
    i32 k, x, id;
    bool operator>(const query_t& b) const& {
        return k > b.k;
    }
    void read(i32 id) {
        cin >> k >> x;
        this->id = id;
    }
} query[N];

i32 ans[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, q;
    cin >> n >> q;
    for (i32 i = 1; i <= n; ++i)
        siz[i] = 1, fa[i] = i;

    for (i32 i = 1; i < n; ++i)
        edge[i].read();
    for (i32 i = 1; i <= q; ++i)
        query[i].read(i);

    std::sort(edge + 1, edge + n, std::greater<edge_t>()), std::sort(query + 1, query + q + 1, std::greater<query_t>());

    for (i32 i = 1, j = 1; i <= q; ++i) {
        // cout << query[i].id << ' ' << query[i].k << '\n';
        while (j < n && edge[j].w >= query[i].k) {
            // cout << edge[j].w << ' ';
            merge(edge[j].u, edge[j].v);
            ++j;
        }
        ans[query[i].id] = siz[find(query[i].x)] - 1;
        // cout << ans[query[i].id] << '\n';
    }

    for (i32 i = 1; i <= q; ++i)
        cout << ans[i] << '\n';

    return 0;
}