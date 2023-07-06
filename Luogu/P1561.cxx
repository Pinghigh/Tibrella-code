#include <algorithm>
#include <iostream>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
using std::cin;
using std::cout;

using i32 = int;

#define N 25000

i32 n;

class cow {
public:
    i32 u, d;

    void read() {
        cin >> u >> d;
    }
} farm[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i)
        farm[i].read();

    std::sort(farm + 1, farm + n + 1, [](const cow& a, const cow& b) {
        if (a.u < a.d) {
            return (b.u >= b.d || a.u < b.u);
        } else {
            return (b.u >= b.d && a.d > b.d);
        }
    });

    i32 f1 = 0, f2 = 0;

    for (i32 i = 1; i <= n; ++i) {
        f1 += farm[i].u;
        f2 = std::max(f1, f2) + farm[i].d;
    }

    cout << f2;

    return 0;
}