#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::lower_bound;

using i32 = int;
using i64 = long long;

const i32 inf = 0x3f3f3f3f;

#define N 100005
#define K 1003

i32 n, m;
i32 a[N], b[N];  // 原数列与可补充

i32 ans[N];

i32 len[N], pre[N], end[N], laspos[N];

std::bitset<N> vis;

i32 emplace(i32 pos, i32 lasval) {  // LIS 的上一个值为 lasval，现在需要在 pos 这个位置填一个数。
    i32 ps = lower_bound(b + 1, b + m + 1, lasval) - b - 1;
    vis[ps] = true;
    ans[pos] = b[ps];
    return b[ps];
}

bool find_not_empty(i32& j, i32& x, i32 l) {
    for (i32 ps = j - 1; ps; --ps) {
        if (~a[ps] && len[ps] == l && a[ps] < x) {
            x = a[ps];
            j = ps;
            return true;
        }
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
        end[i] = inf;
    }
    a[++n] = inf;  // 保证 a[n+1] 一定是 LIS 结尾
    end[n] = inf;
    cin >> m;
    for (i32 i = 1; i <= m; ++i)
        cin >> b[i];

    std::sort(b + 1, b + m + 1);

    for (i32 i = 1; i <= n; ++i) {
        if (~a[i]) {
            i32 j = lower_bound(end + 1, end + n + 1, a[i]) - end - 1;
            len[i] = j + 1;
            pre[i] = laspos[j];
            end[j + 1] = a[i];
            laspos[j + 1] = i;
        } else {
            for (i32 j = n, pos = m; pos; --pos) {
                while (end[j] >= b[pos])
                    --j;
                end[j + 1] = b[pos], laspos[j + 1] = i;
            }
        }
    }

    // cout << len[n];

    // 先把 LIS 的位置填上
    i32 i = len[n], j = n, x = a[n];  // j 是已经填了的位置，当前位置为 pre[j]

    while (i--) {
        if (~a[j]) {
            if (!~a[pre[j]])  // 当前空，上一个位置确定，直接填
                x = emplace(pre[j], a[j]);
            else
                x = a[pre[j]];

            j = pre[j];
        } else {
            /*
                若刚才找到的那位是空的，则当前位有两种情况
                1. [1,j) 能找到一个符合定义的非空位置，即 len[ps]+1=len[j],a[ps]<x
                2. 当前位也为空

                显然这两种情况是互斥的，所以直接按照第一种情况找，即 find_not_empty，找不到则一定是第二种情况
            */

            if (!find_not_empty(j, x, i)) { // len[j] 不一定 == i。
                for (i32 ps = j - 1; ps; --ps) {
                    if (!~a[ps]) {
                        x = emplace(ps, x);
                        j = ps;
                        break;
                    }
                }
            }
        }
    }

    // 刚才只填了 LIS 所包含的 -1,现在用两个指针分别遍历 a b 两个序列然后瞎填数就行
    for (i = 1, j = 1; i < n; ++i) {
        if (!~a[i]) {
            if (ans[i]) continue;  // 如果在 LIS 里，那就已经被填过了
            while (vis[j])
                ++j;
            vis[j] = true;
            ans[i] = b[j];
        } else
            ans[i] = a[i];
    }

    for (i = 1; i < n; ++i)
        cout << ans[i] << ' ';

    return 0;
}