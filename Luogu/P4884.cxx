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

using i8 = char;
using i16 = short int;
using i32 = long int;
using i64 = long long int;
using i128 = __int128;

template <typename type>
type gcd(type a, type b) {
    while (b)
        a %= b, std::swap(a, b);
    return a;
}

i128 a = 10, b, p;  // 10^x=9b+1

template <typename type>
type binpow(type x, type y) {
    type res = 1;
    x %= p;
    while (y) {
        if (y & 1) (res %= p) *= x %= p;
        x *= x %= p;
        y >>= 1;
    }
    return res % p;
}

auto max = [](auto a, auto b) { return a > b ? a : b; };

auto min = [](auto a, auto b) { return a < b ? a : b; };

#include <unordered_map>

std::unordered_map<i64, i64> mp;  // 存储的实际上是模数所对应的最大 r（从小到大枚举，挨个覆盖）

#include <cstdlib>

void output(i128 x) {
    write(x, '\n');
    exit(0);
}

int main() {
    read(b, p);
    a = (a % p + p) % p;
    b = 9 * b + 1;
    b = (b % p + p) % p;

    if (!a && !b) output(1);
    if (b == 1) output(0);

    i128 m = sqrt(p)+1, tmp = b;
    for (i128 i = 0; i <= m; ++i) {
        mp[tmp] = i;
        tmp = tmp * a % p;
    }
    tmp = binpow(a, m);
    for (i128 i = 1, pian = tmp; i <= p / m + 10; ++i) {
        auto it = mp.find(tmp);
        if (it != mp.end()) {
            output(i * m - it->second);
        }
        tmp = tmp * pian % p;
    }

    return 0;
}