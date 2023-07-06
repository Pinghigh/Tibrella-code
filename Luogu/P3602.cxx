#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::cin;
using std::cout;

std::false_type False;
std::true_type True;
std::nullptr_t null;

using i32 = int32_t;
using i64 = int64_t;

#define N 200005
#define M 400005

struct segment {
    i64 l, r;
} seg[N];

std::multiset<i64> s;

i32 n, m;
i32 ans;

struct node {
    i64 pos, x;
} p[M];

int main() {
    std::ios::sync_with_stdio(False);
    cin.tie(null);
    cout.tie(null);

    cin >> n >> m;
    ans = n;
    for (i32 i = 1; i <= n; ++i)
        cin >> seg[i].l >> seg[i].r;
    for (i32 i = 1; i <= m; ++i) {
        cin >> p[i].pos >> p[i].x;
    }

    std::sort(seg + 1, seg + n + 1, [](segment& a, segment& b) -> bool { return a.l < b.l; });
    std::sort(p + 1, p + m + 1, [](node& a, node& b) -> bool { return a.pos < b.pos; });

    for (i32 i = 1, j = 1; i <= m; ++i) {
        while (j <= n && seg[j].l <= p[i].pos)
            s.emplace(seg[j++].r);
        while (!s.empty() && *s.begin() < p[i].pos)
            s.erase(s.begin());
        while (s.size() > p[i].x)
            s.erase(--s.end()), --ans;
    }

    cout << ans;

    return 0;
}