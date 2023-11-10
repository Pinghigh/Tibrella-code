#include <cmath>
#include <iostream>

using std::cin;
using std::cout;

#define N 50005
#define SIZ 240

using i32 = int;
using i64 = long long;

i32 a[N];
// i32 sum[SIZ];
i32 tag[SIZ];
i32 bel[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    i32 blksiz = sqrt(n);
    i32 blkcnt = 1;
    for (i32 i = 1, siz = 1; i <= n; ++i, ++siz) {
        cin >> a[i];
        // sum[blkcnt] += a[i];
        bel[i] = blkcnt;
        if (siz >= blksiz) siz = 0, ++blkcnt;
    }
    blkcnt = bel[n];  // 可能超 1

    for (i32 i = 1; i <= n; ++i) {
        i32 op, l, r, x;
        cin >> op >> l >> r >> x;
        if (!op) {
            if (bel[l] == bel[r])
                while (l <= r)
                    a[l++] += x;
            else {
                for (i32 i = bel[l] + 1; i <= bel[r] - 1; ++i)
                    tag[i] += x;
                for (i32 i = l; bel[i] == bel[l]; ++i)
                    a[i] += x;
                for (i32 i = r; bel[i] == bel[r]; --i)
                    a[i] += x;
            }
        } else
            cout << a[r] + tag[bel[r]] << '\n';
    }

    return 0;
}