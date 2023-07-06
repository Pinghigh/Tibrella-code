#include <algorithm>
#include <bitset>
#include <iostream>

#define int long long

#define N 25

using namespace std;

bitset<N> q[N];
int f[N][N];

signed main() {
    signed n, m, a, b;
    cin >> n >> m >> a >> b;

    n++;
    m++;
    a++;
    b++;
    q[a][b] = 1;
    q[max(a - 1, 0)][b + 2] = 1;
    q[max(a - 1, 0)][max(b - 2, 0)] = 1;
    q[a + 1][b + 2] = 1;
    q[a + 1][max(b - 2, 0)] = 1;
    q[max(a - 2, 0)][b + 1] = 1;
    q[max(a - 2, 0)][max(b - 1, 0)] = 1;
    q[a + 2][b + 1] = 1;
    q[a + 2][max(b - 1, 0)] = 1;

    f[0][1] = 1;
    /*
        for (int i = 0; i <= n; i ++) {
            for (int j = 0; j <= m; j ++) {
                cout << q[i][j] << ' ';
            }
            cout << endl;
        }
    */
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!q[i][j]) f[i][j] = f[i - 1][j] + f[i][j - 1];
        }
    }

    cout << f[n][m];

    return 0;
}