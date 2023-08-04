#include <algorithm>
#include <iostream>
#include <numeric>

using std::cin;
using std::cout;

#define N 100005

using i32 = int;
using i64 = long long;

i64 a[N], d[N];
i32 id[N];
i64 n, z;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> z;
    i64 tmp = z;
    std::iota(id + 1, id + n + 1, 1);
    for (i32 i = 1; i <= n; ++i) {
        cin >> d[i] >> a[i];
        tmp += a[i] - d[i];
        // cout << id[i] << ' ';
    }
    if (tmp <= 0)
        cout << "NIE";
    else {
        std::sort(id + 1, id + n + 1, [](i32& x, i32& y) -> bool {
            if ((a[x] - d[x]) * (a[y] - d[y]) < 0)
                return (a[x] - d[x] > 0);
            else {
                if (a[x] - d[x] > 0)
                    return d[x] < d[y];
                else
                    return a[x] > a[y];
            }
        });
        // cout << d[2] << '\n';
        for (i32 i = 1; i <= n; ++i) {
            z -= d[id[i]];
            if (z <= 0) {
                cout << "NIE";
                return 0;
            }
            z += a[id[i]];
        }

        cout << "TAK\n";
        for (i32 i = 1; i <= n; ++i)
            cout << id[i] << ' ';
    }

    return 0;
}