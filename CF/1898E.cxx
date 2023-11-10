#include <iostream>

using std::cin;
using std::cout;

using i32 = long long;
using i64 = long long;

#define N 300005
#define LOG 20

i32 f[LOG][N];
i32 log2[N];
i32 t;

void init() {
    log2[2] = 1;
    for (i32 i = 3; i < N; ++i)
        log2[i] = log2[i >> 1] + 1;
}

i32 query(const i32& l, const i32& r) {
    const i32& m = r - l + 1;
    return f[log2[m]][l] & f[log2[m]][r - (1 << log2[m]) + 1];
};

void solve() {
    int n;
    cin >> n;
    for (i32 i = 1; i <= n; ++i)
        cin >> f[0][i];
    for (i32 lg = 1; lg <= log2[n]; ++lg)
        for (i32 i = 1; i + (1 << lg) - 1 <= n; ++i) {
            f[lg][i] = f[lg - 1][i] & f[lg - 1][i + (1 << (lg - 1))];
        }

    i32 q;
    cin >> q;
    while (q--) {
        i32 k, ll;
        cin >> ll >> k;
        if (f[0][ll] < k)
            cout << "-1 ";
        else {
            i32 l = ll, r = n;
            while (r > l) {
                i32 mid = (l + r + 1) >> 1;
                if (query(ll, mid) >= k)
                    l = mid;
                else
                    r = mid - 1;
            }
            cout << l << ' ';
        }
    }

    if (t) {
        for (i32 l = 1; l <= log2[n]; ++l)
            for (i32 i = 1; i <= n; ++i)
                if (f[l][i])
                    f[l][i] = 0;
                else
                    break;
    }
    cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();

    cin >> t;
    while (t--)
        solve();

    return 0;
}
