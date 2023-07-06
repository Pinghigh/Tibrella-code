#pragma GCC target("avx2,sse4a,bmi,bmi2,lzcnt,popcnt")

#include <cstdio>

using llint = long long int;
using ullint = unsigned long long int;
using sint = short int;
using uint = unsigned int;
using ldouble = long double;

#ifdef __WINDOWS__
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef __LINUX__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

char output_stk[40];
sint top;

template <typename T>
void read(T& x) {
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

template <typename T, typename... Args>
void read(T& x, Args&... args) {
    read(x);
    read(args...);
}

template <typename T>
void write(T x) {
    do {
        output_stk[++top] = (x % 10) ^ 48;
        x /= 10;
    } while (x);
    do {
        putchar(output_stk[top]);
    } while (--top);
}

template <typename T>
void write(T x, char ch) {
    do {
        output_stk[++top] = (x % 10) ^ 48;
        x /= 10;
    } while (x);
    do {
        putchar(output_stk[top]);
    } while (--top);
    putchar(ch);
}

template <typename T, typename... Args>
void write(T& x, Args... args) {
    write(x);
    write(args...);
}

template <typename T, typename... Args>
void write(T& x, char ch, Args... args) {
    write(x, ch);
    write(args...);
}

#include <cstring>

#define N 305
#define endl '\n'

struct edge {
    edge* nex;
    int fr, to;
} graph[N];
edge *fir[N], *tot = graph;
int ind[N];
void add(int a, int b) {
    tot->fr = a;
    tot->to = b;
    tot->nex = fir[a];
    ++ind[b];
    fir[a] = tot++;
}

int n, m;
int val[N];
int t1;
int f[N][N];
int siz[N];
auto max = [](auto& a, auto b) { return a > b ? a : b; };
auto min = [](auto& a, auto& b) { return a < b ? a : b; };
void dfs(int nod) {
    siz[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        dfs(e->to);
        for (int i = min(m, siz[nod]); i; --i) {
            for (int j = 1; j <= siz[e->to] && j + i <= m; ++j) {
                f[nod][i + j] = max(f[nod][i + j], f[e->to][j] + f[nod][i]);
            }
        }
        siz[nod] += siz[e->to];
    }
}

int main() {
    read(n, m);
    ++m;
    for (int i = 1; i <= n; ++i) {
        read(t1, f[i][1]);
        add(t1, i);
    }

    dfs(0);

    write(f[0][m], '\n');
    // for (int i = 0; i <= n; ++ i) {
    //     for (int j = 0; j <= m; ++ j) {
    //         cout << f[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    return 0;
}