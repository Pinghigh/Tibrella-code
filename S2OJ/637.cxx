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

void read(char& ch) {
    do {
        ch = getchar();
    } while (ch != 'C' && ch != 'F' && ch != '#' && ch != '.' && ch != EOF);
    if (ch == EOF) ch = 0;
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
void write(T x, Args... args) {
    write(x);
    write(args...);
}

template <typename T, typename... Args>
void write(T x, char ch, Args... args) {
    write(x, ch);
    write(args...);
}


#include <bitset>
#include <cstring>

#define N 100005

auto max = [](auto a, auto b) { return a > b ? a : b; };

std::bitset<N> vis;
int t, n, k;
int fa[N];
int ans;

int main() {
    read(t);
    while (t--) {
        ans = 0;
        vis.reset();
        read(n, k);
        for (int i = 2; i <= n; ++i)
            read(fa[i]);
        for (int i = n; i > 1; --i) {
            if (!vis[i] && !vis[fa[i]]) {
                vis[fa[i]] = 1;
                ++ans;
            }
        }
        if (ans*2 >= k)
            write((k + 1) >> 1, '\n');
        else
            write(k - ans, '\n');
    }

    return 0;
}