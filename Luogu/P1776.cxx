#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::max;

#define N 105
#define M 100005
#define W 40005

int f[W];
int q[M], hh, tt;
int n, vol, v[N], w[N], m[N];

int calc(int i, int mod, int k) {
    return f[mod + k * w[i]] - k * v[i];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(f, 0xcf, sizeof f);
    f[0] = 0;

    cin >> n >> vol;
    for (int i = 1; i <= n; ++i) {
        cin >> v[i] >> w[i] >> m[i];
        for (int d = 0; d < w[i]; ++d) {  // 枚举 vol mod w[i]，实际上枚举的是 vol
            hh = 1, tt = 0;
            // 最初的可转移的状态集合，其实覆盖整个值域（0~m）
            int mxchs = (vol - d) / w[i];
            for (int j = mxchs - 1; j >= max(mxchs - m[i], 0); --j) {
                while (hh <= tt && calc(i, d, q[tt]) <= calc(i, d, j))
                    --tt;
                q[++tt] = j;
            }
            // 倒序循环每个状态
            for (int c = mxchs; ~c; --c) {
                while (hh <= tt && q[hh] > c - 1)
                    ++hh;
                if (hh <= tt) f[d + c * w[i]] = max(f[d + c * w[i]], calc(i, d, q[hh]) + c * v[i]);
                if (c - m[i] > 0) {
                    while (hh <= tt && calc(i, d, q[tt]) <= calc(i, d, c - m[i] - 1))
                        --tt;
                    q[++tt] = c - m[i] - 1;
                }
            }
        }
    }

    int ans = -114514;
    for (int i = 1; i <= vol; ++i)
        ans = max(f[i], ans);
    cout << ans;

    return 0;
}