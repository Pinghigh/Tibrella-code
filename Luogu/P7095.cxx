#include <algorithm>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

#define N 100005

using i32 = long long;
using i64 = long long;

struct dx {
    i32 a, b, c, d;

    void init() {
        cin >> a >> b >> c >> d;
    }
} e[N];

i32 t;
i32 n;
i32 ansa, ansb, tmpa, tmpb;

struct cmp {
    bool operator()(const dx& a, const dx& b) {
        return a.b > b.b || (a.b == b.b && (a.d < b.d || (a.d == b.d && ((a.a > b.a) || (a.a == b.a && (a.c < b.c))))));
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t >> n;

    tmpa = tmpb = ansa = ansb = 0;
    for (i32 i = 1; i <= n; ++i)
        e[i].init();
    std::sort(e + 1, e + n + 1, [](dx& a, dx& b) -> bool { return (a.a < b.a) || (a.a == b.a && (a.c > b.c || ((a.b < b.b || (a.b == b.b && a.d > b.d))))); });
    for (i32 i = 1; i <= n; ++i) {
        while (tmpa < e[i].a)
            ++tmpa, ++ansa;
        tmpa += e[i].c;
    }
    std::priority_queue<dx, std::vector<dx>, cmp> q;
    tmpa = ansa;
    for (i32 i = 1; i <= n; ++i) {  // 满足限制 1 的条件下能不选就不选，就是把必要的选出来，其他扔堆里
        if (tmpa < e[i].a) {
            while (!q.empty() && tmpa < e[i].a) {
                tmpa += q.top().c;
                tmpb += q.top().d;
                q.pop();
            }
            while (tmpb < e[i].b)
                ++tmpb, ++ansb;
            tmpb += e[i].d, tmpa += e[i].c;
        } else
            q.push(e[i]);
    }
    while (!q.empty()) {
        // cout << q.top().b << ' ' << q.top().d << '\n';
        while (tmpb < q.top().b)
            ++tmpb, ++ansb;
        tmpb += q.top().d;
        q.pop();
    }
    cout << ansa << ' ' << ansb << '\n';

    return 0;
}