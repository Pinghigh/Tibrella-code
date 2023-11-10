#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 5001

i32 a[N];

i32 solve(const i32& l, const i32& r) {
    if (l > r) return 0;
    else if (l == r) return std::min(a[l], 1);
    i32 mid = 0, mn = 1e9+7;
    for (i32 i = l; i <= r; ++i) 
        if (a[i] < mn) mn = a[mid = i];
    for (i32 i = l; i <= r; ++i) a[i] -= mn;
    return std::min(r-l+1, solve(l, mid-1) + mn + solve(mid+1, r));
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    for (i32 i = 1; i <= n; ++i) cin >> a[i];

    cout << std::min(n, solve(1, n));

    return 0;
}