#include <iostream>

using namespace std;

#define N 100514  // koishi, not inm
#define int long long

int T, n, a, b;
int mid, mx;
int res[N];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;

    while (T--) {
        cin >> n >> a >> b;
        mid = n * (n + 1) >> 2;
        mx = (n + (n >> 1) + 1) * n >> 2;
        if (a > mid && b > mid) {
            cout << -1 << endl;
        } else if (a == 0 && b == 0) {
            for (int i = 1; i <= n; ++i) {
                cout << i << ' ';
            }
            cout << endl;
        } else if (a == 0) {
            if (b > mx) {
                cout << -1 << endl;
            } else {
                for (int i = 1; i <= n; ++i) {
                    cout << i << ' ';
                }
                cout << endl;
            }
        } else if (b == 0) {
            if (a > mx) {
                cout << -1 << endl;
            } else {
                for (int i = n; i > 0; --i) {
                    cout << i << ' ';
                }
                cout << endl;
            }
        } else if (a <= mid && b <= mid) {
            for (int i = 1; i <= (n >> 1); ++i) {
                cout << i << ' ' << n - i + 1 << ' ';
            }
            cout << endl;
        } else if () {

        } else {
            cout << -1 << endl;
        }
    }

    return 0;
}