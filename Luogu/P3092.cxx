#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

using i64 = long long int;

i64 n, k;

#define N 100005
#define K 20
#define ST (1 << 17)

i64 buy[K][N];
i64 f[ST];
i64 coin[K], price[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> k >> n;
    for (int i = 0; i < k; ++i)
        cin >> coin[i];
    for (int j = 1; j <= n; ++j)
        cin >> price[j];

    i64 r, sum;
    for (int i = 0; i < k; ++i) {
        r = 0;
        sum = 0;
        for (int j = 1; j <= n; ++j) {  // 枚举左端点
            while (sum <= coin[i] && r <= n)
                sum += price[++r];
            buy[i][j] = r - 1;
            if (sum) sum -= price[j];  // 有可能啥都买不起
        }
    }

    i64 max_st = (1 << k) - 1;
    for (i64 st = 0; st <= max_st; ++st) {
        if (f[st] >= n) continue;
        for (int i = 0; i < k; ++i) {
            if ((~st) & (1 << i)) {
                f[st | (1 << i)] = max(f[st | (1 << i)], buy[i][f[st] + 1]);
            }
        }
    }

    i64 ans = -1;
    for (i64 st = 0; st <= max_st; ++st) {
        i64 tmp = 0;
        if (f[st] >= n) {
            for (int i = 0; i < k; ++i) {
                if (((~st) & (1 << i))) tmp += coin[i];
            }
            ans = max(tmp, ans);
        }
    }

    cout << ans << std::endl;

    // for (int i = 0; i <= k; ++i) {
    //     for (int j = 1; j <= n + 1; ++j) {
    //         cout << buy[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    return 0;
}