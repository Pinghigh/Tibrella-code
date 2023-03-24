#include <iostream>
#include <cstring>

using std::cin;
using std::cout;

#define endl '\n'
#define N 55

template <typename T>
T min(T a, T b) {
    return (a<b?a:b);
}

int n,c;
int f[N][N][2]; // 0 表示左，1 表示右
int w[N];
int pos[N];

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    memset(f,0x3f,sizeof f);

    cin >> n >> c;
    for (int i = 1; i <= n; ++ i) {
        cin >> pos[i] >> w[i];
        w[i] += w[i-1];
    }
    f[c][c][0] = f[c][c][1] = 0;

    for (int i = c; i > 0; -- i) {
        for (int j = i + 1; j <= n; ++ j) {
            f[i][j][0] = min(f[i+1][j][0]+(pos[i+1]-pos[i])*(w[i] + w[n] - w[j]), f[i+1][j][1]+(pos[j]-pos[i])*(w[i] + w[n] - w[j]));
            f[i][j][1] = min(f[i][j-1][1]+(pos[j]-pos[j-1])*(w[i-1] + w[n] - w[j-1]), f[i][j-1][0]+(pos[j]-pos[i])*(w[i-1] + w[n] - w[j-1]));
        }
    }
    cout << min(f[1][n][0], f[1][n][1]) << endl;

    return 0;
}