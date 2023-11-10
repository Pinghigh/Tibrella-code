#include <iostream>
#include <set>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 2000006

std::set<i32> s[N<<1];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 t;
    cin >> t;
    while (t--) {
        i32 n, m;
        cin >> n >> m;
        for (i32 i = 1; i <= n; ++ i)
            for (i32 j = 1; j <= m; ++ j) {
                char c;
                cin >> c;
                if (c == '1') s[i+j].emplace(i);
            }

        i32 ans = 0;

        for (i32 i = 1; i <= n+m; ++ i) {
            if (s[i+1].empty()) continue;
            i32 x = i;
            ++ans;
            for (i32 y = 1; y <= n; ++ y) {
                s[x+y].erase(y);
                if (s[x+y].size() && *s[x+y].rbegin()>y)--x;
                else ++x;
            }
        }

        cout << ans << '\n';
    }
    return 0;
}