#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 100001

i32 a[N];
i32 stk[N], fir[N], lst[N];

template <typename T>
static inline void chkmax(T& a, const T& b) {if (a < b) a = b;}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
        if (!fir[a[i]]) fir[a[i]] = i;
        lst[a[i]] = i;
    }
    lst[0] = ++n;
    i32 ans = 0;
    for (i32 i = 0, top = 0; i <= n; ++i) {
        if (i == fir[a[i]]) stk[++top] = a[i], chkmax(ans, top);
        if (stk[top] != a[i]) return cout << "-1", 0;
        top -= (i == lst[a[i]]);
    }
    cout << ans-1 << '\n';

    return 0;
}