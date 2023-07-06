#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 100005

i64 t;
i64 n, x;
std::queue<i64> q[4];
i64 t1;

void solve() {
    cin >> n >> x;
    for (i32 i = 1; i < 4; ++i) {
        q[i] = std::queue<i64>();

        for (i32 j = 1; j <= n; ++j) {
            cin >> t1;
            q[i].emplace(t1);
        }
    }
    i64 tmp = 0;
    for (i32 i = 1; i <= n; ++i) {
        bool seen = false;
        for (i32 j = 1; j < 4; ++j) {
            if (q[j].empty()) continue;
            i32 now = q[j].front();
            if (((now ^ x) | now) ^ x) continue;
            tmp |= now;
            seen = true;
            q[j].pop();
        }
        if (!seen) break;
    }
    if (tmp == x)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--)
        solve();

    return 0;
}