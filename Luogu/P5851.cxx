#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::sort;
using std::endl;
using std::max;
using std::min;

// #define max(a,b) ((a)>(b)?(a):(b))
// #define min(a,b) ((a)>(b)?(b):(a))
#define N 310
constexpr int M = ((N)*(N-1)/2);

struct cow {
    int w;
    int l,r;

    void read() {
        std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
        cin >> w >> l >> r;
    }
} cows[M];

int n,m;
int p[N][N][N];
int f[N][N];
int i,j,k,len;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for (i = 1; i <= m; i ++) {
        cows[i].read();
        for (j = cows[i].l; j <= cows[i].r; ++ j) {
            p[cows[i].l][cows[i].r][j] = cows[i].w;
        }
    }

    for (len = 1; len <= n; ++ len) {
        for (i = 1; i + len - 1 <= n; ++ i) {
            j = i + len - 1;
            for (k = i; k <= j; ++ k) {
                p[i][j][k] = max(max(p[i+1][j][k],p[i][j-1][k]),p[i][j][k]);
            }
        }
    }

    for (len = 1; len <= n; ++ len) {
        for (i = 1; i + len - 1 <= n; ++ i) {
            j = i + len - 1;
            for (k = i; k <= j; ++ k) {
                f[i][j] = max(f[i][j],f[i][k-1]+f[k+1][j]+p[i][j][k]);
            }
        }
    }

    cout << f[1][n];

    return 0;
}