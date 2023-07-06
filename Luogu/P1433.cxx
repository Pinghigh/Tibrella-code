#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;

const char endl = '\n';
const int N = 16;
constexpr int ST = 1 << N;

template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

#define count(num) __builtin_popcount(num)
#define get_dis(n1, n2) sqrt((x[n1] - x[n2]) * (x[n1] - x[n2]) + (y[n1] - y[n2]) * (y[n1] - y[n2]))

int n;
double f[N][ST];
double dis[N][N];
double x[N], y[N];
int suc;

int main() {
    memset(f, 0x42, sizeof f);
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
    }

    suc = (1 << n) - 1;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dis[i][j] = get_dis(i, j);
        }
    }

    for (int i = 1; i <= n; ++i) {
        f[i][1 << i - 1] = dis[0][i];
    }
for (int s = 0; s <= 1 << n; ++s)
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i ^ j)
                 {
                    int fix = 1 << j - 1;
                    if (!(s & fix)) {
                        f[j][s | fix] = min(f[j][s | fix], f[i][s] + dis[i][j]);
                    }
                }
        }
    }
    

    double ans = 0xffffffff;
    for (int i = 0; i <= n; ++i) {
        ans = min(ans, f[i][suc]);
    }   
    cout << std::fixed << std::setprecision(2) << ans;

    // for (int i = 0; i <= 1<<n+1; ++ i) {
    //     cout << f[n+1][i] << endl;
    // }

    // for (int i = 0; i <= n; i ++)
    // {
    //     for (int j = 0; j < (1 << n); j ++)
    //         cerr << f[i][j] << " ";
    //     cerr << endl;
    // }

    return 0;
}
