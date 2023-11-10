#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    i64 ans = 0;
    cin >> n;
    i32 a1, a2, b1, b2;
    std::vector<i64> q;
    while (n--) {
        cin >> a1 >> b1 >> a2 >> b2;
        if (a1 + b1 >= a2 + b2) {
            q.emplace_back(a1 + b1);
            q.emplace_back(a2 + b2);
            ans += a1 + a2;
        } else if (a1 > b2)
            ans += a1 - b2;
        else if (a2 < b1)
            ans += a2 - b1;
    }

    std::sort(q.begin(),q.end());
    bool a = 0;
    for (const auto&x:q) {
        a^=1;
        if (a) ans -= x;
    }

    cout << ans;

    return 0;
}