#include <iostream>
#include <algorithm>
#include <unordered_set>

using std::cin;
using std::cout;

#define N 200001

using i32 = int;
using i64 = long long;

std::unordered_set<i32> s[N];
i32 cnt[N];
i32 ans[N];

i32 n, m;

char op;
i32 x, y;     

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i32 i = 1; i <= m; ++ i) {
        cin >> op >> x;
        if (op == '!') {
            ++cnt[x];
        } else {
            cin >> y;
            if (op == '+') s[x].emplace(y), s[y].emplace(x), ans[x] -= cnt[y], ans[y] -= cnt[x];
            else s[x].erase(y), s[y].erase(x), ans[x] += cnt[y], ans[y] += cnt[x];
        }
    }
    
    for (i32 i = 1; i <= n; ++ i) {
        while (!s[i].empty()) {
            ans[i] += cnt[*s[i].begin()];
            s[i].erase(s[i].begin());
        }
        cout << ans[i] << ' ';
    }

    return 0;
}