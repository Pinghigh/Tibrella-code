#include <iostream>

using std::cin;
using std::cout;

void solve() {
    long long n, k, x;
    cin >> n >> k >> x;
    long long min = (1 + k) * k / 2;
    long long max = min + k * (n - k);
    if (x <= max && x >= min) cout << "YES\n";
    else cout << "NO\n";
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
