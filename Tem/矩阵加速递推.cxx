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

using llint = long long int;

const int N = 105;
constexpr llint MOD = 1e9 + 7;

llint n, k;

struct matrix {
    llint data[5][5];
    llint siz;

    llint* operator[](int a) {
        return data[a];
    }

    const llint* operator[](const int a) const {
        return data[a];
    }

    matrix operator*(const matrix& b) {
        matrix _res;
        for (int i = 1; i <= siz; ++i) {
            for (int j = 1; j <= siz; ++j) {
                for (int k = 1; k <= siz; ++k) {
                    _res.data[i][j] += data[i][k] * b.data[k][j] % MOD;
                    _res.data[i][j] %= MOD;
                }
            }
        }
        return _res;
    }

    matrix& operator*=(const matrix& b) {
        *this = *this * b;
        return *this;
    }

    matrix() {
        siz = 3;
        memset(data, 0, sizeof data);
    }

    void iden() {
        for (int i = 1; i <= siz; ++i) {
            data[i][i] = 1;
        }
    }
} ori, tmp, res;

template <class T>
void binpow(T& a, llint p) {
    res.iden();
    while (p) {
        if (p & 1) res = res * a;
        a = a * a;
        p >>= 1;
    }
}

int main() {
    int t;
    read(t);
    while (t--) {
        read(n);
        if (n <= 3)
            puts("1");
        else {
            res = ori = matrix();
            ori.data[1][1] = ori.data[1][3] = ori.data[2][1] = ori.data[3][2] = 1;
            binpow(ori, n);
            write(res.data[2][1], '\n');
        }
    }
    return 0;
}