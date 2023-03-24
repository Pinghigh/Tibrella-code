#include <array>
#include <cstring>
#include <iostream>
#include <set>

using namespace std;

#define N 500010
#define MOD 80112002

int u[N], v[N], fir[N], nex[N];  // 存图
int in[N];                       // 统计入度
int idx, nNow, nNex;
int n, m;
int ans;
int f[N];
set<int> topo;

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    memset(fir, -1, sizeof fir);
    // memset(in,127,sizeof in);

    cin >> n >> m;

    while (m--) {
        cin >> nNow >> nNex;
        u[++idx] = nNow;
        v[idx] = nNex;
        nex[idx] = fir[nNow];
        fir[nNow] = idx;
        in[nNex]++;
    }

    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            topo.insert(i);
            f[i] = 1;
        }
    }

    int nidx = 0;
    while (!topo.empty()) {
        nidx = *topo.begin();
        topo.erase(topo.begin());
        for (int i = fir[nidx]; ~i; i = nex[i]) {
            f[v[i]] += f[u[i]];
            // printf("[ADD] %d to node[%d]; %d now\n", f[u[i]], v[i], f[v[i]]);
            f[v[i]] %= MOD;
            --in[v[i]];
            if (!(in[v[i]])) {
                // printf("[INS] NODE %d\n", v[i]);
                topo.insert(v[i]);
            }
        }
        if (!~fir[nidx]) {
            ans += f[nidx];
            // printf("[RES] ADD %d from node[%d] \n", f[nidx], nidx);
        }
    }

    ans %= MOD;
    cout << ans << endl;

    return 0;
}