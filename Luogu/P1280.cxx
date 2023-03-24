#include <iostream>

using namespace std;

#define MAXN 10010
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

int u[MAXN],v[MAXN],ne[MAXN],fir[MAXN],idx;
int n,k,p,t;
int dp[MAXN];
int tmpMax;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> k;
    for (int i = 1; i <= k; i ++) {
        cin >> p >> t;
        idx ++;
        u[idx] = p;
        v[idx] = t;
        ne[idx] = fir[p];
        fir[p] = idx;
    }

    for (int i = n; i > 0; i --) {
        if (fir[i]) {
            idx = fir[i];
            tmpMax = -114514;
            while (idx) {
                tmpMax = max(tmpMax,dp[i+v[idx]]);
                //cout << "idx:" << idx << " tmpMax=" << tmpMax << " i=" << i << endl;
                idx = ne[idx];
            }
            dp[i] = tmpMax;
        } else {
            dp[i] = dp[i+1] + 1;
        }
    }
    cout << dp[1] << endl;

    return 0;
}
