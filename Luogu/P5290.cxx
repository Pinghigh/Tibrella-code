#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;

#define N 200005

using i64 = long long;
using i32 = int;

i32 n;
i64 p[N];
i32 son[N], nex[N];  // 左儿子右兄弟
i32 t1;
std::vector<i32> buf;
std::priority_queue<i32> q[N];

void merge(i32 x, i32 y) {
    if (q[x].size() < q[y].size()) std::swap(q[x], q[y]);
    while (q[y].size()) {
        buf.emplace_back(std::max(q[x].top(), q[y].top()));
        q[x].pop(), q[y].pop();
    }
    for (auto& i : buf)
        q[x].emplace(i);
    buf.resize(0);
}

void dfs(i32 nod) {
    for (i32 to = son[nod]; to; to = nex[to]) {
        dfs(to);
        merge(nod, to);
    }
    q[nod].emplace(p[nod]);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i)
        cin >> p[i];
    for (i32 i = 2; i <= n; ++i) {
        cin >> t1;
        nex[i] = son[t1];
        son[t1] = i;
    }

    dfs(1);
    i64 ans = 0;
    while (q[1].size()) {
        ans += q[1].top();
        q[1].pop();
    }
    cout << ans;
    return 0;
}