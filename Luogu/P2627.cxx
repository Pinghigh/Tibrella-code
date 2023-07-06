#include <cstdio>
#include <cstring>

#ifdef __LINUX__
#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a)
#endif

#ifdef __WINDOWS__
#define getchar() _getchar_nolock()
#define putchar(a) _putchar_nolock()
#endif

template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    bool f = 0;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') {
            f = 1;
        }
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
    x *= (f ? -1 : 1);
}

template <typename __inputType, typename... __inputArgs>
void read(__inputType& x, __inputArgs&... __args) {
    read(x);
    read(__args...);
}

template <typename __outputType>
void write(__outputType __x, char __ch = ' ') {
    if (!__x)
        putchar(48);
    else {
        if (__x < 0) {
            __x = -__x;
            putchar('-');
        }
        static char __output_stack[64], __pos;
        __pos = 0;
        do {
            __output_stack[__pos++] = __x % 10 ^ 48;
            __x /= 10;
        } while (__x);
        while (__pos--) {
            putchar(__output_stack[__pos]);
        }
    }
    putchar(__ch);
}

template <typename __outputType, typename... __outputArgs>
void write(__outputType __x, char __ch, __outputArgs... __args) {
    write(__x, __ch);
    write(__args...);
}

#include <algorithm>
#include <cmath>

template <typename type>
type gcd(type a, type b) {
    while (b)
        a %= b, std::swap(a, b);
    return a;
}

auto max = [](auto a, auto b) { return a > b ? a : b; };
auto min = [](auto a, auto b) { return a < b ? a : b; };

using i8 = char;
using i16 = short int;
using i32 = long int;
using i64 = long long int;
using i128 = __int128;

#define N 200005

i64 n, k, e[N], f[N];  // 第 i 头牛休息最小损失
int q[N], head, tail;
;

int main() {
    read(n, k);
    for (int i = 1; i <= n; ++i)
        read(e[i]);

    head = 1;
    tail = 0;
    for (int i = 0; i <= n + 1; ++i) {
        if (head <= tail && i - q[head] - 1 > k) ++head;
        f[i] = f[q[head]] + e[i];
        while (head <= tail && f[q[tail]] >= f[i])
            --tail;
        q[++tail] = i;
    }
    i64 ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += e[i];
    ans -= f[n + 1];
    write(ans, '\n');

    return 0;
}