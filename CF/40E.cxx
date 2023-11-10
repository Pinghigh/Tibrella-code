#include <iostream>
#include <utility>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 1003

i32 cnt[N], cnt1[N];
i32 pow2[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, m, a, b, c, p, k;
    i32 ans = 0;
    cin >> n >> m;
    bool flag = n > m;
    if ((n & 1) != (m & 1)) goto failed;

    if (!flag) std::swap(m, n);
    cin >> k;
    for (i32 i = 1; i <= k; ++ i) {
        if (flag)
            cin >> a >> b >> c;
        else cin >> b >> a >> c;

        ++cnt[a];
        cnt1[a] += (c == -1);
        if (cnt[a] == m && (cnt1[a] & 1) == 0) goto failed;
    }

    cin >> p;
    ans = 1;
    pow2[0] = 1;
    for (i32 i = 1; i <= n; ++ i) 
        pow2[i] = (pow2[i - 1] << 1ll) % p;
    
    for (i32 i = 1; i < n; ++ i) 
        if (!cnt[i]) {
            std::swap(cnt[i], cnt[n]);
            break;
        }

    for (i32 i = 1; i < n; ++ i) 
        if (m - cnt[i]) ans = ans * 1ll * pow2[m - cnt[i] - 1] % p;
    
    cout << ans;

    return 0;

failed:
    cout << '0';
    return 0;
}