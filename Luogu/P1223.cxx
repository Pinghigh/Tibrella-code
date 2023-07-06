#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

using i32 = int;
using f64 = double;

#define N 1005

i32 n;
struct p {
    i32 id;
    i32 t;
} peo[N];
f64 sum;
f64 ans;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> peo[i].t;
        peo[i].id = i;
    }
    sort(peo + 1, peo + n + 1, [](p& a, p& b) { return a.t < b.t; });
    for (int i = 1; i <= n; ++i) {
        cout << peo[i].id << ' ';
        ans += sum;
        sum += peo[i].t;
    }
    cout << endl << fixed << setprecision(2) << ans * 1.0 / n;

    return 0;
}