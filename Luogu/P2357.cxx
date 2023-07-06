#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 200005

i32 n, f;

i64 cf[N];   // 差分数组
i64 icf[N];  // i*cf[i]

inline i32 lowbit(i32 x) {
    return x & -x;
}

void mod(i32 pos, i64 val) {
    for (i32 i = pos; i <= n; i += lowbit(i)) {
        icf[i] += val * pos;
        cf[i] += val;
    }
}

i64 que(i32 pos) {
    i64 res = 0;
    for (i32 i = pos; i; i -= lowbit(i)) {
        res += (pos + 1) * cf[i] - icf[i];
    }
    return res;
}

void modify(i32 l, i32 r, i64 val) {
    mod(l, val), mod(r + 1, -val);
}

i64 query(i32 l, i32 r) {
    return que(r) - que(l - 1);
}

i64 t1, t2, t3, t4;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> f;

    for (i32 i = 1; i <= n; ++i) {
        cin >> t1;
        modify(i, i, t1);
    }

    while (f--) {
        cin >> t1;
        if (t1 == 1) {
            cin >> t2 >> t3 >> t4;
            modify(t2, t3, t4);
        } else if (t1 == 2) {
            cin >> t2;
            modify(1, 1, t2);
        } else if (t1 == 3) {
            cin >> t2;
            modify(1, 1, -t2);
        } else if (t1 == 4) {
            cin >> t2 >> t3;
            cout << query(t2, t3) << '\n';
        } else
            cout << que(1) << '\n';
    }

    return 0;
}