#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

#define N 5000006

using i32 = int;

i32 n, m, a[N];
i32 tree[N];

inline i32 lowbit(i32 x) {
    return x & -x;
}

inline void mod(i32 pos, i32 v) {
    for (int i = pos; i <= n; i += lowbit(i))
        tree[i] += v;
}

inline i32 query(i32 pos) {
    i32 res = 0;
    for (int i = pos; i; i -= lowbit(i))
        res += tree[i];
    return res;
}

void modify(i32 l, i32 r, i32 v) {
    mod(l, v);
    mod(r + 1, -v);
}

i32 t1, t2, t3;
i32 op;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        cin >> op;
        if (op == 2) {
            cin >> t1 >> t2 >> t3;
            modify(t1, t2, t3);
        } else if (op == 3) {
            cin >> t1;
            cout << query(t1) << '\n';
        }
    }

    return 0;
}