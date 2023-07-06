#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::min;

using i32 = int;

#define N 1005

i32 n;
struct tas {
    i32 id;
    i32 a, b;
    i32 d;
} task[N];
i32 f1, f2;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> task[i].a;
        task[i].id = i;
    }
    for (int i = 1; i <= n; ++i) {
        cin >> task[i].b;
        task[i].d = task[i].a - task[i].b;
    }
    std::sort(task + 1, task + n + 1, [](tas& a, tas& b) { return min(a.b, b.a) > min(a.a, b.b); });
    for (int i = 1; i <= n; ++i) {
        f1 += task[i].a;
        f2 = std::max(f1, f2) + task[i].b;
    }
    cout << f2 << '\n';
    for (int i = 1; i <= n; ++i)
        cout << task[i].id << ' ';

    return 0;
}