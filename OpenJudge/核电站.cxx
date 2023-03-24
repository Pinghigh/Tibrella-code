#include <iostream>

using namespace std;

#define N 60
#define M 10
#define min(a,b) ((a)<(b) ? (a):(b))
#define max(a,b) ((a)>(b) ? (a):(b))
#define int long long 

int f[N][M];
int n,m;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    f[0][0] = 1;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 0; j < min(m,i+1); ++ j) {
            f[i][0] += f[i-1][j];
            if (j >= 1) {
                f[i][j] += f[i-1][j-1];
            }
        }
    }   

    int ans = 0;

    for (int i = 0; i < m; ++ i) {
        ans += f[n][i];
    }

    cout << ans;

    return 0;
}
