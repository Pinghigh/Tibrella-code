#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 200005

struct edge {
    i32 fr, to;
    i64 dis;

    void init() {
        cin >> fr >> to >> dis;
    }
} set[N];

i32 t;
i32 n, m;
i64 k;
i32 fa[N], rk[N];

i32 find(i32 a) {
    if (a != fa[a]) fa[a] = find(fa[a]);
    return fa[a];
}

bool merge(i32 a, i32 b) {
    i32 af = find(a), bf = find(b);
    if (af == bf)
        return false;
    else {
        if (rk[af] > rk[bf]) {
            fa[bf] = af;
            rk[af] = std::max(rk[af], rk[bf] + 1);
        } else {
            fa[af] = bf;
            rk[bf] = std::max(rk[bf], rk[af] + 1);
        }
        return true;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        std::iota(fa + 1, fa + n + 1, 1);

        for (i32 i = 1; i <= m; ++i)
            set[i].init();

        std::sort(set + 1, set + m + 1, [](edge a, edge b) -> bool { return a.dis < b.dis; });

        i32 cnt = 0;
        i64 ans = 0;
        for (edge* e = set + 1; cnt < n - 1; ++e) {
            if (merge(e->fr, e->to)) {
                ++cnt;
                if (e->dis > k) ans += e->dis - k;
            }
        }

        if (ans)
            cout << ans << '\n';
        else {
            i32 i = std::lower_bound(set + 1, set + m + 1, k, [](edge e, i32 x) -> bool { return e.dis < x; }) - set;
            // cout << std::min(set[i].dis - k, k - set[i - 1].dis) << '\n';

            if (i > m)
                cout << k - set[i - 1].dis << '\n';
            else if (i == 1)
                cout << set[i].dis - k << '\n';
            else
                cout << std::min(set[i].dis - k, k - set[i - 1].dis) << '\n';

            // cout << set[i].dis << '\n';
        }

        if (t) memset(rk + 1, 0, sizeof(i32) * n);
    }

    return 0;
}