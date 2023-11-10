#include <algorithm>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

constexpr i32 mod = 10000;

i32 t, m, n;
i32 nex[100005];
i32 a[100005];

i64 binpow(i64 x, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) res = res * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> t;
    while (t--) {
        cin >> m;
        nex[1] = 0;
        cin >> a[1];
        for (i32 i = 2, j = 0; i <= m; ++i) {
            cin >> a[i];
            while (j && a[j + 1] != a[i])
                j = nex[j];
            if (a[j + 1] == a[i]) ++j;
            nex[i] = j;
        }
        i64 res = 0;
        for (i32 i = m; i; i = nex[i]) {
            res += binpow(n, i);
            if (res >= mod) res -= mod;
        }
        cout << std::setw(4) << std::setfill('0') << res << '\n';
    }

    return 0;
}