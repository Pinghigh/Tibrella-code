#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 1000006

i32 sa[N], rk[N << 1], oldrk[N << 1];
i32 cnt[128], id[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    std::string s;
    i32 n;

    cin >> s;
    n = s.size();
    s = '%' + s;
    i32 m = 127;
    for (i32 i = 1; i <= n; ++i)
        ++cnt[rk[i] = s[i]];
    for (i32 i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];
    for (i32 i = n; i; --i)
        sa[cnt[rk[i]]--] = i;

    i32 p, i;
    for (i32 w = 1; m != n; w <<= 1, m = p) {
        // 第二关键字
        for (p = 0, i = n; i > n - w; --i)
            id[++p] = i;
        for (i = 1; i <= n; ++i)
            if (sa[i] > w) id[++p] = sa[i] - w;

        memset(cnt, 0, sizeof(i32) * (m + 1));

        // 第一关键字
        for (i32 i = 1; i <= n; ++i)
            ++cnt[rk[id[i]]];
        for (i32 i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i32 i = n; i; --i)
            sa[cnt[rk[id[i]]]--] = id[i];

        std::swap(rk, oldrk);
        auto cmp = [&](const i32& a, const i32& b) -> bool { return oldrk[a] == oldrk[b] && oldrk[a + w] == oldrk[b + w]; };
        for (p = 0, i = 1; i <= n; ++i)
            rk[sa[i]] = cmp(sa[i], sa[i - 1]) ? p : ++p;
    }

    for (i32 i = 1; i <= n; ++i)
        cout << sa[i] << ' ';

    return 0;
}