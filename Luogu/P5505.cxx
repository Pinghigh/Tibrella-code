#include <iostream>

using std::cin;
using std::cout;

namespace tkgs {
    using i32 = int;
    using i64 = long long;
    const i64 mod = 1e9 + 7;

#define N 1005
#define NUM 2005
    namespace mat {
        i64 x, y, tmp;
        void exgcd(const i64& a, const i64& b) {
            if (!b) {
                x = 1, y = 0;
            } else {
                exgcd(b, a % b);
                tmp = x;
                x = y;
                y = tmp - a / b * y;
            }
        }

        i64 inv(const i64& a, const i64& b) {
            exgcd(a, b);
            return x;
        }

        i64 fact[NUM], ifact[NUM];

        void init() {
            const i32 n = 2000;
            fact[0] = ifact[0] = 1;
            for (i32 i = 1; i <= n; ++i)
                fact[i] = fact[i - 1] * i % mod;
            ifact[n] = inv(fact[n], mod);
            for (i32 i = n - 1; i; --i)
                ifact[i] = ifact[i + 1] * (i + 1) % mod;
        }

        i64 getC(i32 a, i32 b) {
            if (a < b)
                return 0;
            else
                return fact[a] * ifact[b] % mod * ifact[a - b] % mod;
        }
    }  // namespace mat

    i32 s[N], n, m;

    i64 g(i64 i) {
        i64 res = 1;
        for (i32 j = 1; j <= m; ++j)
            res = res * mat::getC(s[j] + n - i - 1, n - i - 1) % mod;
        res = res * mat::getC(n, i) % mod;
        return res;
    }

    void main() {
        cin >> n >> m;
        for (i32 i = 1; i <= m; ++i)
            cin >> s[i];
        mat::init();
        i64 ans = 0;
        for (i32 j = 0; j < n; ++j)
            (ans += g(j) * ((j & 1) ? -1 : 1)) %= mod;
        cout << (ans % mod + mod) % mod;
    }
}  // namespace tkgs

int main() {
    tkgs::main();
    return 0;
}