#include <cstdio>
#include <cstring>

#ifdef __LINUX__
#define putchar(a) putchar_unlocked(a)
#endif

#ifdef __WINDOWS__
#define putchar(a) _putchar_nolock()
#endif

static char buf[100000], *pa(buf), *pb(buf);

#define getchar() (pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++)

template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    bool f = 0;
    char ch;
    do {
        ch = getchar();
        // if (ch == '-') {
        //     f = 1;
        // }
    } while (ch < 48 || ch > 57);
    do {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
    x *= (f ? -1 : 1);
}

template <typename __inputType, typename... __inputArgs>
void read(__inputType& x, __inputArgs&... __args) {
    read(x);
    read(__args...);
}

char __output_stack[32], __pos;
template <typename __outputType>
void write(__outputType __x, char __ch = ' ') {
    __pos = 0;
    do {
        __output_stack[__pos++] = __x % 10 ^ 48;
        __x /= 10;
    } while (__x);
    while (__pos--) {
        putchar(__output_stack[__pos]);
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

i32 tmp;

void exgcd(i32 a, i32 b, i32& x, i64& y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}

#define N 5000001

i32 a[N], s[N], f[N];
i64 n, p, k, ans, ktmp, y;

int main() {
    read(n, p, k);
    s[0] = 1;
    for (i32 i = 1; i <= n; ++i)
        read(a[i]), s[i] = s[i - 1] % p * a[i] % p;
    exgcd(s[n], p, f[n], y);
    // write(p, '\n');
    for (i32 i = n - 1; i; --i) {
        f[i] = f[i + 1] % p * a[i + 1] % p;
    }
    f[1] %= p;
    ans = k * f[1] % p;
    ktmp = k % p;
    for (i32 i = 2; i <= n; ++i) {
        f[i] = s[i - 1] % p * f[i] % p;
        cout << f[i] << ", ";
        // ktmp = (ktmp * k) % p;
        // ans = ((ans % p + ktmp * f[i]) % p + p) % p;
    }
    write(ans, '\n');

    return 0;
}