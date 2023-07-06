#include <iostream>
#include <queue>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

i32 n;
std::priority_queue<i64> q;
i64 ans;
i64 t1;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> t1;
        t1 -= i;
        q.push(t1);
        if (!q.empty() && q.top() > t1) {
            ans += q.top() - t1;
            q.pop();
            q.push(t1);
        }
    }
    cout << ans;

    return 0;
}