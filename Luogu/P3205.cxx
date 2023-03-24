#include <bitset>
#include <climits>
#include <iostream>

using namespace std;

int n;
const int mod = 19650827;
const int N = 1514;
int q[N];
int f[2][N][N]; // f[0] 左 f[1] 右
int r;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> q[i];
        f[1][i][i]= 1; // 此处一个人只有一种方案，所以不用两种状态都初始化为 1
    }
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            r = l + len - 1;
            if (q[l]<q[l+1]) {
                f[0][l][r] += f[0][l+1][r];
            }
            if(q[l]<q[r]) {
                f[0][l][r] += f[1][l+1][r];
            }

            if (q[r]>q[r-1]) {
                f[1][l][r] += f[1][l][r-1];
            }
            if (q[r]>q[l]) {
                f[1][l][r] += f[0][l][r-1];
            }

            f[1][l][r] %= mod;
            f[0][l][r] %= mod;
        }
    }
    cout << (f[1][1][n]+f[0][1][n])%mod << endl;

    return 0;
}