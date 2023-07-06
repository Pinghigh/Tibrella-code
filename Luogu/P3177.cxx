#pragma GCC target("avx2,sse4a,lzcnt,popcnt,bmi,bmi2,fma")

#define re register

#include <cstdio>

#ifdef __WINDOWS__
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef __LINUX__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

template <typename __inputType>
inline void read(__inputType& x) {
    x = 0;
    static char ch;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename __inputType, typename... __inputArgs>
void read(__inputType& x, __inputArgs&... __args) {
    read(x);
    read(__args...);
}

static unsigned char __output_stack[64], __pos;
template <typename __outputType>
inline void write(__outputType __x, char __ch = ' ') {
    __pos = 0;
    do {
        __output_stack[__pos++] = __x % 10 ^ 48;
        __x /= 10;
    } while (__x);
    while (__pos--) {
        putchar(__output_stack[__pos]);
    }
    putchar(__ch);
}

template <typename __outputType, typename... __outputArgs>
void write(__outputType __x, char __ch, __outputArgs... __args) {
    write(__x, __ch);
    write(__args...);
}

#include <algorithm>

#define N 2005

using i32 = int;
using i64 = long long;

template <typename T>
inline T max(T a, T b) {
    return a > b ? a : b;
}
template <typename T>
inline T min(T a, T b) {
    return a < b ? a : b;
}

struct edge {
    edge* nex;
    i32 to, w;
} graph[N << 1], *fir[N];
edge* tot = graph;

i32 n, k;

i32 siz[N];
i64 f[N][N];

void dfs(i32 nod, i32 fa) {
    siz[nod] = 1;
    // f[nod][0] = f[nod][1] = 0;
    for (re edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to != fa) {
            dfs(to, nod);
            for (re i32 i = min(k, siz[nod]); ~i; --i)
                for (re i32 j = min(siz[to], k - i); ~j; --j) {
                    f[nod][i + j] = max(f[nod][i + j], f[nod][i] * 1ll + f[to][j] + j * 1ll * (k - j) * e->w + (siz[to] - j) * 1ll * (n - k + j - siz[to]) * e->w);
                }
            siz[nod] += siz[to];
        }
    }
}

int main() {
    // memset(f, -1, sizeof f);
    read(n), read(k);
    for (re i32 i = 1; i < n; ++i) {
        i32 a, b, w;
        read(a), read(b), read(w);

        tot->to = b;
        tot->w = w;
        tot->nex = fir[a];
        fir[a] = tot++;

        tot->to = a;
        tot->w = w;
        tot->nex = fir[b];
        fir[b] = tot++;
        // cout << (tot - 1)->w << std::endl;
    }

    dfs(1, 0);

    write(f[1][k]);

    return 0;
}