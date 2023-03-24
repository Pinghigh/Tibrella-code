#include <bits/stdc++.h>

using namespace std;

#define eb emplace_back

const int N = 5e5 + 10;
const int mod = 1e9 + 7;

int add(int a, int b) {return (a + b >= mod) ? (a + b - mod) : (a + b);}
 
int n;
int a[N], b[N], tot;

vector<int> vec[N];

signed main() {
    #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
    #endif
    ios :: sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        cin >> a[i];
        b[++ tot] = a[i];
    }
    sort(b + 1, b + 1 + n);
    tot = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; ++ i) { 
        a[i] = lower_bound(b + 1, b + 1 + tot, a[i]) - b;
        vec[a[i]].eb(i);
    }
    int ans = 0;
    for (int i = 1; i <= tot; ++ i) {
        if (!vec[i].size()) continue;
        int siz = vec[i].size();
        ans = add(ans, 1ll * vec[i][0] * (n - vec[i][0] + 1) % mod * b[i] % mod);
        for (int j = 1; j < siz; ++ j) {
            ans = add(ans, 1ll * (vec[i][j] - vec[i][j - 1]) * (n - vec[i][j] + 1) % mod * b[i] % mod);
        }
    }
    cout << ans << '\n';
    return 0;
}