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
    if (__x < 0) {
        putchar('-');
        __x = -__x;
    }
    if (!__x) {
        putchar(48);
        putchar(__ch);
        return;
    }
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

// using u8 = unsigned int8_t;
using u16 = unsigned short int;
using u32 = unsigned int;
using u128 = unsigned __int128;

const i128 mod = 999911659;
const i128 al[] = { 0, 2, 3, 4679, 35617 };

i128 fact[35617 + 10];

int q, n;

void exgcd(i128 a, i128 b, i128& x, i128& y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    i128 tmp = x;
    x = y;
    y = tmp - a / b * y;
}

i128 c(i128 a, i128 b, i128 p) {
    if (a < b) return 0;
    if (b > a - b) b = a - b;
    i128 d, e, f;
    exgcd(fact[b], p, d, e);
    exgcd(fact[a - b], p, e, f);
    return (fact[a] % p * d % p * e % p) % p;
}

void init(i128 p) {
    fact[0] = 1;
    for (u32 i = 1; i < al[4]; ++i) {
        fact[i] = fact[i - 1] * i % p;
    }
}

i128 lucas(i128 a, i128 b, i128 p) {
    if (b == 0 || a == b) return 1;
    return (c(a % p, b % p, p) * lucas(a / p, b / p, p) % p);
}

i128 binpow(i128 a, i128 k) {
    i128 res = 1;
    a %= mod;
    while (k) {
        if (k & 1) (res *= a) %= mod;
        (a *= a) %= mod;
        k >>= 1;
    }
    return res;
}

i128 a[50];

i128 crt() {
    i128 tmp = 1, ans = 0;
    for (int i = 1; i < 5; ++i)
        tmp *= al[i];
    for (int i = 1; i < 5; ++i) {
        i128 m = tmp / al[i], x, y;
        // write(m, '\n');
        exgcd(m, al[i], x, y);
        // write(m, ' ', a[i], ' ', al[i], '\n');
        ans = (ans + a[i] * m % tmp * x % tmp) % tmp;
    }
    return (ans % tmp + tmp) % tmp;
}

#include <cmath>

int main() {
    read(n, q);

    if (!(q % mod)) {
        putchar(48);
        return 0;
    }

    for (i8 k = 1; k < 5; ++k) {
        init(al[k]);
        for (i128 i = 1, lim = sqrt(n); i <= lim; ++i) {
            if (!(n % i)) {
                (a[k] += lucas(n, i, al[k]) % al[k]) %= al[k];
                if (n / i != i) (a[k] += lucas(n, n / i, al[k]) % al[k]) %= al[k];
            }
        }
    }

    // write(crt(), ' ');

    write(binpow(q, crt()) % mod, '\n');

    return 0;
}