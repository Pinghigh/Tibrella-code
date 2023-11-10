#include <iostream>
#include <bitset>

using std::cin;
using std::cout;

#define N 20000001

using i32 = int;
using i64 = long long;
using u32 = unsigned;

#define P 1000001

// constexpr i64 mod = 1ll<<32;

u32 pr[N];
std::bitset<N> is;
u32 idx;
u32  a[N];

u32 seed;
static inline u32 getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    u32 n;
    cin >> n >> seed;
    for (u32 i = 1; i <= n; ++ i) a[i] = getnext();
    
    for (u32 i = 2; i <= n; ++ i) {
        if (!is[i]) pr[++idx] = i;
        for (u32 j = 1; j <= idx && pr[j] * i <= n; ++ j) {
            is[pr[j] * i] = true;
            if (i % pr[j] == 0) break;
        }
    }

    u32 ans = 0;
    for (u32 i = 1; i <= idx; ++ i) 
        for (u32 j = 1; pr[i] * j <= n; ++ j) a[pr[i]*j] += a[j];
    
    for (u32 i = 1; i <= n; ++ i) ans ^= a[i];

    cout << ans;
    rand();

    return 0;
}
