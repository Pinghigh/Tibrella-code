#include <iostream>
#include <queue>

using namespace std;

using i64 = long long;

int main() {
    priority_queue<i64, vector<i64>, greater<i64>> q;
    i64 n;
    cin >> n;
    i64 ans = 0, x;
    while (n--) {
        cin >> x;
        q.push(x);
        ans += x - q.top();
        q.pop();
        q.push(x);
    }
    cout << ans;
    return 0;
}