

#include <cstdint>
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

using i8 = int8_t;
using i16 = short int;
using i32 = long long int;
using i64 = long long int;
using i128 = __int128;

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

char __output_stack[64];
i8 __pos;
template <typename __outputType>
void write(__outputType __x, char __ch = ' ') {
    if (!__x)
        putchar(48);
    else {
        if (__x < 0) {
            __x = -__x;
            putchar('-');
        }
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

template <typename it>
it gcd(it a, it b) {
    it t;
    while (b) {
        t = a;
        a = b;
        b = t % a;
    }
    return a;
}

#include <algorithm>
#include <cmath>

const int mod = 10000;

#define N 55

int n, m, nfish, s, t, k;

struct matrix {
    i64 data[N][N];
    i64* operator[](const int x) {
        return data[x];
    }

    matrix() {
        memset(data, 0, sizeof data);
    }

    matrix operator*(const matrix& ano) {
        matrix res;
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k)
                for (int j = 0; j < n; ++j) {
                    res[i][j] += data[i][k] * ano.data[k][j] % mod;
                    res[i][j] %= mod;
                }
        return res;
    }

    void debug() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                write(data[i][j], ' ');
            }
            putchar('\n');
        }
    }
};

matrix binpow(matrix a, i32 p) {
    matrix res;
    for (int i = 0; i <= n; ++i) {
        res[i][i] = 1;
    }
    while (p) {
        if (p & 1) res = res * a;
        a = a * a;
        p >>= 1;
    }
    return res;
}

matrix ori, ched[13], lmx, ans;
i32 t1, t2;
i32 mov[5], tim;
i32 lcm, dv;

int main() {
    read(n, m, s, t, k);
    for (int i = 1; i <= m; ++i) {
        read(t1, t2);
        ori[t1][t2] = ori[t2][t1] = 1;
    }
    for (int i = 1; i <= 12; ++i) {
        ched[i] = ori;
    }

    for (int i = 0; i < n; ++i) {
        ans[i][i] = 1;
    }

    read(nfish);
    while (nfish--) {
        read(tim);
        for (int i = 0; i < tim; ++i)
            read(mov[i]);  // 第 i 秒在哪个位置
        mov[tim] = mov[0];
        for (int i = 1; i <= 12; ++i)
            for (int k = 0; k < n; ++k)
                ched[i][k][mov[(i - 1) % tim + 1]] = 0;
    }
    lmx = ched[1];
    for (int i = 2; i <= 12; ++i) {
        lmx = lmx * ched[i];
    }
    if (k >= 12) {
        ans = binpow(lmx, k / 12);
        k %= 12;
    }
    for (int i = 1; i <= k; ++i)
        ans = ans * ched[i];

    // lmx.debug();
    write(ans[s][t], '\n');
    // for (int i = 1; i <= 12; ++i)
    //     ched[i].debug(), putchar('\n');

    return 0;
}
