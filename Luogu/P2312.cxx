#include <stdio.h>
#include <algorithm>
#include <vector>

using i32 = int;
using i64 = long long;

constexpr i64 mod = 1610612741;
std::vector<i32> x;

#define N 105

i32 n, m;
i64 a[4][N];

int main() {
    scanf("%d %d", &n, &m);

    for (i32 i = 0; i <= n; ++ i) {
        bool f = false;
        char c;
        do {
            c = getchar();
            if (c == '-') f = true;
        } while (c < 48 || c > 57);
        do {
            c ^= 48;
            ((a[0][i] *= 10) += c) %= mod;
            c = getchar();
        } while (c > 47 && c < 58);
        if (f) a[0][i] = (a[0][i] * -1 % mod + mod)%mod;
    }

    i32 ans = 0;
    for (i32 i = 1; i <= m; ++ i) {
        i64 res = 0; 
        for (i32 k = n; k > -1; -- k)
            res = (res * i % mod + a[0][k]) % mod;
        if (res == 0) x.emplace_back(i), ++ans;
    }
    printf("%d\n", ans);
    for (const auto& k : x) {
        printf("%d\n", k);
    }

    // for (i32 i = 0; i <= n; ++ i) printf("%lld\n",a[0][i]);

    // i64 res = 0;
    // for (i32 k = n; k>-1; -- k) 
    //     res = (res * 1 % modlist[0] + a[0][k]) % modlist[0];
    // printf("%lld",res);

    return 0;
}