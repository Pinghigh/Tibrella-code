#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

#define N 1501

using i32 = int;
using i64 = long long;

i32 x[N*N], y[N*N];
i32 xc[N], yc[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    i64 ans = 0;
    for (i32 i = 1; i <= n; ++ i) for (i32 j = 1; j <= n; ++ j) {i32 p; cin >> p; x[p] = i, y[p] = j;}
    for (i32 i = 1; i <= n * n; ++ i) {
        i32 a = xc[x[i]]++, b=yc[y[i]]++;
        ans += a*(n-b-1) + b*(n-a-1);
    }
    cout << (ans >> 1);

    return 0;
}