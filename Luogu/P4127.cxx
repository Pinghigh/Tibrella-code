#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

const char endl = '\n';

using i64 = long long int;
i64 f[20][9 * 20][9 * 20];
int a[64];

i64 mod;

i64 dfs(int bit, i64 sum, i64 div, bool limit) {
    if (!bit && !sum)
        return 0;
    else if (!bit)
        return div == 0 && sum == mod;
    if (!limit && ~f[bit][sum][div]) return f[bit][sum][div];
    int lim = limit ? a[bit] : 9;
    i64 cnt = 0;
    for (int i = 0; i <= lim; ++i) {
        cnt += dfs(bit - 1, sum + i, (div * 10 + i) % mod, limit && i == lim);
    }
    if (!limit) f[bit][sum][div] = cnt;
    return cnt;
}

i64 solve(i64 num) {
    i64 len = 0;
    while (num) {
        a[++len] = num % 10;
        num /= 10;
    }
    i64 res = 0;
    for (mod = 1; mod <= 9 * len; ++mod) {
        memset(f, -1, sizeof f);
        res += dfs(len, 0, 0, 1);
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i64 l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;

    return 0;
}