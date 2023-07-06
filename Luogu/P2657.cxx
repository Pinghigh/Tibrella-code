#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

#define N 15
#define endl '\n'

int a, b;
int f[N][N];
int sta[N];
int pos;

template <typename Type>
Type abs(Type __num) {
    return __num > 0 ? __num : -__num;
}

int dfs(int now, int prev, bool all_zero, bool limit) {
    if (!now) return 1;
    if (~f[now][prev] && !limit) return f[now][prev];

    int max_num = limit ? sta[now] : 9;
    int res = 0;

    for (int i = 0; i <= max_num; ++i) {
        if (abs(i - prev) < 2) {
            continue;
        }
        if (all_zero && !i)
            res += dfs(now - 1, -2, 1, limit && i == max_num);
        else
            res += dfs(now - 1, i, 0, limit && i == max_num);
    }
    if (!limit && !all_zero) f[now][prev] = res;
    return res;
}

int solve(int num) {
    pos = 0;
    do {
        sta[++pos] = num % 10;
        num /= 10;
    } while (num);

    return dfs(pos, -2, 1, 1);
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b;
    memset(f, -1, sizeof f);

    cout << solve(b) - solve(a - 1) << endl;

    return 0;
}