#include <iostream>
#include <algorithm>
#include <queue>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

i32 n;

#define N 200005

struct p {
    i32 a, b;
} a[N];

std::priority_queue<i32, std::vector<i32>, std::greater<i32>> q;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++ i) cin >> a[i].a >> a[i].b;
    i64 tot = 0, m = 0;
    for (i32 i = 1; i <= n; ++ i) tot+=a[i].b;

    std::sort(a+1, a+n+1, [](const p&a, const p&b) {return a.a>b.a;});
    i64 tmp = 0;
    for (i32 i = 1; i <= n; ++ i) {
        tmp+=a[i].b;
        q.push(a[i].b);
        if (a[i].a>n-q.size()) {
            tmp -= q.top();
            q.pop();
        }
        m = std::max(tmp, m);
    }

    cout << tot-m;

    return 0;
}