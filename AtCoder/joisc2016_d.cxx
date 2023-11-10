#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

using u64 = unsigned long long;
std::vector<i32> lsh; // 离散化

template <typename T, i64 SIZ>
class BIT {
private:
    T a[SIZ];
public:
    i64 n;
    void set_n(i64 xn) {
        n = xn;
    }

    inline i64 lowbit(const i64& x) {
        return x & -x;
    }

    void add(const T& x, i64 pos) {
        pos = n - pos + 1;
        while (pos <= n) {
            a[pos] += x;
            pos += lowbit(pos);
        }
    }

    T query(i64 pos) {
        pos = n - pos + 1;
        T x = 0;
        while (pos) {
            x += a[pos];
            pos -= lowbit(pos);
        }
        return x;
    }
};

#define N 400005

BIT<i64, N> tree;

i32 x;

i32 a[N];
i32 op[N], q[N], y[N];



int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, m;
    cin >> n >> m;
    for (i32 i = 1; i <= n; ++ i) {
        cin >> a[i];
        lsh.emplace_back(a[i]);
    }
    for (i32 i = 1; i <= m; ++ i) {
        cin >> op[i] >> q[i];
        if (op[i] == 2) {
            cin >> y[i];
            lsh.emplace_back(y[i]);
        } else lsh.emplace_back(q[i]);
    }
    
    /* 离散化 */
    lsh.emplace_back(0);
    std::sort(lsh.begin(),lsh.end());
    lsh.erase(std::unique(lsh.begin(),lsh.end()),lsh.end());
    for (i32 i = 1; i <= n; ++ i) 
        a[i] = std::lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin();
    for (i32 i = 1; i <= m; ++ i) {
        if (op[i] == 1) q[i] = std::lower_bound(lsh.begin(), lsh.end(), q[i]) - lsh.begin();
        else y[i] = std::lower_bound(lsh.begin(), lsh.end(), y[i]) - lsh.begin();
    }
    tree.set_n(lsh.size());



    /* 预处理 */
    for (i32 i = 0; i <= n; ++ i) tree.add(1, std::max(a[i], a[i+1])), tree.add(-1, std::min(a[i], a[i+1]));

    /* solve */
    for (i32 i = 1; i <= m; ++ i) {
        const i32 &op = ::op[i], &x = ::q[i], &y = ::y[i];
        // cout << op << ' ' << lsh[x] << ' ' << lsh[y] << '\n';
        if (op == 1) cout << (tree.query(x) >> 1) << '\n';
        else {
            // cout << "x " << lsh[a[x]] << '\n';
            // revert changes
            tree.add(-1, std::max(a[x], a[x+1])), tree.add(1, std::min(a[x], a[x+1]));
            tree.add(-1, std::max(a[x], a[x-1])), tree.add(1, std::min(a[x], a[x-1]));
        
            // apply new changes
            a[x] = y;
            tree.add(1, std::max(a[x], a[x+1])), tree.add(-1, std::min(a[x], a[x+1]));
            tree.add(1, std::max(a[x], a[x-1])), tree.add(-1, std::min(a[x], a[x-1]));
        }
    }

    // cout << '\n';
    // for (auto& x : lsh) cout << x << ' ';


    return 0;
}