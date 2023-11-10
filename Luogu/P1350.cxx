#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

constexpr i32 mod = 1e5+3;

#define N 4005

i64 f[N][N];

i32 a,b,c,d;
i64 k;

i64 l[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    cin >> a >> b >> c >> d >> k;

    for (i32 i = 0; i <= b+d; ++ i) f[i][0] = 1;
    for (i32 i = 1; i <= b+d; ++ i) l[i] = i<=b?a:a+c;

    for (i32 i = 1; i <= b+d; ++ i) 
        for (i32 j = 1; j <= std::min(k, l[i]); ++ j) f[i][j] = (f[i-1][j-1] * (l[i]-j+1) % mod + f[i-1][j]) % mod;
    
    cout << f[b+d][k] % mod;

    return 0;
}