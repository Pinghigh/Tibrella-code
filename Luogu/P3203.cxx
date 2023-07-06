#include <cmath>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;

#define N 200005

i32 n, m;
i32 k[N];     // 弹力系数
i32 step[N];  // 跳出当前块所需步数
i32 to[N];    // 跳出当前块之后到哪里了
i32 bel[N];   // 属于哪个块

i32 blk_siz, blk_cnt;

void init() {
    blk_siz = sqrt(n);

    // 预处理端点属于哪个块
    blk_cnt = 1;
    for (i32 i = 0, cnt = 1; i < n; ++i, ++cnt) {
        if (cnt > blk_siz) cnt = 1, ++blk_cnt;
        bel[i] = blk_cnt;
    }

    // 预处理 step 和 to
    for (i32 i = n - 1; ~i; --i) {
        if (bel[i + k[i]] != bel[i])
            step[i] = 1, to[i] = i + k[i];
        else
            step[i] = step[i + k[i]] + 1, to[i] = to[i + k[i]];
    }
}

void modify(i32 pos, i32 val) {
    k[pos] = val;
    // 块内暴力重构，反正都是根号
    for (i32 i = std::min(n - 1, bel[pos] * blk_siz - 1); ~i && bel[i] == bel[pos]; --i) {
        if (bel[i + k[i]] != bel[i])
            step[i] = 1, to[i] = i + k[i];
        else
            step[i] = step[i + k[i]] + 1, to[i] = to[i + k[i]];
        // cout << to[i] << ' ';
    }
    // cout << '\n';
}

i32 query(i32 pos) {
    i32 res = 0;
    while (pos < n) {
        res += step[pos];
        // cout << step[pos] << ' ';
        pos = to[pos];
    }
    // cout << '\n';
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    for (i32 i = 0; i < n; ++i)
        cin >> k[i];

    init();

    cin >> m;

    i32 op, x, y;

    while (m--) {
        cin >> op >> x;
        --op;
        if (op) {
            cin >> y;
            modify(x, y);
        } else
            cout << query(x) << '\n';
    }

    // for (i32 i = 0; i < n; ++i)
    //     cout << step[i] << ' ';

    // cout << bel[2] << ' ' << bel[2+k[2]];

    return 0;
}