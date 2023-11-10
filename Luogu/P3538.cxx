#include <bitset>
#include <cmath>
#include <iostream>
#include <string>

using std::cin;
using std::cout;

using u32 = unsigned int;
using u64 = unsigned long long;

constexpr u64 base = 53;
constexpr u64 mod = 1610612741;

#define N 500005

u64 basis[N];
u64 prehash[N];

std::string s;
u32 q;

u64 hash(u32 l, u32 r) {
    return prehash[r] - prehash[l - 1] * basis[r - l + 1];
}

std::bitset<N> npr;

u64 pri[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> q >> s;

    const u32& n = q;

    // init string hash
    s = '$' + s;
    basis[0] = 1;
    for (u32 i = 1; i <= n; ++i) {
        basis[i] = basis[i - 1] * base;
        prehash[i] = prehash[i - 1] * base + s[i] - 'a' + 1;
    }

    constexpr u64 mxn = 5e5;

    for (u32 i = 2, lim = mxn; i <= lim; ++i) {
        if (!npr[i]) {

            pri[i] = i;
            // if (i == 3853) return (std::cerr << "pri=" << pri[i]), 1;
            for (u32 j = i * i; j <= mxn; j += i) {
                npr[j] = true;
                if (!pri[j]) pri[j] = i;
            }
        }
    }
    cin >> q;

    // for (u32 i = 1; i <= 100; ++i)
    //     cout << pri[i] << ' ';

    do {
        u32 l, r;
        cin >> l >> r;
        u32 len = r - l + 1;
        u32 ans = len;

        if (hash(l, r - 1) == hash(l + 1, r))
            cout << "1\n";
        else {
            while (len > 1) {
                if (hash(l, r - ans / pri[len]) == hash(l + ans / pri[len], r)) ans /= pri[len];
                len /= pri[len];
            }
            cout << ans << '\n';
        }
    } while (--q);

    // std::cerr << (hash(3, 5) == hash(6, 8));

    return 0;
}