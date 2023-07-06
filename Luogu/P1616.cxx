#include <iostream>
#include <algorithm>
#define T 10000010
#define N 11451

using namespace std;

long long int t,m,med[N][2],f[T];
// 0->time 1->value
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t >> m;
    for (int i = 1; i <= m; i ++) {
        cin >> med[i][0] >> med[i][1];
    }

    for (int i = 1; i <= m; i ++) {
        for (int j = med[i][0]; j <= t; j ++) {
            f[j] = max(f[j],f[j-med[i][0]]+med[i][1]);
        }
    }

    cout << f[t];

    return 0;
}