#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>

using std::cin;
using std::cout;

#define N 100005

using i32 = int;
using i64 = long long;

const i64 val = 1e5;

std::bitset<N> b1, b2;
struct q {
    i32 l, r;
    i32 op;
    i32 x;
    i32 id;

    void init(const i32& idx) {
        id = idx;
        cin >> op >> l >> r >> x;
    }
} que[N];
i32 a[N];
i32 cnt[N];
i32 bel[N];
i32 n, m;
i32 blk_siz;

std::bitset<N> ans;

void add(const i32& x) {
    i32 v = a[x];
    if (!cnt[v]++) b1[v] = b2[val - v] = true;
}
void del(const i32& x) {
    i32 v = a[x];
    if (!--cnt[v]) b1[v] = b2[val - v] = false;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i)
        cin >> a[i];
    for (i32 i = 1; i <= m; ++i)
        que[i].init(i);

    blk_siz = n / std::sqrt(1.0 * m);
    if (blk_siz < 1) blk_siz = 1;
    for (i32 i = 1, cnt = 1, id = 1; i <= n; ++i, ++cnt) {
        if (cnt > blk_siz) cnt = 1, ++id;
        bel[i] = id;
    }

    std::sort(que + 1, que + m + 1, [](q& a, q& b) -> bool {
        if (bel[a.l] != bel[b.l])
            return bel[a.l] < bel[b.l];
        else if (a.r != b.r)
            return ((bel[a.l] & 1) ? a.r < b.r : a.r > b.r);
        else
            return a.l < b.l;
    });

    i32 l, r;
    l = r = 1;
    b1[a[1]] = b2[val - a[1]] = true;
    ++cnt[a[1]];

    for (i32 i = 1; i <= m; ++i) {
        q& x = que[i];
        while (l > x.l)
            add(--l);
        while (r < x.r)
            add(++r);
        while (l < x.l)
            del(l++);
        while (r > x.r)
            del(r--);

        if (x.op == 1)
            ans[x.id] = (b1 & (b1 << x.x)).any();
        else if (x.op == 2) {
            ans[x.id] = (b1 & (b2 >> (val - x.x))).any();
            // std::cerr << b1.to_string() << '\n' << (b2 >> (val - x.x)).to_string() << '\n';
        } else {
            for (i32 i = 1, lim = sqrt(x.x); i <= lim; ++i) {
                if (x.x % i == 0) {
                    if (b1[i] && b1[x.x / i]) {
                        ans[x.id] = true;
                        break;
                    }
                }
            }
        }
    }

    for (i32 i = 1; i <= m; ++i) {
        if (ans[i])
            cout << "hana\n";
        else
            cout << "bi\n";
    }

    return 0;
}