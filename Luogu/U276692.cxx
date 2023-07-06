#include <cstdio>

char buf[1 << 21], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)

#ifdef __WINDOWS__
#define putchar _putchar_nolock
#endif

#ifdef __LINUX__
#define putchar putchar_unlocked
#endif

char ch;
template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename __inputType, typename... __inputArgs>
void read(__inputType& x, __inputArgs&... __args) {
    read(x);
    read(__args...);
}

static unsigned char __output_stack[64], __pos;
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

#include <cmath>

using i64 = unsigned long long;
i64 n, k, x, y, t, lim;

int main() {
    read(t);
    while (t--) {
        read(n, k);
        if (k % (n - k) != k || n <= k) {
            putchar('-');
            putchar('1');
            putchar('\n');
        } else
            write(k, ' ', n - k, '\n');
        // if (!k) {
        //     write(n - 1, ' ', 1, '\n');
        // } else if ((n >> 1) < k) {
        //     putchar('-');
        //     putchar('1');
        //     putchar('\n');
        // } else {
        //     n -= k;
        //     if (!(n & 1) && (n >> 1) > k) {
        //         write((n >> 1) + k, ' ', n >> 1, ' ');
        //         goto nex;
        //     }
        //     for (y = 1, lim = sqrt(n); y <= lim; ++y) {
        //         if (!(n % y)) {
        //             if (y > k && !((n - y) % y)) {
        //                 write(n - y + k, ' ', y, ' ');
        //                 goto nex;
        //             } else if (n / y > k && !((n - n / y) % (n / y))) {
        //                 write(n - n / y + k, ' ', n / y, ' ');
        //                 goto nex;
        //             }
        //         }
        //     }
        // failed:
        //     putchar('-');
        //     putchar('1');
        // nex:
        //     putchar('\n');
        // }
    }
    return 0;
}
