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

i16 t;
i64 a, b, c, d, ans;

int main() {
    read(t);
    while (t--) {
        read(a, b, c, d);
        ans = 0;
        for (i32 i = 1, j, lim = sqrt(d); i <= lim; ++i) {
            if (!(d % i)) {
                if (!(i % b) && gcd(a / b, i / b) == 1 && gcd(d / c, d / i) == 1) ++ans;
                j = d / i;
                if (i != j && !(j % b) && gcd(a / b, j / b) == 1 && gcd(d / c, d / j) == 1) ++ans;
            }
        }
        write(ans, '\n');
    }
    return 0;
}