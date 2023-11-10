#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

constexpr i64 mod = 1e9+7;

#define N 1000006   

i64 fact[N], ifact[N];
i32 m, n, t;

void exgcd(i64 a, i64 b, i64&x, i64&y) {
    if (!b) return x=1,y=0,void();
    exgcd(b,a%b,x,y);
    i64 tmp = x;
    x = y;
    y = tmp - (a/b)*y;
}

i64 inv(const i64& a) {
    i64 x, y;
    exgcd(a,mod,x,y);
    return x;
}

i64 f[N];

i64 C(i64 a, i64 b) {
    if (b>a) return 0;
    return fact[a]*ifact[b]%mod*ifact[a-b]%mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    f[2]=1, fact[0]=ifact[0]= 1;
    for (i32 i = 1; i < N; ++ i) fact[i] = fact[i-1]*i%mod;
    for (i32 x = 3; x < N; ++ x) f[x] = (x-1)*(f[x-1]+f[x-2])%mod;
    ifact[N-1] = inv(fact[N-1]);
    for (i32 i = N-2; i; --i) ifact[i] = ifact[i+1]*(i+1)%mod;

    cin >> t;
    do {
        cin >> n >> m;
        if (n == m) cout << "1\n";
        else cout << f[n-m]*C(n,m)%mod << '\n';
    } while(--t);

    return 0;
}