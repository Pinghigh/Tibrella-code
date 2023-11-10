#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

#define N 50005
#define SIZ 250

using i32 = int;
using i64 = long long;

i32 a[N];
std::vector<i32> blk[SIZ];
// i32 sum[SIZ];
i32 tag[SIZ];
i32 bel[N], rd[N];

#define all(x) x.begin(), x.end()

void modify(i32 l, i32 r, i32 x) {
    for (i32 i = bel[l] + 1; i <= bel[r] - 1; ++i)
        tag[i] += x;
    if (bel[l] != bel[r]) {
        for (i32 i = l; bel[i] == bel[l]; ++i)
            a[i] += x;
        for (i32 i = r; bel[i] == bel[r]; --i)
            a[i] += x;
    } else
        for (i32 i = l; i <= r; ++i)
            a[i] += x;

    blk[bel[l]].clear();
    for (i32 i = rd[bel[l] - 1] + 1; i <= rd[bel[l]]; ++i)
        blk[bel[l]].emplace_back(a[i]);
    std::sort(all(blk[bel[l]]));
    if (bel[l] != bel[r]) {
        blk[bel[r]].clear();
        for (i32 i = rd[bel[r] - 1] + 1; i <= rd[bel[r]]; ++i)
            blk[bel[r]].emplace_back(a[i]);
        std::sort(all(blk[bel[r]]));
    }
}

i32 query(i32 l, i32 r, i64 x) {
    i32 res = 0;
    for (i32 i = bel[l] + 1; i <= bel[r] - 1; ++i)
        res += std::lower_bound(all(blk[i]), x - tag[i]) - blk[i].begin();
    if (bel[l] != bel[r]) {
        for (i32 i = l; i <= rd[bel[l]]; ++i)
            if (a[i] < x - tag[bel[i]]) ++res;
        for (i32 i = r; i > rd[bel[r] - 1]; --i)
            if (a[i] < x - tag[bel[i]]) ++res;
    } else
        for (i32 i = l; i <= r; ++i)
            if (a[i] < x - tag[bel[i]]) ++res;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    i32 blksiz = sqrt(n * log2(n));
    i32 blkcnt = 1;
    for (i32 i = 1, siz = 1; i <= n; ++i, ++siz) {
        cin >> a[i];
        // sum[blkcnt] += a[i];
        bel[i] = blkcnt;
        blk[blkcnt].emplace_back(a[i]);
        if (siz >= blksiz) siz = 0, rd[blkcnt++] = i;
    }
    blkcnt = bel[n];  // 可能超 1
    rd[blkcnt] = n;
    for (i32 i = 1; i <= blkcnt; ++i)
        std::sort(all(blk[i]));

    for (i32 i = 1; i <= n; ++i) {
        i32 op, l, r;
        i64 x;
        cin >> op >> l >> r >> x;
        if (!op) {
            modify(l, r, x);
        } else {
            cout << query(l, r, x * x) << '\n';
        }
    }

    // for (i32 i = 1; i <= n; ++i)
    //     cout << a[i] + tag[i] << ' ';
    // cout << '\n';

    // for (i32 i = 1; i <= n; ++i)
    //     cout << a[i] + tag[i] << ' ';

    return 0;
}