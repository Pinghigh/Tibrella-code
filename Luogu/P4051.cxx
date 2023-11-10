#include <cstring>
#include <iostream>
#include <string>

using std::cin;
using std::cout;

#define N 1000005

using i32 = int;
using i64 = long long;

i32 rk[N << 2], lrk[N << 2], sa[N << 1], tsa[N << 1], key1[N << 1];
i32 cnt[N];

int main() {
    i32 n, m;
    std::string s;
    cin >> s;
    n = s.size() << 1;
    s = '%' + s + s;

    m = 127;
    for (i32 i = 1; i <= n; ++i)
        ++cnt[rk[i] = s[i]];
    for (i32 i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];
    for (i32 i = 1; i <= n; ++i)
        sa[cnt[s[i]]--] = i;

    i32 p;
    for (i32 w = 1; m != n; w <<= 1, m = p) {
        p = 0;
        for (i32 i = n; i > n - w; --i)
            tsa[++p] = i;
        for (i32 i = 1; i <= n; ++i)
            if (sa[i] > w) tsa[++p] = sa[i] - w;

        memset(cnt, 0, (m << 2) + 3);
        for (i32 i = 1; i <= n; ++i)
            ++cnt[key1[i] = rk[tsa[i]]];
        for (i32 i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i32 i = n; i; --i)
            sa[cnt[key1[i]]--] = tsa[i];

        std::swap(lrk, rk);
        static auto cmp = [&](const i32& a, const i32& b) { return lrk[a] == lrk[b] && lrk[a + w] == lrk[b + w]; };
        p = 0;
        for (i32 i = 1; i <= n; ++i)
            rk[sa[i]] = cmp(sa[i], sa[i - 1]) ? p : ++p;
    }
    for (i32 i = 1, lim = n >> 1; i <= n; ++i)
        if (sa[i] <= lim) cout << s[sa[i] + lim - 1];

    return 0;
}