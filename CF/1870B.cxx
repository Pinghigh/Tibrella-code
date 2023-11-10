#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 200005
i32 a[N], b[N];
std::bitset<40> ba, bb;

void solve() {
    i32 n, m;
    cin >> n >> m;

    i32 mx = 0, mn = 0;
    i32 bx = 0, ax = 0;
    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
        ax ^= a[i];
    }
    for (i32 i = 1; i <= m; ++i) {
        cin >> b[i];
        bx |= b[i];
    }
    if (n & 1) {
        cout << ax << ' ' << (ax|bx) << '\n';
    } else {
        cout << (ax&(~bx)) << ' ' << ax << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}