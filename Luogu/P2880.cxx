// P3895
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

using i32 = int;
using i64 = long long;

#define N 50001
#define LG 16

i32 mn[LG][N], mx[LG][N];
i32 lg[N];
i32 a[N];

void init(const i32& n) {
    for (i32 i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;

    for (i32 l = 0, lim = lg[n]; l <= lim; ++l)
        for (i32 i = 1; i + (1 << l) - 1 <= n; ++i)
            if (!l)
                mn[l][i] = a[i];
            else
                mn[l][i] = min(mn[l - 1][i], mn[l - 1][i + (1 << (l - 1))]);

    for (i32 l = 0, lim = lg[n]; l <= lim; ++l)
        for (i32 i = 1; i + (1 << l) - 1 <= n; ++i)
            if (!l)
                mx[l][i] = a[i];
            else
                mx[l][i] = max(mx[l - 1][i], mx[l - 1][i + (1 << (l - 1))]);
}

i32 query(i32 l, i32 r) {
    i32 lg2 = lg[r - l + 1];
    return max(mx[lg2][l], mx[lg2][r - (1 << lg2) + 1]) - min(mn[lg2][l], mn[lg2][r - (1 << lg2) + 1]);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, q;
    cin >> n >> q;
    for (i32 i = 1; i <= n; ++i)
        cin >> a[i];
    init(n);
    while (q--) {
        i32 l, r;
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }

    return 0;
}