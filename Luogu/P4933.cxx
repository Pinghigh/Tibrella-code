#include <iostream>

using std::cin;
using std::cout;

#define N 1145
#define P 40000
#define MAX 66666
#define MOD 998244353

int n, res;
int t[N];
int dp[N][MAX];

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    for (int i = 1; i <= n; i++) {
        res++;
        for (int j = 1; j < i; j++) {
            int k = t[i] - t[j];
            dp[i][k + P] += (dp[j][k + P] + 1);
            dp[i][k + P] %= MOD;
            res += dp[j][k + P] + 1;
            res %= MOD;
        }
    }

    cout << res;

    return 0;
}

