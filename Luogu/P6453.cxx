#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;
using u32 = unsigned int;

const i64 mod = 1e9 + 7;

#define N 505
#define LG 10

struct Node {
    Node *son, *nex;
    i32 h, w;
    i32 rh;
} space[N];
Node *tot = space, *root;

i32 n, k, he[N];
i32 st[LG][N];

i64 fact[N], ifact[N];

template <typename T>
u32 log2(T a) {
    return (sizeof(T) << 3) - __builtin_clz(a) - 1;
}

void exgcd(const i64& a, const i64& b, i64& x, i64& y) {
    if (!b) {
        x = 1, y = 0;
    } else {
        exgcd(b, a % b, x, y);
        i64 tmp;
        tmp = x;
        x = y;
        y = tmp - (a / b) * y;
    }
}

i64 inv(i64 a) {
    i64 x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

void init() {
    /* ST Table */
    for (i32 lg = 0, lim = log2(n); lg <= lim; ++lg)
        for (i32 i = 1; i + (1 << lg) - 1 <= n; ++i)
            if (!lg)
                st[lg][i] = he[i];
            else
                st[lg][i] = std::min(st[lg - 1][i], st[lg - 1][i + (1 << (lg - 1))]);
    /* Factorial */
    fact[0] = ifact[0] = 1;
    for (i32 i = 1; i <= n; ++i)
        fact[i] = i * fact[i - 1] % mod;
    ifact[n] = inv(fact[n]);
    for (i32 i = n - 1; i; --i)
        ifact[i] = ifact[i + 1] * (i + 1) % mod;
}

i32 query(u32 l, u32 r) {
    u32 lg = log2(r - l + 1);
    return std::min(st[lg][l], st[lg][r - (1 << lg) + 1]);
}

/* Tree */

Node* build(u32 l, u32 r, i32 h) {
    i32 mn = query(l, r);
    Node* nod = tot++;
    nod->h = mn - h;
    nod->w = r - l + 1;
    nod->rh = mn;
    for (u32 i = l; i <= r; ++i) {
        if (he[i] > mn) {
            i32 sr = i;
            while (he[r + 1] > mn)
                ++r;
            Node* son = build(i, sr, mn);
            son->nex = nod->son;
            nod->son = son;
            l = sr + 2;
        }
    }
    return nod;
}

i64 getC(i32 a, i32 b) {
    return fact[a] * ifact[a - b] % mod * ifact[b] % mod;
}

i64 f[N][N], g[N][N];  // 包含 i 和不包含 i
i32 siz[N];

void dfs(Node* nod) {
    i32 u = nod - space;

    if (nod->w == 1) return (f[u][0] = 1, f[u][1] = nod->h), void();

    siz[u] = std::min(nod->h, nod->w);
    for (Node* to = nod->son; to; to = to->nex)
        dfs(to);

    for (i32 i = 0; i <= k; ++i)
        g[u][i] = f[nod->son - space][i];

    for (Node* to = nod->son->nex; to; to = to->nex) {
        i32 v = to - space;
        for (i32 i = k; i; --i)
            for (i32 j = 0; j < i; ++j)
                g[u][i] = (g[u][i] + g[v][j] * g[u][i - j] % mod) % mod;
    }

    for (i32 i = 1; i <= k; ++i) {
        for (i32 j = 0; j <= i; ++j) {
            f[u][i] = (f[u][i] + g[u][j] * getC(nod->w - i + j, nod->h - i));
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(st, 0x3f, sizeof st);

    cin >> n >> k;
    for (i32 i = 1; i <= n; ++i)
        cin >> he[i];

    init();

    root = build(1, n, 0);

    dfs(root);

    cout << f[0][k];

    return 0;
}