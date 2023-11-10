#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

void solve() {
    string s;
    long long q;
    cin >> s >> q;
    auto n = s.size();
    s = ' ' + s;
    if (q == 1) {
        cout << s[1];
        return;
    } else if (q <= n) {
        cout << s[q];
        return;
    }
    long long l = 1, r = n;
    while (r > l) {
        long long mid = (l + r) >> 1;
        if (n * (n + 1) / 2 - (mid * (mid - 1)) / 2 < q)
            r = mid;
        else
            l = mid + 1;
    }
    // cout << r << '\n';
    q -= n * (n + 1) / 2 - (r * (r - 1ll)) / 2;
    --r;
    auto& id = r;
    static char stk[1000001];
    int top = 0, lim = 0;
    for (int i = 1; i <= n; ++i) {
        while (top && lim < n - id && stk[top] > s[i]) --top, ++lim;
        stk[++top] = s[i];
    }
    cout << stk[q];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}