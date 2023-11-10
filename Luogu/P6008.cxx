#include <iostream>

using std::cin;
using std::cout;

using i32 = long long;
using i64 = long long;

i32 n, m;

#define N 1006

i32 fa[N * N], f[N * N], rk[N * N];

using std::max;

i32 find(const i32& x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void merge(i32 x, i32 y) {
    x = find(x), y = find(y);
    if (x != y) {
        if (rk[x] > rk[y])
            fa[y] = x, rk[x] = max(rk[x], rk[y] + 1);
        else
            fa[x] = y, rk[y] = max(rk[y], rk[x] + 1);
    }
}

static inline i32 hash(i32 x, i32 y) {
    return x * m + y;
}

char s[N][N];

constexpr i64 mod = 1e9 + 7;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i)
        cin >> (s[i]+1);

    for (i32 i = 1; i <= n; ++i)
        for (i32 j = 1; j <= m; ++j)
            fa[hash(i, j)] = hash(i, j), f[hash(i, j)] = 1;

    for (i32 i = n - 1; i > 1; --i) {
        for (i32 j = 2; j < m; ++j)
            if (s[i][j] == '.' && s[i][j - 1] == '.') fa[find(hash(i,j))]=find(hash(i,j-1));
        for (i32 j = 2; j < m; ++j)
            if (s[i][j] == '.' && s[i + 1][j] == '.' && find(hash(i, j)) != find(hash(i + 1, j))) 
                (f[find(hash(i, j))] *= f[find(hash(i + 1, j))]) %= mod, fa[find(hash(i+1, j))]=find(hash(i, j));
        for (i32 j = 2; j < m; ++j) if (s[i][j] == '.' && find(hash(i,j))==hash(i,j)) ++f[hash(i,j)] %= mod;
    }

    i64 ans = 1;
    for (i32 i = n - 1; i > 1; --i) 
        for (i32 j = 2; j < m; ++j) {
            if (s[i][j] == '.' && find(hash(i,j))==hash(i,j)) ans = ans*f[hash(i,j)]%mod;
        }

    cout << ans;

    return 0;
}