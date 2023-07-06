#include <bitset>
#include <iostream>

using std::cin;
using std::cout;

using i64 = long long;

#define N 20
#define ST (1 << 19)

const char endl = '\n';

i64 n, m;
i64 num[N];
i64 f[N][ST + 10][2];
std::bitset<N> vis;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    i64 len = 0;
    while (n) {
        num[len++] = n % 10;
        n /= 10;
    }

    f[0][0][0] = 1;
    i64 max_st = (1 << len) - 1;
    for (i64 st = 0; st <= max_st; ++st) {
        vis.reset();
        for (int i = 0; i < len; ++i) {
            if (vis[num[i]] || (1 << i) & st) continue;
            vis[num[i]] = true;
            for (int j = 0; j < m; ++j) {  // 枚举余数
                if (num[i]) f[(j * 10 + num[i]) % m][st | (1 << i)][1] += f[j][st][0];
                f[(j * 10 + num[i]) % m][st | (1 << i)][1] += f[j][st][1];
            }
        }
    }

    cout << f[0][max_st][1] << endl;

    return 0;
}