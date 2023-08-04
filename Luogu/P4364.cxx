#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;
using f64 = double;

#define N 500005

i32 n;
f64 k;

i32 d[N], ans[N];
std::vector<i32> e[N];
i32 it;

void solve(i32 nod) {
    for (auto& to : e[nod])
        solve(to);
    ans[nod] = d[++it];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    for (i32 i = 1; i <= n; ++i)
        cin >> d[i];
    std::sort(d + 1, d + n + 1, std::greater<i32>());

    for (i32 i = 1; i <= n; ++i)
        e[(i32)(i / k)].emplace_back(i);

    solve(0);

    for (i32 i = 1; i <= n; ++i)
        cout << ans[i] << ' ';

    return 0;
}