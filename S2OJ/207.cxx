#include <cstdio>

template <typename T>
void read(T& _x) {
    _x = 0;
    static char ch;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        _x = _x * 10 + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename T, typename... Args>
void read(T& _x, Args&... args) {
    read(_x);
    read(args...);
}

#define MAXN 100015
#define MAXL 17

int N, M, K;
int fa[MAXN];
int f[MAXL + 4][MAXN];
unsigned int seed1, seed2, tseed, ans, mul = 1;
int u, v;

int jump(int x, int d) {
    int res = x;
    for (int lg = MAXL; ~lg; --lg) {
        if (d & 1 << lg) {
            res = f[lg][res];
        }
    }
    return res;
}

int main() {
    // scanf("%u %u", &seed1, &seed2);
    // scanf("%d %d %d", &N, &M, &K);
    read(seed1, seed2, N, M, K);
    for (int i = 0; i < N - 1; i++) {
        read(u, v);
        if (fa[v]) fa[u] = v;
        else fa[v] = u;
    }
    for (int i = 1; i <= N; ++i) {
        f[0][i] = fa[i];
        // f[1][i] = fa[i];
    }

    for (int lg = 1; lg <= MAXL; ++lg) {
        for (int i = 1; i <= N; ++i) {
            f[lg][i] = f[lg - 1][f[lg - 1][i]];
        }
    }

    for (int i = 1; i <= M; ++i) {
        static int x, d;
        x = (tseed = (tseed * seed1 + seed2) ^ ans) % N + 1;
        d = (tseed = (tseed * seed1 + seed2) ^ ans) % K;
        // printf("%d\n", jump(x, d));
        ans = ans + mul * jump(x, d) + seed2;
        mul = mul * seed2;
    }
    printf("%u\n", ans);
    return 0;
}

