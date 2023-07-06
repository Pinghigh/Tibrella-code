#include <iostream>

using std::cin;
using std::cout;

#define max(a, b) ((a) > (b)) ? (a) : (b)
#define N 114514

int n, res, tmp;
int a;
int dp[32];

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    res = -114514;
    while (n--) {
        cin >> a;
        tmp = -114514;

        for (int j = 0; j < 32; j++) {
            if ((1 << j) & a) {
                tmp = max(tmp, dp[j] + 1);
            }
        }
        for (int j = 0; j < 32; j++) {
            if ((1 << j) & a) {
                dp[j] = max(dp[j], tmp);
            }
        }
        res = max(tmp, res);
    }

    cout << res;

    return 0;
}
