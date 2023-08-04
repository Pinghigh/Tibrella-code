#include <bitset>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 50004

i32 n, k;
i64 m;

i64 p[N], c[N];

struct good {
    i32 id;
    i64 val;

    bool operator>(const good& b) const {
        return val > b.val;
    }
};
std::priority_queue<good, std::vector<good>, std::greater<good>> qq, qc, qp;

std::bitset<N> vis;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k >> m;
    for (i32 i = 1; i <= n; ++i) {
        cin >> p[i] >> c[i];
        qc.emplace((good){ i, c[i] });
        qp.emplace((good){ i, p[i] });
    }
    for (i32 i = 1; i <= k; ++i)
        qq.emplace((good){ 0, 0 });

    i64 cost = 0, res = 0;
    while (cost <= m) {
        while (!qc.empty() && vis[qc.top().id])
            qc.pop();
        while (!qp.empty() && vis[qp.top().id])
            qp.pop();
        if (qc.empty() && qp.empty()) {
            break;
        }
        if (!qc.empty() && qp.top().val > qc.top().val + qq.top().val) {
            if (cost + qc.top().val + qq.top().val > m) break;
            ++res;
            cost += qc.top().val + qq.top().val;
            vis[qc.top().id] = true;
            qq.emplace((good){ qc.top().id, p[qc.top().id] - qc.top().val });
            qq.pop(), qc.pop();
        } else {
            if (cost + qp.top().val > m) break;
            ++res;
            cost += qp.top().val;
            vis[qp.top().id] = true;
            qp.pop();
        }
    }
    cout << res;

    return 0;
}