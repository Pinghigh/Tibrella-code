#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 100005
#define BLK 400

i32 cnt[BLK][N];
i32 ans[BLK][BLK];
i32 bel[N];
i32 l[N], r[N];
i32 a[N];
i32 blksiz, blkcnt;
i32 n, c, m;

i32 buc[N], t[N]; // 桶 & 时间戳清空
i32 tim;

static inline char calc(const i32& cnt) {
    if (cnt & 1) {
        return (cnt > 1) ? -1 : 0;
    } return 1;
}

i32 query(const i32& l, const i32& r) {
    i32 res = 0;
    if (bel[l] == bel[r]) { // 同一块内
        for (i32 i = l; i <= r; ++ i) {
            if (t[a[i]] != tim) t[a[i]] = tim, buc[a[i]] = 0; // 时间戳
            ++buc[a[i]];
            res += calc(buc[a[i]]);
        }
        return res;
    }

    i32 lb = bel[l]+1, rb = bel[r]-1;    
    res = ans[lb][rb];

    for (i32 i = l; bel[i] == bel[l]; ++i) {
        if (t[a[i]] != tim) t[a[i]] = tim, buc[a[i]] = 0; // 时间戳
        ++buc[a[i]];
        res += calc(buc[a[i]] + cnt[lb][a[i]] - cnt[rb+1][a[i]]);
    }
    for (i32 i = r; bel[i] == bel[r]; --i) {
        if (t[a[i]] != tim) t[a[i]] = tim, buc[a[i]] = 0; // 时间戳
        ++buc[a[i]];
        res += calc(buc[a[i]] + cnt[lb][a[i]] - cnt[rb+1][a[i]]);
    }

    return res;
}

#define time() (std::chrono::steady_clock::now().time_since_epoch().count())

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> c >> m;
    blksiz = sqrt(n) + time() % 10 * (time() & 1 ? 1 : -1);

    for (i32 i = 1; i <= n; ++ i) cin >> a[i];

    blkcnt = 1;
    l[1] = 1;
    for (i32 i = 1, siz = 1; i <= n; ++i, ++siz) {
        bel[i] = blkcnt;
        if (siz == blksiz) {
            siz = 0;
            r[blkcnt] = i;
            l[++blkcnt] = i + 1;
        }
    }   
    blkcnt = bel[n];
    for (i32 i = 1; i <= blkcnt; ++ i) {
        i32 tmp = 0;
        for (i32 j = l[i]; j <= n; ++ j) {
            ++cnt[i][a[j]];
            tmp += (!(cnt[i][a[j]] & 1)) ? 1 : (cnt[i][a[j]] > 1 ? -1 : 0);
            if (bel[j] != bel[j+1]) ans[i][bel[j]] = tmp;
        }
    }

    // for (i32 i = 1; i <= blkcnt; ++ i) {
    //     for (i32 j = 1; j <= blkcnt; ++ j) cout << ans[i][j] << ' ';
    //     cout << '\n';
    // }

    // for (i32 i = 1; i <= n; ++ i) cout << bel[i] << ' ';
    // cout << '\n' << '\n';

    while (m--) {
        i32 l, r;
        static i32 ans = 0;
        ++tim;
        cin >> l >> r;
        l = (l + ans) % n + 1; r = (r + ans) % n + 1;
        if (l > r) std::swap(l, r);
        // cout << l << ' ' << r << '\n';
        cout << (ans = query(l, r)) << '\n';
        // cout << tim << '\n';
        // for (i32 i = 1; i <= n; ++ i) cout << t[a[i]] << ' ' ;
        // cout << '\n';
        // for (i32 i = 1; i <= n; ++ i) cout << buc[a[i]] << ' ' ;
        // cout << '\n';
    }

    

    return 0;
}