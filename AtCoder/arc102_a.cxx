#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

u64 n, k;
u64 cnt1, cnt2;
u64 ans;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    for (u32 i = k; i <= n; ++i)
        if (i % k == 0) ++cnt1;
    ans += cnt1 * cnt1 * cnt1;
    if (!(k & 1)) {
        for (u32 i = k >> 1; i <= n; ++i)
            if (i % k == k >> 1) ++cnt2;
        ans += cnt2 * cnt2 * cnt2;
    }
    cout << ans;
    return 0;
}