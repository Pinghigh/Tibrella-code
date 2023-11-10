#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

using pii = std::pair<i32, i32>;

const i64 mod = 1e9+7;

#define N 200005

i64 fact[N], ifact[N];

i64 binpow(i64 x, i64 p) {
    i64 res = 1;
    while(p) {
        if (p&1) res = res * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return res;
}

pii b[2005];
i32 h, w, n;
i32 t1, t2;

i64 C(i32 a, i32 b) {
    if (b>a)return 0;
    else return fact[a]*ifact[b]%mod*ifact[a-b]%mod;
}

i64 f[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> h >> w >> n;
    for (i32 i = 1; i <= n; ++ i) {
        cin >> t1 >> t2;
        b[i] = {t1, t2};
    }
    std::sort(b+1,b+n+1);
    b[n+1]={h,w}, b[0] = {1, 1};

    fact[0]=ifact[0]=1;
    for (i32 i = 1; i <= 200000; ++ i) fact[i] = fact[i-1]*i%mod;
    ifact[200000]=binpow(fact[200000],mod-2);
    for (i32 i = 200000-1; i; --i) ifact[i] = ifact[i+1]*(i+1)%mod;

    // cout << fact[10000] << ' ' << ifact[10000] << '\n';

    for (i32 i = 1; i <= n+1; ++ i) {
        const i32 &xi = b[i].first, &yi = b[i].second;
        f[i] = C(xi+yi-2,xi-1);
        for (i32 j = 1; j < i; ++ j) {
            const i32 &xj = b[j].first, &yj = b[j].second;
            if (xj > xi || yj > yi) continue;
            f[i] -= f[j]*C(xi-xj+yi-yj,xi-xj)%mod;
            if (f[i]<0)f[i]+=mod;
        }
    }
    // const i64 &ans = C(h+w-2,h-1)-f[n+1];
    cout << f[n+1]%mod;

    return 0;
}