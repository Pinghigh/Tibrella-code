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

using i8 = char;
using i16 = short int;
using i32 = long int;
using i64 = long long int;
using i128 = __int128;

#define N 3

#include <array>

using std::array;

i128 mod;

struct matrix {
    array<array<i128, N>, N> data{};

    matrix operator*(const matrix& b) {
        matrix res;

        for (int i = 1; i < N; ++i)
            for (int j = 1; j < N; ++j)
                for (int k = 1; k < N; ++k) {
                    res.data[i][j] += (data[i][k] % mod) * (b.data[k][j] % mod) % mod;
                    res.data[i][j] %= mod;
                }

        return res;
    }

    void debug() {
        for (int i = 1; i <= 2; ++i) {
            for (int j = 1; j <= 2; ++j) {
                write(data[i][j], ' ');
            }
            putchar('\n');
        }
    }

    void iden() {
        for (int i = 1; i < N; ++i) {
            data[i][i] = 1;
        }
    }
};

template <class T>
T binpow(T a, i128 p) {
    T res;
    res.iden();
    while (p) {
        if (p & 1) res = res * a;
        a = a * a;
        p >>= 1;
        // res.debug();
    }
    return res;
}

i128 g, a, c, x, n;

int main() {
    read(mod, a, c, x, n, g);
    matrix ori, base;
    ori.data[1][1] = x;
    ori.data[2][1] = c;
    base.data[1][1] = a;
    base.data[1][2] = base.data[2][2] = 1;

    base = binpow(base, n) * ori;

    // ori.debug();
    // base.debug();

    write(base.data[1][1] % g, '\n');

    return 0;
}