#include <iostream>
#include <set>
#include <bitset>

using std::cin;
using std::cout;

#define N 200005

using i32 = int;
using i64 = long long;

#define LG 30

i32 a[N];
i32 bpos[LG][N];
i32 pos[N];

i32 log2(const i32& x) {
    return sizeof(i32) * __CHAR_BIT__ - __builtin_clz(x) - 1;
}

std::bitset<N> st, ans;
i32 b[N];
std::set<i32> s;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    i32 mx = 0, cnt = n;
    for (i32 i = 1; i <= n; ++ i) {cin >> bpos[0][i]; pos[i]=i;if (!st[bpos[0][i]]) st[bpos[0][i]] = true, --cnt;}
    for (i32 i = 1; i <= n; ++ i) {cin >> a[i]; mx = std::max(mx, a[i]); b[i] = 0x3f3f3f3f;}

    if (cnt != 0) {
        cnt = (mx - n) / cnt;

        for (i32 i = 1, lim = log2(cnt); i <= lim; ++ i) 
            for (i32 j = 1; j <= n; ++ j)
                bpos[i][j] = bpos[i-1][bpos[i-1][j]];
        
        for (i32 i = 0, lim = log2(cnt); i <= lim; ++ i) 
            if (cnt & (1<<i))
                for (i32 j = 1; j <= n; ++ j)
                    pos[j] = bpos[i][pos[j]];
    }
    for (i32 i = 1; i <= n; ++ i) b[i] = std::min(b[i], a[pos[i]]);
 
    for (i32 i = 1; i <= n; ++ i) ans[b[i]] = true;

    for (i32 i = 1; i <= n; ++ i) if (!ans[i]) s.emplace(i);

    for (i32 i = 1; i <= n; ++ i)
        if (ans[b[i]]) ans[b[i]] = false;
        else {
            auto t = s.lower_bound(b[i]);
            b[i] = *t;
            s.erase(t);
        }

    for (i32 i = 1; i <= n; ++ i) cout << b[i] << ' ';

    return 0;
}