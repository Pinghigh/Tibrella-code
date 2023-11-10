#include <cstdint>
#include <cstdio>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

#define N 200005
std::vector<i64> sum, min, ssum;

void solve() {
    sum.clear(), min.clear(), ssum.clear();
    i32 n;
    cin >> n;
    i64 fir, sec;
    i64 ans = 0, tmpm = 0;
    if (n == 1) {
        cin >> fir;
        if (fir > 0)
            cout << fir << '\n';
        else
            cout << 0 << '\n';
        return;
    }
    i64 min = 0x3f3f3f3f3f3f3f3f, add = 0, sum = 0;
    do {
        cin >> fir >> sec;
        n -= 2;
        if (fir < 0 && sec > 0 && fir + sec > 0) {
            ::sum.emplace_back(sum += fir + sec);
            ssum.emplace_back(sec);
            ::min.emplace_back(min = std::min(fir + sec, min));
        } else
            break;
    } while (n >= 2);
    if (::sum.size()) {
        ssum.emplace_back(0);
        add = ::sum.back();
        for (i32 i = ::sum.size() - 2; i > -1; --i)
            ssum[i] += ssum[i + 1];
        for (i32 i = 0; i < ::sum.size(); ++i)
            add = std::max(::sum[i] + ssum[i + 1] - ::min[i], add);
    }
    if (!(fir < 0 && sec > 0)) ans += (fir > 0 ? fir : 0) + (sec > 0 ? sec : 0);

    for (i32 i = 1; i <= n; ++i) {
        i32 x;
        cin >> x;
        if (x > 0) ans += x;
    }
    cout << ans + add << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}