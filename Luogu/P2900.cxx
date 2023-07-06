#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

#define N 50004

using i32 = int;
using i64 = long long;
using f64 = double;

i32 n;
struct land {
    i64 w, l;
} buy[N];
i64 f[N];
i64 q[N], hh, tt;

f64 calc(i32 i, i32 j) {
    return (f[j] - f[i] * 1.0) / -(buy[j + 1].w - buy[i + 1].w);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i)
        cin >> buy[i].w >> buy[i].l;

    std::sort(buy + 1, buy + n + 1, [](const land& a, const land& b) -> bool {
        if (a.w != b.w)
            return a.w > b.w;
        else
            return a.l > b.l;
    });

    /*
        去掉无用矩形之后的序列的 l 一定单调递减
        证明：排序使得 w 单调递增，于是导致 l 不单调递减的矩形一定无用。
    */

    i32 l = 0;
    for (i32 i = 1; i <= n; ++i) {
        if (buy[l].l < buy[i].l) buy[++l] = buy[i];
    }
    n = l;

    hh = 1, tt = 0;
    q[++tt] = 0;
    for (i32 i = 1; i <= n; ++i) {
        while (tt > hh && calc(q[hh], q[hh + 1]) <= buy[i].l)
            ++hh;
        f[i] = f[q[hh]] + buy[q[hh] + 1].w * buy[i].l;
        while (tt > hh && calc(q[tt - 1], q[tt]) >= calc(q[tt], i))
            --tt;
        q[++tt] = i;
    }
    cout << f[n];

    return 0;
}