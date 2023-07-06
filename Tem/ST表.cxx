// P3895
#include <cmath>
#include <cstdio>

#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a)

template <typename T>
void read(T &x) {
    x = 0;
    T f = 1;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') {
            f = -1;
        }
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
    return f * x;
}

template <typename T>
void write(T x) {
    if (x < 0) {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 ^ '0');
}

template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

constexpr int N = 1e5 + 514;
constexpr int LOG = log2(N) + 1;
int n, m;
int l, r;
int f[LOG][N];
int logn[N];

void init_log() {
    logn[1] = 0;
    logn[2] = 1;
    for (int i = 3; i <= n; ++i) {
        logn[i] = logn[i >> 1] + 1;
    }
}

void init_st() {
    for (int i = 1; i <= logn[n]; ++i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
        }
    }
}

int query(int lef, int rig) {
    int len = rig - lef + 1;
    return max(f[logn[len]][lef], f[logn[len]][r - (1 << logn[len]) + 1]);
}

int main() {
    read(n);
    read(m);
    init_log();
    for (int i = 1; i <= n; ++i) {
        read(f[0][i]);
    }
    init_st();
    while (m --) {
        read(l); read(r);
        write(query(l,r));
    }

    return 0;
}