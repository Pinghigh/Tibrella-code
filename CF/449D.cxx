#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 2000006

i32 f[N];
i32 n;

constexpr i32 mod = 1e9+7;

constexpr i32 s = (1 << 20) - 1;

void sos(const i64& x) {
    for (i32 i = 0; i < 20; ++ i)
        for (i32 j = s; j >= 0; -- j) 
            if((j & (1 << i)) == 0)
                f[j] = (f[j] + f[j ^ (1 << i)] * x % mod + mod) % mod; 
}

i32 binpow(i32 p) {
    i32 x = 2, res = 1; 
    while (p) {
        if (p & 1) res = x * 1ll * res % mod;
        x = x * 1ll * x % mod;
        p >>= 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    i32 x;

    cin >> n;
    for (i32 i = 1; i <= n; ++ i) {
        cin >> x;
        ++f[x];
    }

    sos(1);
    for (i32 i = 0; i <= s; ++ i) f[i] = binpow(f[i]) - 1;
    sos(-1);

    cout << f[0];
    

    return 0;
}