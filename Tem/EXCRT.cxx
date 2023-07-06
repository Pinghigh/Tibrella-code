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

#define N 100005

i128 ex_gcd(i128 a, i128 b, i128& x, i128& y) {
    if (b) {
        i128 tmp;
        i128 g = ex_gcd(b, a % b, x, y);
        tmp = x;
        x = y;
        y = tmp - a / b * y;
        return g;
    } else {
        x = 1, y = 0;
        return a;
    }
}

i64 n;
i128 a[N], m[N];  // a === x (mod m)

#include <cstdlib>

i128 ex_crt() {
    i128 k1, k2, a1, m1, a2, m2, c, gc, g;
    a1 = a[1], m1 = m[1];
    for (i64 i = 2; i <= n; ++i) {
        a2 = a[i], m2 = m[i], c = ((a2 - a1) % m2 + m2) % m2;
        g = ex_gcd(m1, m2, k1, k2);
        gc = m2 / g;
        k1 = k1 % gc * ((c / g) % gc) % gc;
        a1 = k1 * m1 + a1;
        m1 *= gc;
        a1 = (a1 % m1 + m1) % m1;
    }
    return a1;
}

int main() {
    read(n);
    for (i64 i = 1; i <= n; ++i) {
        read(m[i], a[i]);
    }

    write(ex_crt(), '\n');
    return 0;
}