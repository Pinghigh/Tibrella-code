#include <iostream>
#include <algorithm>
#define MAXN 1010

using namespace std;

int n, m;
int v[MAXN], w[MAXN];
int f[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        cin >> v[i] >> w[i];
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            f[i][j] = f[i - 1][j];
            if (j >= v[i]) f[i][j] = max(f[i][j],f[i-1][j-v[i]] + w[i]);
        }
    }
    
    cout << f[n][m];  
    
    return 0;
}