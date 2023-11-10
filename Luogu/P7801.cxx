#include <cstdio>

using i8 = char;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using i32 = int;
using i64 = long long;
using f64 = double;

struct istream {
    const static size_t SIZE = 1 << 18;
    char buf[SIZE], *cur, *end;
    char get() {
        if (cur == end) {
            cur = buf;
            end = buf + fread(buf, 1, SIZE, stdin);
        }
        return (cur != end) ? *(cur++) : EOF;
    }

    istream& operator>>(char& c) {
        do
            c = get();
        while (c == ' ' || c == '\n' || c == '\r');
        return *this;
    }

    template <typename T>
    istream& operator>>(T& x) {
        x = 0;
        char c;
        do
            c = get();
        while (c < 48 || c > 57);
        do {
            x = (x << 3) + (x << 1) + (c ^ 48);
            c = get();
        } while (c > 47 && c < 58);
        return *this;
    }
} cin;

#define N 101
#define A 501
#define C 100001

i32 mx[N][A], mn[N][A];
i32 a[N], c[N];
i32 suma, sumc;

#include <algorithm>
#include <cstring>

template <typename T>
void chkmax(T& a, const T& b) {
    if (b > a) a = b;
}

template <typename T>
void chkmin(T& a, const T& b) {
    if (b < a) a = b;
}

int main() {
    i32 n, l;
    cin >> n >> l;
    for (i32 i = 1; i <= n; ++i)
        cin >> a[i];

    for (i32 i = 1; i <= n; ++i)
        cin >> c[i], sumc += c[i];
    memset(mx, -0x3f, sizeof mx);
    memset(mn, 0x3f, sizeof mn);

    mx[0][0] = mn[0][0] = 0;
    i32 suma = 0;

    for (i32 i = 1; i <= n; ++i) {
        suma += a[i];
        for (i32 j = std::min(l, i); j; --j) {
            for (i32 k = a[i]; k <= suma; ++k) {
                chkmax(mx[j][k], mx[j - 1][k - a[i]] + c[i]);
                chkmin(mn[j][k], mn[j - 1][k - a[i]] + c[i]);
            }
        }
    }
    // for (i32 j = 0; j <= l; ++j) {
    //     for (i32 k = 0; k <= suma; ++k) {
    //         printf("%d ", mx[j][k]);
    //     }
    //     putchar('\n');
    // }
    f64 ans = 1e18;
    for (i32 i = 1; i <= suma; ++i) {
        if (mx[l][i] > 0) chkmin(ans, mx[l][i] * (sumc - mx[l][i] * 1.0) / (suma - i) / i);
        if (mn[l][i] < 0x3f3f3f3f) chkmin(ans, mn[l][i] * (sumc - mn[l][i] * 1.0) / (suma - i) / i);
    }

    printf("%.3lf", ans);

    return 0;
}