#pragma GCC optimize("O2,unroll-loops,inline")
#pragma GCC target("avx2,fma,bmi,bmi2,lzcnt,popcnt,tune=native")

#include <iostream>
#include <unordered_map>
#include <chrono>
#include <random>

using std::cin;
using std::cout;

using i32 = long long int;
using i64 = long long;

constexpr i32 mod = 1e9 + 7;

struct my_hash {
    static uint64_t splitmix64(uint64_t x) {
        unsigned ov = x;
        x = x + 12453167u; // LCG
        ov = ((ov >> ((ov >> 28u) + 4u)) ^ ov) ^ 3277803737u;  // 映射
        return (ov >> 22u) ^ ov; // 映射
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            75645418741891ull;
        return splitmix64(x + FIXED_RANDOM);
    }
};

std::unordered_map<i32, i32> f;

#define N 200005

i32 b[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 t;
    cin >> t;

    i32 n = 0;
    while (t--) {
        // memset(b + 1, 0, n * sizeof(i32));
        cin >> n;
        for (i32 i = 1; i <= n; ++ i) cin >> b[i];
        f.clear();

        i32 ans = f[0] = 1, delta = 0;
        for (i32 i = 1; i <= n; ++ i) {
            delta += b[i];
            i32 add = (ans - f[b[i] - delta] + mod) % mod;
            f[b[i] - delta] = ans;
            ans = (ans + add) % mod;
        }
        cout << ans << '\n';
    } 
    return 0;
}