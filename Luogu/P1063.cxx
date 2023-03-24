#include <iostream>
#include <climits>

using std::cin;
using std::cout;
using std::endl;

#define N 514
#define max(a,b) ((a)>(b)?(a):(b))

struct node {
    int h;
    int t;
} all[N];

int n;
int j;
int ori[N];
int f[N][N];
int res=INT_MIN;


int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        cin >> ori[i];
        ori[i+n] = ori[i];
        all[i].t=ori[i];all[i+1].h=ori[i];all[i+n].t=ori[i];
        all[i+1+n].h=ori[i];
    }
    all[1].h = all[n].t;
    
    // for (int i = 1; i <= 2*n; ++ i) cout << all[i].h << ' ' << all[i].t << endl;
    
    for (int len = 2; len <= n; ++ len) {
        for (int i = 1; i + len - 1 <= 2*n; ++ i) {
            j = i + len - 1;
            f[i][j] = INT_MIN;

            for (int k = i; k < j; ++ k) {
                f[i][j] = max(f[i][j], f[i][k] + f[k+1][j] + all[i].h*all[j].t*ori[k]);
                // cout << f[i][j] << endl;
            }
        }
    }

    for (int i = 1; i <= n; ++ i) {
        res = max(res, f[i][i+n-1]);
    }

    cout << res;

    return 0;
}