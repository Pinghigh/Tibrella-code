#include <cstdint>
#include <cstdio>

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
    static short int __output_stack[64], __pos;
    __pos = 0;
    do {
        __output_stack[__pos++] = __x % 10;
        __x /= 10;
    } while (__x);
    while (__pos--) {
        putchar(__output_stack[__pos] ^ 48);
    }
    putchar(__ch);
}

template <typename __outputType, typename... __outputArgs>
void write(__outputType __x, char __ch, __outputArgs... __args) {
    write(__x, __ch);
    write(__args...);
}

auto max = [](auto a, auto b) { return a > b ? a : b; };

auto min = [](auto a, auto b) { return a < b ? a : b; };

using i8 = int8_t;
using i16 = short int;
using i32 = long int;
using i64 = long long int;
using i128 = __int128;

#define P 100005

void ex_gcd(i64 a, i64 b, i64& x, i64& y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    ex_gcd(b, a % b, x, y);
    i64 tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}

int n, m, p;
i64 fact[P];

i64 C(i64 a, i64 b) {
    if (a < b) return 0;
    if (b > a - b) b = a - b;
    i64 d, e, f;
    ex_gcd(fact[b], p, d, e);
    ex_gcd(fact[a - b], p, e, f);
    return (fact[a] * d * e) % p;
}

void init() {
    fact[0] = 1;
    for (int i = 1; i < p; ++i) {
        fact[i] = fact[i - 1] * i % p;
    }
}

i64 lucas(int a, int b) {
    if (b == 0) return 1;
    return (C(a % p, b % p) * lucas(a / p, b / p) % p + p) % p;
}

i32 t;

int main() {
    read(t);
    while (t--) {
        read(n, m, p);
        init();
        // write(lucas(n, m), '\n');
        printf("%lld\n", lucas(n + m, n));
    }
    return 0;
}