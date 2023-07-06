#include <cstdio>

#define getchar getchar_unlocked
#define putchar putchar_unlocked

char __input_ch;
#define ch __input_ch

void read(char& c) {
    do {
        c = getchar();
    } while (c == '\t' || c == '\n' || c == '\r' || c == ' ');
}

template <typename T>
void read(T& x) {
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename T, typename... Args>
void read(T& x, Args&... args) {
    read(x), read(args...);
}

#undef ch

char __output_stk[40], __top;

#define stk __output_stk
#define top __top

template <typename T>
void write(T x) {
    do {
        stk[++top] = x % 10 ^ 48;
        x /= 10;
    } while (x);
    do {
        putchar(stk[top]);
    } while (--top);
}

template <typename T>
void write(T x, char ch) {
    write(x), putchar(ch);
}

template <typename T, typename... Args>
void write(T x, Args... args) {
    write(x), write(args...);
}

template <typename T, typename... Args>
void write(T x, char ch, Args... args) {
    write(x), putchar(ch), write(args...);
}

using i32 = int;
using i64 = long long;
using i128 = __int128;

const i32 mod = 10007;

#include <algorithm>

i32 n, m, k;
i64 ans;

i128 gcd(i128 a, i128 b) {
    i32 tmp;
    while (b) {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

void mo() {
    if (ans >= mod) ans -= mod;
}

void dfs(i32 pos, i128 prod) {
    if (!pos) {
        if (prod % k) return;
        if (gcd(prod / k, (i128)k) == 1) return ++ans, mo();
        return;
    }
    if (prod % k)
        for (int i = 1; i <= m; ++i)
            dfs(pos - 1, i * prod);
    else
        for (int i = 1; i <= m; ++i)
            if (gcd(i, k) == 1) dfs(pos - 1, i * prod);
}

int main() {
    read(n, m, k);

    dfs(n, 1);

    write(ans);

    return 0;
}