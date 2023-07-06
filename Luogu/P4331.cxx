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

#define N 1000006
i32 a[N], b[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> t1;
        t1 -= i;
        a[i] = t1;
        q.push(t1);
        if (!q.empty() && q.top() > t1) {
            q.pop();
            q.push(t1);
        }
        b[i] = q.top();
    }
    for (i32 i = n - 1; i; --i)
        b[i] = std::min(b[i], b[i + 1]);
    for (i32 i = 1; i <= n; ++i)
        ans += abs(a[i] - b[i]);

    cout << ans << '\n';
    for (i32 i = 1; i <= n; ++i)
        cout << b[i] + i << ' ';

    return 0;
}