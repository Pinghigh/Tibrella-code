#include <cmath>
#include <iostream>
#include <numeric>

using std::cin;
using std::cout;
using std::iota;

using i8 = char;
using i64 = long long;
using i32 = int;

#define N 500005

i32 n, m;
i64 tree[N], a[N];
i32 pre[N], nxt[N];

inline i32 lowbit(i32 x) {
    return x & -x;
}

void add(i32 pos, i64 x) {
    while (pos <= n) {
        tree[pos] += x;
        pos += lowbit(pos);
    }
}

void modify(i32 pos, i64 x) {
    while (pos <= n) {
        tree[pos] -= x;
        pos += lowbit(pos);
    }
}

i64 q(i32 pos) {
    i64 res = 0;
    while (pos) {
        res += tree[pos];
        pos -= lowbit(pos);
    }
    return res;
}

i64 query(i32 l, i32 r) {
    return q(r) - q(l - 1);
}

void sqrt(i32 l, i32 r) {
    for (i32 i = l; i && i <= r; i = nxt[i]) {
        // if (a[i] <= 1) continue;
        i64 tmp = sqrt(a[i]);
        if (tmp <= 1) nxt[pre[i]] = nxt[i], pre[nxt[i]] = pre[i];  // 下次修改跳过当前点
        modify(i, a[i] - tmp);
        a[i] = tmp;
    }
}

i32 op;
i32 l, r;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    iota(nxt + 1, nxt + n, 2);
    iota(pre + 1, pre + n + 1, 0);
    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
        add(i, a[i]);
        // cout << nxt[i] << ' ';
        // tree[i] = a[i] + tree[i - 1];
    }

    i32 t1;
    cin >> m;
    // m = n;
    while (m--) {
        cin >> op >> l >> r;
        if (l > r) {
            t1 = l;
            l = r;
            r = t1;
        }
        if (op)
            cout << query(l, r) << '\n';
        else
            sqrt(l, r);
    }

    return 0;
}