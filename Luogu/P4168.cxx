#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

#define N 40005
#define BLK 205  // block count

using i32 = int;
using i64 = long long;

i32 s[BLK][N];      // s[i][j] 前 i 个块 j 出现了几次
i32 mod[BLK][BLK];  // mod[i][j]，从块 i 到块 j 的众数

i32 n, m;
i32 blk_siz;
i32 a[N];
i32 bel[N];
std::vector<i32> b(1);
i32 blk_cnt;  // 总块数

i32 cnt[N];  // 桶
i32 l, r;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    b.reserve(n + 3);
    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
        b.emplace_back(a[i]);
    }

    // 离散化
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());

    for (i32 i = 1; i <= n; ++i)
        a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();

    // 处理块
    blk_siz = sqrt(n);
    blk_cnt = 1;
    for (i32 i = 1, id = 1; i <= n; ++i, ++blk_cnt) {
        if (blk_cnt > blk_siz) ++id, blk_cnt = 1;
        bel[i] = id;
    }
    blk_cnt = bel[n];

    // 预处理 s 数组
    for (i32 i = 1; i <= blk_cnt; ++i) {
        for (i32 pos = (i - 1) * blk_siz + 1, lim = std::min(n, blk_siz * i); pos <= lim; ++pos) {
            ++s[i][a[pos]];
        }
        for (i32 num = 1; num <= b.size(); ++num)
            s[i][num] += s[i - 1][num];
    }

    // 预处理 mod 数组
    for (i32 i = 1; i <= blk_cnt; ++i) {
        for (i32 j = i; j <= blk_cnt; ++j) {
            i32 mode = mod[i][j - 1];
            i32 mod_cnt = s[j][mode] - s[i - 1][mode];
            for (i32 pos = (j - 1) * blk_siz, lim = std::min(n, blk_siz * j); pos <= lim; ++pos) {
                if (mod_cnt < (s[j][a[pos]] - s[i - 1][a[pos]]))
                    mode = a[pos], mod_cnt = s[j][a[pos]] - s[i - 1][a[pos]];
                else if (mod_cnt == (s[j][a[pos]] - s[i - 1][a[pos]]) && a[pos] < mode)
                    mode = a[pos];
            }
            mod[i][j] = mode;
        }
    }

    // for (i32 i = 1; i <= blk_cnt; ++i) {
    //     for (i32 j = 1; j <= n; ++j)
    //         cout << s[i][j] << ' ';
    //     cout << '\n';
    // }
    i32 x = 0;
    while (m--) {
        cin >> l >> r;
        l = (l + x - 1) % n + 1, r = (r + x - 1) % n + 1;
        if (l > r) std::swap(l, r);
        if (bel[r] - bel[l] <= 1) {
            x = a[l];
            ++cnt[a[l]];
            for (i32 i = l + 1; i <= r; ++i) {
                if (++cnt[a[i]] > cnt[x])
                    x = a[i];
                else if (cnt[a[i]] == cnt[x] && a[i] < x)
                    x = a[i];
            }
            for (i32 i = l; i <= r; ++i)
                cnt[a[i]] = 0;
        } else {
            auto count = [](i32 x) -> i32 { return s[bel[r] - 1][x] - s[bel[l]][x] + cnt[x]; };  // 返回真正的 cnt
            x = mod[bel[l] + 1][bel[r] - 1];
            for (i32 i = l; bel[i] == bel[l]; ++i) {
                ++cnt[a[i]];
                if (count(a[i]) > count(x))
                    x = a[i];
                else if (count(a[i]) == count(x) && a[i] < x)
                    x = a[i];
            }
            for (i32 i = r; bel[i] == bel[r]; --i) {
                ++cnt[a[i]];
                if (count(a[i]) > count(x))
                    x = a[i];
                else if (count(a[i]) == count(x) && a[i] < x)
                    x = a[i];
            }

            // for (i32 i = 1; i <= n; ++i) {
            //     cout << count(i) << ' ';
            // }
            // cout << '\n';

            for (i32 i = l; bel[i] == bel[l]; ++i)
                cnt[a[i]] = 0;

            for (i32 i = r; bel[i] == bel[r]; --i)
                cnt[a[i]] = 0;
        }
        x = b[x];
        cout << x << '\n';
    }

    // for (i32 i = 1; i <= n; ++i)
    //     cout << a[i] << ' ';

    return 0;
}