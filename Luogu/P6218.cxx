#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
const char endl = '\n';
using i64 = long long;

i64 l, r;
i64 num;

i64 f[32][70];

i64 dfs(i64 bit, i64 cha, bool is_zero, bool limit) {
    if (!~bit) return cha >= 30;  // 如果 cnt(0) - cnt(1) >= 0 则是一个合法的数
    if (!is_zero && !limit && ~f[bit][cha]) return f[bit][cha];
    i64 res = 0;
    for (i64 i = 0; i <= (limit ? (num >> bit) & 1 : 1); ++i) {
        res += dfs(bit - 1, cha + (!i ? (is_zero ? 0 : 1) : -1), !i && is_zero, limit && (limit ? (num >> bit) & 1 : 1) == i);
    }
    if (!is_zero && !limit) f[bit][cha] = res;
    return res;
}

i64 solve(i64 a) {
    num = a;
    memset(f, -1, sizeof f);
    return dfs(30, 30, 1, 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> l >> r;
    cout << solve(r) - solve(l - 1);

    // for (int i = 30; ~i; --i)
    //     cout << ((114514 >> i) & 1);

    return 0;
}