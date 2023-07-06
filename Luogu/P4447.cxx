#include <iostream>
#include <map>
#include <queue>

using std::cin;
using std::cout;

using i32 = int;

std::map<i32, i32> m;
i32 n, t1;
std::queue<i32> q;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> t1;
        ++m[t1];
    }

    i32 ans = 0x3f3f3f3f;
    while (m.size()) {
        std::map<i32, i32>::iterator i, j;
        i = j = m.begin();
        i32 t = 1;
        if (!(--i->second)) q.push(i->first);
        for (++j; j != m.end() && i->first == j->first - 1 && j->second > i->second; ++i, ++j) {  // i 已经减过了，所以是 j->second 严格大于 i->second
            ++t;
            if (!(--j->second)) q.push(j->first);   
        }
        while (q.size()) {
            m.erase(q.front());
            q.pop();
        }
        if (t < ans) ans = t;
    }

    cout << ans;

    return 0;
}