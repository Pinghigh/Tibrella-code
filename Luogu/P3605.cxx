#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 100001

i32 n;
i32 a[N];

i32 lowbit(i32 x) {
    return -x & x;
}

void add(i32 pos, i32 x) {
    while (pos <= n) {
        a[pos] += x;
        pos += lowbit(pos);
    }
}

i32 query(i32 pos) {
    i32 res = 0;
    do
        res += a[pos];
    while (pos -= lowbit(pos));
    return res;
}

i32 son[N], nex[N];

i32 p[N];

#define all(x) x.begin(), x.end()

i32 ans[N];

void dfs(i32 x) {
    ans[x] -= query(p[x] - 1);
    for (i32 to = son[x]; to; to = nex[to])
        dfs(to);
    ans[x] += query(p[x] - 1);
    add(p[x], 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    std::vector<i32> lsh;
    for (i32 i = 1; i <= n; ++i) {
        cin >> p[i];
        lsh.emplace_back(p[i]);
    }
    std::sort(all(lsh), std::greater<i32>());
    lsh.erase(std::unique(all(lsh)), lsh.end());
    for (i32 i = 1; i <= n; ++i)
        p[i] = std::lower_bound(all(lsh), p[i], std::greater<i32>()) - lsh.begin() + 1;

    for (i32 i = 2; i <= n; ++i) {
        i32 x;
        cin >> x;
        nex[i] = son[x];
        son[x] = i;
    }

    dfs(1);

    for (i32 i = 1; i <= n; ++ i) cout << ans[i] << '\n';

    return 0;
}