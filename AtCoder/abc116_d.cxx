#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

#define N 100005

using i32 = int;
using i64 = long long;

struct sus {
    i32 t;
    i64 d;

    void read() {
        cin >> t >> d;
    }
} sushi[N];

i32 n, k;

#include <bitset>

std::bitset<N> vis, ch;
i32 tt, it;
i64 ans;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        sushi[i].read();
    }
    std::sort(sushi + 1, sushi + n + 1, [](const sus& a, const sus& b) { return a.d > b.d; });

    i64 res = 0;

    for (int i = 1; i <= k; ++i) {
        res += sushi[i].d;
    }
    it = 1;
    for (i64 i = 1; i <= n; ++i) {
        while (vis[sushi[it].t] && it <= n)
            ++it;
        if (it > n) break;
        vis[sushi[it].t] = ch[it] = true;
        if (k < it) {
            while (ch[k] && k)
                --k;
            if (!k) break;
            res += sushi[it++].d - sushi[k--].d;
        }
        ans = std::max(ans, res + i * i);
    }
    cout << ans;

    return 0;
}