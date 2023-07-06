#include <bitset>
#include <cstdint>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

const char endl = '\n';

auto max = [](auto a, auto b) { return a > b ? a : b; };

using i64 = int_fast64_t;

#define N 110
#define ST 59074
#define M 20

const i64 p3[] = { 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049 };

i64 f[N][ST];
std::bitset<M> hill[N], st_now;
i64 now[M], pre[M];

i64 n, m;
char ch;
i64 st;
i64 i;
i64 ans;

void unzip(i64 x, i64* a) {
    i64 top = m - 1;
    while (~top) {
        a[top--] = x % 3;
        x /= 3;
    }
}

i64 zip(i64* a) {
    i64 res = 0;
    for (int k = 0; k < m; ++k) {
        res = res * 3 + a[k];
    }
    return res;
}

void dfs(i64 bit, i64 cnt) {
    if (bit == m) {
        i64 sta = zip(now);
        f[i + 1][sta] = max(f[i + 1][sta], cnt + f[i][st]);
        ans = max(f[i + 1][sta], ans);
        return;
    }
    if (!pre[bit]) {                                                                   // 如果上面是 0，说明这个地方可能能放一个炮
        if (now[max(bit - 2, 0)] != 2 && now[max(bit - 1, 0)] != 2 && !st_now[bit]) {  // 保证上方为 0 且左侧两个位置都没炮
            now[bit] = 2;
            dfs(bit + 1, cnt + 1);
        }
        // 也可以不放
        now[bit] = 0;
        dfs(bit + 1, cnt);
    }
    if (pre[bit] == 1) {  // 上面是 1，这个只能为 0
        now[bit] = 0;
        dfs(bit + 1, cnt);
    }
    if (pre[bit] == 2) {  // 上面为 2，这个只能为 1
        now[bit] = 1;
        dfs(bit + 1, cnt);
    }
    now[bit] = 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i = 1; i <= n; ++i) {
        for (i64 j = 0; j < m; ++j) {
            cin >> ch;
            hill[i][j] = (ch == 'H');
        }
    }

    memset(f, -1, sizeof f);
    f[0][0] = 0;
    for (i = 0; i < n; ++i) {
        st_now.reset();
        st_now = hill[i + 1];  // 复制一份地形状况下来
        for (st = 0; st <= p3[m]; ++st) {
            if (~f[i][st]) {  // 如果状态合法
                unzip(st, pre);
                // memset(now, 0, sizeof now);  // 清空当前状态
                dfs(0, 0);
            }
        }
    }

    cout << ans << endl;

    return 0;
}