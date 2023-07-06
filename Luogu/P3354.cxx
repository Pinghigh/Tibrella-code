#pragma GCC target("avx2,sse4a,avx512f,bmi,bmi2,lzcnt,popcnt,fma")

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

auto max = [](auto a, auto b) { return a > b ? a : b; };
auto min = [](auto a, auto b) { return a < b ? a : b; };

#define N 105

struct edge {
    edge* nex;
    int to, w;
} graph[N << 2], *fir[N];
edge* tot = graph;
void add(int a, int b, int c) {
    tot->to = b;
    tot->w = c;
    tot->nex = fir[a];
    fir[a] = tot++;
}

int sum;

int n, k;
int val[N];
int f[N][N], dp[N][N];
int siz[N], dis[N];
int t1, t2;

void dfs(int nod) {
    
}

int main() {
    return 0;
}