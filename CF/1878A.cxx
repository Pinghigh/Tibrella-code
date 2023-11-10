#include <iostream>

using std::cin;
using std::cout;

void solve() {
    int n, k;
    cin >> n >> k;
    bool flag = false;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        flag |= (x == k);
    }
    cout << (flag ? "YES\n" : "NO\n");
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
