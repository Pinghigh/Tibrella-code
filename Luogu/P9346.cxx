#include <cstdio>

namespace Fastio {
    namespace Fread {
        const unsigned long long SIZE = (1 << 20);
        char buf[SIZE], *S, *T;
        inline char getchar() {
            if (S == T) {
                T = (S = buf) + fread(buf, 1, SIZE, stdin);
                if (S == T) return '\n';
            }
            return *S++;
        }
    }  // namespace Fread
    namespace Fwrite {
        const unsigned long long SIZE = (1 << 20);
        char buf[SIZE], *S = buf, *T = buf + SIZE;
        inline void flush() {
            fwrite(buf, 1, S - buf, stdout);
            S = buf;
        }
        inline void putchar(char c) {
            *S++ = c;
            if (S == T) flush();
        }
        struct NTR {
            ~NTR() {
                flush();
            }
        } ztr;
    }  // namespace Fwrite

#define getchar Fread::getchar
#define putchar Fwrite::putchar

    struct Reader {
        template <typename T>
        Reader& operator>>(T& x) {
            char c = getchar();
            T dp = 1;
            while (c < '0' || c > '9') {
                if (c == '-') dp = -1;
                c = getchar();
            }
            x = 0;
            while (c >= '0' && c <= '9')
                x = x * 10 + (c - '0'), c = getchar();
            x *= dp;
            return *this;
        }
        Reader& operator>>(char& c) {
            c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            return *this;
        }
        Reader& operator>>(char* str) {
            unsigned long long len = 0;
            char c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            while (c != ' ' && c != '\n' && c != '\r')
                str[len++] = c, c = getchar();
            str[len] = '\0';
            return *this;
        }
        inline Reader() {}
    } cin;
    const char endl = '\n';
    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (!x) {
                putchar('0');
                return *this;
            }
            if (x < 0) putchar('-'), x = -x;
            static char sta[40];
            unsigned long long top = 0;
            while (x)
                sta[++top] = x % 10 ^ 48, x /= 10;
            while (top)
                putchar(sta[top]), --top;
            return *this;
        }
        Writer& operator<<(char c) {
            putchar(c);
            return *this;
        }
        Writer& operator<<(char* str) {
            unsigned long long cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        Writer& operator<<(const char* str) {
            unsigned long long cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        inline Writer() {}
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
}  // namespace Fastio
using namespace Fastio;

#include <algorithm>
#include <cstring>

#define N 5005

using i64 = long long;
using i32 = int;

const i64 mod = 985661441;

struct edge {
    edge* nex;
    i64 to;
} graph[N << 1], *fir[N];
edge* tot = graph;
void add(i64 u, i64 v) {
    tot->to = v;
    tot->nex = fir[u];
    fir[u] = tot++;
    // cout << "[ADD] " << u << " TO " << v << '\n';
}

i32 fact[N], ifact[N];

void exgcd(i32 a, i32 b, i32& x, i32& y) {
    if (!b) {
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b, x, y);
        i32 tmp = x;
        x = y;
        y = tmp - a / b * y;
    }
}

i32 inv(i32 a) {
    i32 x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

void init(i32 n) {
    fact[0] = ifact[0] = 1;
    for (i32 i = 1; i <= n; ++i) {
        fact[i] = 1ll * fact[i - 1] * i % mod;
    }
    ifact[n] = inv(fact[n]);
    for (i32 i = n - 1; i; --i) {
        ifact[i] = 1ll * ifact[i + 1] * (i + 1) % mod;
    }
}

i32 n;
i32 t1, t2;
i32 f[N][N][3], g[N][3];
i32 siz[N];

inline i32 getC(i32 a, i32 b) {
    if (a < b || a < 0 || b < 0) return 0;
    // cout << a << ' ' << b << ' ' << fact[a] << ' ' << ifact[b] << ' ' << ifact[a - b] << '\n';
    return 1ll * fact[a] * ifact[b] % mod * ifact[a - b] % mod;
}

inline i32 geta(i32 a, i32 b) {
    if (a < b || a < 0 || b < 0) return 0;
    return 1ll * fact[a] * ifact[a - b] % mod;
}

void dfs(i32 nod) {
    siz[nod] = 1;
    f[nod][0][0] = 1;  // nod 这棵树还没加子树，因此有一个方案。

    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        dfs(to);
        memset(g, 0, sizeof(g));  // 傻逼东西记得清空
        for (i32 i = 0; i < siz[nod]; ++i)
            for (i32 j = 0; j < siz[to]; ++j)
                for (i32 x = 0; x < 3; ++x)
                    for (i32 y = 0; y < 3; ++y) {
                        g[i + j + 1][x] = (g[i + j + 1][x] + 1ll * getC(i + j + 1, i) * (j + 1) % mod * f[nod][i][x] % mod * f[to][j][y] % mod) % mod;    // 根节点单独拎出来
                        if (x != 2 && y != 2) g[i + j][x + 1] = (g[i + j][x + 1] + 1ll * getC(i + j, i) * f[nod][i][x] % mod * f[to][j][y] % mod) % mod;  // nod 入度 +1
                    }

        siz[nod] += siz[to];
        for (i32 i = 0; i <= siz[nod]; ++i)
            for (i32 j = 0; j < 3; ++j)
                f[nod][i][j] = g[i][j];
    }
}

i32 res[N], ans;
i32 tmp, sum;

int main() {
    cin >> n;
    init(n);
    for (i32 i = 2; i <= n; ++i) {
        cin >> t1;
        add(t1, i);
    }

    // for (int i = 1; i <= n; ++i)
    //     cout << fact[i] << ' ' << ifact[i] << '\n';

    dfs(1);

    i32 mul;
    for (i32 i = 0; i < n; ++i) {
        // cout << f[1][i][0] << ' ' << f[1][i][1] << ' ' << f[1][i][2] << '\n';
        res[i] = (1ll * f[1][i][1] + f[1][i][2] + f[1][i][0]) % mod;
        mul = n - i;
        for (i32 j = i - 1; ~j; --j) {
            res[i] = (res[i] - 1ll * res[j] * mul % mod + mod) % mod;
            mul = 1ll * mul * (n - j) % mod;
        }
    }

    sum = inv(sum);
    // 求期望
    for (i32 i = 0; i < n; ++i) {
        ans += 1ll * i * res[i] % mod * fact[n - i - 1] % mod;
        ans %= mod;
    }

    cout << (1ll * ans * ifact[n - 1] % mod + mod) % mod;

    return 0;
}