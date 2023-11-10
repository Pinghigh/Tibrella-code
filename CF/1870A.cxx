#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i32 = long long;
using i64 = long long;

void solve() {
    i32 n, k, x;
    cin >> n >> k >> x;
    if (x < k - 1 || n <= k - 1 || (x == 0 && k != 1)) {
        cout << "-1\n";
        return;
    }
    i64 ans = 0;
    for (i32 i = 0; i < k; ++i)
        ans += i;
    if (n > k) {
        if (x == k)
            ans += (n - k) * (x - 1);
        else
            ans += (n - k) * x;
    }
    cout << ans << '\n';
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