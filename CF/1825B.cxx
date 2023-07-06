#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

#define N 200005
const char endl = '\n';
int mn, mx;
int t, n, m;
int a[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        mn = 0x3f3f3f3f;
        mx = -0x3f3f3f3f;
        cin >> n >> m;
        for (int i = 1, lim = n * m; i <= lim; ++i) {
            cin >> a[i];
        }
        if (n > m) std::swap(n, m);
        std::sort(a + 1, a + n * m + 1);
        cout << max((a[n * m] - a[1]) * n * (m - 1) + (a[n * m] - a[2]) * (n - 1), (a[n * m] - a[1]) * n * (m - 1) + (a[n * m - 1] - a[1]) * (n - 1)) << endl;
    }

    return 0;
}