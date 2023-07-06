    #include <iostream>

    using std::cin;
    using std::cout;

    using i32 = int;
    using i64 = long long;

    inline i64 lowbit(i64 x) {
        return x & -x;
    }

    #define N 100005

    i64 id[N], d[N];

    i32 n, m;
    i32 t1, t2, t3, op;

    void mod(i32 pos, i64 val) {
        for (i32 i = pos; i <= n; i += lowbit(i)) {
            id[i] += pos * val;
            d[i] += val;
        }
    }

    i64 que(i32 pos) {
        i64 res = 0;
        for (i32 i = pos; i; i -= lowbit(i)) {
            res += d[i] * (pos + 1) - id[i];
        }
        return res;
    }

    void modify(i32 l, i32 r, i64 val) {
        mod(l, val);
        mod(r + 1, -val);
    }

    i64 query(i32 l, i32 r) {
        return que(r) - que(l - 1);
    }

    int main() {
        std::ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        cin >> n >> m;
        for (i32 i = 1; i <= n; ++i) {
            cin >> t1;
            modify(i, i, t1);
        }
        while (m--) {
            cin >> op;
            if (op == 1) {
                cin >> t1 >> t2 >> t3;
                modify(t1, t2, t3);
            } else {
                cin >> t1 >> t2;
                cout << query(t1, t2) << '\n';
            }
        }

        return 0;
    }