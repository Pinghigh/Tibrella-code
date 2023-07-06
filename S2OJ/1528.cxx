#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

#define N 36
#define M 2000006

using i32 = int;
using i64 = long long;

i64 f[N][M];
i64 a[N], b[N];
i32 n, m;

struct Node {
    i32 son[2];
    i64 mx;
} space[N * 30];

struct trie {
    i32 root;
    void insert(i32 key, i64 val) {
        for (i32 i = 0; i < 31; ++ i) {
             
        }
    }
};

i64 calc(i64 x) {
    i64 res = 0, cost = 0;
    for (i32 i = 1; i <= n; ++i) {
        if ((1 << (i - 1)) & x) {
            // cout << i << ' ';
            cost ^= a[i], res += b[i];
        }
    }
    // cout << x << ' ' << res << ' ' << cost << '\n';
    return cost <= m ? res : -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (i32 i = 1; i <= n; ++i)
        cin >> b[i];

    i64 ans = 0;

    for (i64 i = 1, lim = (1 << (n)) - 1; i <= lim; ++i) {
        ans = std::max(calc(i), ans);
    }

    cout << ans;

    return 0;
}