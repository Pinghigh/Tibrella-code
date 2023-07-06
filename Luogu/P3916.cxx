#include <iostream>


using namespace std;

#define N 11451

int u[N], v[N], fir[N], nex[N];
int f[N];
int m,n;
int nNow, nNex;
int idx;

void dfs(int node) {

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; ++ i) {
        cin >> nNow >> nNex;
        v[++idx] = nNow;
        u[idx] = nNex;
        nex[idx] = fir[nNex];
        fir[nNex] = idx;
    } // 反向建边

    dfs(n);

    return 0;
}