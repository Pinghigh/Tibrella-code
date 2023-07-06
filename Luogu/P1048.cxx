#include <iostream>
#include <algorithm>

#define N 1145

using namespace std;

int v[N],t[N],n,m,f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        cin >> t[i] >> v[i];
    }

    for (int i = 1; i <= m; i ++) {
        for (int j = n; j >= t[i]; j --) {
            f[j] = max(f[j],f[j-t[i]] + v[i]);
        }
    }

    cout << f[n];

    return 0;
}