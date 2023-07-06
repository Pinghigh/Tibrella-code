#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

#define N 100005
#define K 25

using i32 = int;

struct edge {
    edge* nex;
    i32 to, fr;
} graph[N << 1], *fir[N];
edge* tot = graph;
void add(i32 a, i32 b) {
    tot->fr = a;
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

i32 dep[N], fa[N], dis[N];

void get_fa(i32 nod, i32 fat) {
    fa[nod] = fat;
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to == fat) continue;
        dep[to] = dep[nod] + 1;
        get_fa(to, nod);
    }
}

i32 n, k, t;
i32 t1, t2;
i32 nod[N];
i32 ans;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k >> t;
    memset(dis, 0x3f, sizeof(i32) * (n + 5));
    for (int i = 1; i < n; ++i) {
        cin >> t1 >> t2;
        add(t1, t2);
        add(t2, t1);
        nod[i] = i;
    }
    nod[n] = n;

    dep[1] = 1;
    get_fa(1, 0);

    std::sort(nod + 1, nod + n + 1, [](const i32& a, const i32& b) { return dep[a] > dep[b]; });

    for (int i = 1; i <= n; ++i) {
        i32 x = nod[i], y = nod[i];
        for (int d = 0; d <= k; ++d, y = fa[y]) {
            dis[x] = min(dis[x], dis[y] + d);
            if (!fa[y] || d == k) break;
        }
        if (dis[x] > k) {  // 距离最近的关键点距离大于 k
            for (int d = 0; d <= k && y; ++d, y = fa[y]) {
                dis[y] = min(d, dis[y]);
            }
            ++ans;
        }
    }

    cout << ans;

    return 0;
}