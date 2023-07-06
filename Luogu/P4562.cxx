#include <bitset>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

#define N 10000007

std::bitset<N> st;

using i32 = int;
using i64 = long long;
using f64 = double;

const int mod = 1e9 + 7;

i64 l, r, k, ans;

i64 init() {
    i32 cnt = 0;
    for (i32 i = l; i <= r; ++i)
        if (!st[i]) {
            ++cnt;
            for (int j = i << 1; j <= r; j += i)
                st[j] = true;
        }
    return cnt;
}

i64 binpow(i64 a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) res = res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> l >> r;
    k = init();

    ans = k;
    for (i32 i = 2; i <= r - l + 2; ++i) {
        ans = ans * i % mod;
    }
    ans = ans * binpow(k + 1, mod - 2) % mod;
    cout << ans;

    return 0;
}