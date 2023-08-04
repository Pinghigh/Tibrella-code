#include <algorithm>
#include <iostream>
#include <numeric>

using std::cin;
using std::cout;

using i32 = int;

#define N 500005

i32 fa[N], rk[N], p[N], sz[N];
i32 t;
char op;
i32 i, j;

i32 find(i32 x) {
    if (x == fa[x]) return x;
    i32 rt = find(fa[x]);
    p[x] += p[fa[x]];
    return fa[x] = rt;
}

void merge(i32 x, i32 y) {
    x = find(x), y = find(y);
    // if (x == y) return;
    // if (rk[x] > rk[y]) {

    //     rk[x] = std::max(rk[x], rk[y] + 1);
    // } else {
    //     fa[x] = y;
    //     rk[y] = std::max(rk[y], rk[x] + 1);
    // }
    fa[x] = y;
    p[x] = sz[y];
    sz[y] += sz[x];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    std::iota(fa + 1, fa + N - 5 + 1, 1);
    std::fill(sz + 1, sz + N - 5 + 1, 1);
    // std::fill(p + 1, p + N - 5 + 1, 1);
    while (t--) {
        cin >> op >> i >> j;
        if (op == 'M') {
            merge(i, j);
        } else {
            i32 fi = find(i), fj = find(j);
            if (fi == fj)
                cout << abs(p[i] - p[j]) - 1 << '\n';
            else
                cout << "-1\n";
        }
    }

    return 0;
}