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

#include <algorithm>
#include <cmath>

i64 ex_gcd(i64 u, i64 v, i64& x, i64& y) {
    if (!v) {
        x = 1, y = 0;
        return u;
    }

    i64 g = ex_gcd(v, u % v, x, y);
    i64 temp = x;
    x = y;
    y = temp - u / v * y;
    return g;
}

i64 a, b, c, g, x, y, ga, gb, maxx, maxy, minx, miny;
i64 t;
i64 k;

int main() {
    read(t);
    while (t--) {
        read(a, b, c);
        // if (a < b) std::swap(a, b);
        g = ex_gcd(a, b, x, y);
        x *= c / g, y *= c / g;
        if (c % g) {
            puts("-1");
        } else {
            ga = a / g;
            gb = b / g;

            /*
            此处先把 x 的最小正整数值求出来，容易想到 x 最小时 y 最大
            x > 1 时，直接往小取就行
            x <= 1 时，求 1 和 x 的差值然后把差值向上取整地消掉即可
            y 同理
            */
            if (x > 1) {
                k = (x - 1) / gb;
                minx = x - k * gb;
                maxy = y + k * ga;
            } else {
                k = ceil((1.0 - x) / gb);
                minx = x + k * gb;
                maxy = y - k * ga;
            }
            if (y > 1) {
                k = (y - 1) / ga;
                miny = y - k * ga;
                maxx = x + k * gb;
            } else {
                k = ceil((1.0 - y) / ga);
                miny = y + k * ga;
                maxx = x - k * gb;
            }

            // 如果 x, y 的最大值不是正整数，那么无正整数解，最小正整数 x, y 就是上面所求
            if (maxy <= 0 || maxx <= 0) {
                write(minx, ' ', miny, '\n');
            } else {
                // 此处算个数的时候需要注意要算自身，所以 + 1
                write((i64)ceil(maxy - 1.0) / ga + 1, ' ', minx, ' ', miny, ' ', maxx, ' ', maxy, '\n');
            }
        }
    }
    return 0;
}