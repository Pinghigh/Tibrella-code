#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

using std::cin;
using std::cout;

using i32 = int;

#define N 20

std::string s[N];
i32 pre[N], pmin[N];

#define PIAN 400001

i32 g[N][PIAN << 1], f[1 << N][2], sm[1 << N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;

    memset(pmin, 0x3f, sizeof pmin);

    for (i32 i = 0; i < n; ++i) {
        cin >> s[i];
        for (i32 j = 1; j <= s[i].size(); ++j) {
            s[i][j - 1] == '(' ? ++pre[i] : --pre[i];
            pmin[i] = std::min(pmin[i], pre[i]);
            if (pmin[i] == pre[i]) ++g[i][PIAN + pre[i]];
        }
    }

    for (i32 i = 1; i < (1 << n); ++i)
        for (i32 j = 0; j < n; ++j)
            if (i & (1 << j)) sm[i] += pre[j];

    for (i32 i = 1; i < (1 << n); ++i)
        f[i][0] = f[i][1] = -0x3f3f3f3f;

    for (i32 S = 0; S < (1 << n); ++S)  // 枚举原集合
        for (i32 i = 0; i < n; ++i) {   // 枚举下一个串
            if (!(S & (1 << i))) {
                i32 SS = S | (1 << i);
                if (sm[S] + pmin[i] >= 0)
                    f[SS][1] = std::max(f[SS][1], f[S][1] + g[i][PIAN - sm[S]]);
                else
                    f[SS][0] = std::max(f[SS][0], f[S][1] + g[i][PIAN - sm[S]]);
            }
        }
    i32 ans = 0;
    for (i32 s = 0; s < (1 << n); ++s)
        ans = std::max(ans, std::max(f[s][0], f[s][1]));

    cout << ans;

    return 0;
}