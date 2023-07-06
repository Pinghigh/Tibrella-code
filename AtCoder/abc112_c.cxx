#include <algorithm>
#include <cstdio>

#ifdef __WINDOWS__
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef __LINUX__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

char __input_ch;
#define ch __input_ch
template <typename T>
void read(T& x) {
    x = 0;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename T, typename... Args>
void read(T& x, Args&... args) {
    read(x), read(args...);
}

#undef ch

char __output_stk[50], __stk_top;

#define stk __output_stk
#define top __stk_top

template <typename T>
void write(T x) {
    do {
        stk[++top] = x % 10 ^ 48;
        x /= 10;
    } while (x);
    do {
        putchar(stk[top]);
    } while (--top);
}

template <typename T>
void write(T x, char ch) {
    write(x), putchar(ch);
}

template <typename T, typename... Args>
void write(T x, char ch, Args... args) {
    write(x), putchar(ch), write(args...);
}

template <typename T, typename... Args>
void write(T x, Args... args) {
    write(x), write(args...);
}

#undef stk
#undef top

template <typename T>
T abs(T x) {
    return (x < 0) ? -x : x;
}

#include <algorithm>

using i32 = long long;
using i64 = long long;
using std::max;
using std::min;

#define N 105

i32 n;
struct poos {
    i32 x, y, h;
} p[N];

i32 cx[N], cy[N], h[N];

i64 check(i32 x, i32 y) {
    // if (x == 0 && y == 100) {
    //     puts("FUCK");
    // }
    i64 res = -1, tmp;
    for (int i = 1; i <= n; ++i) {
        if (h[i]) {
            tmp = h[i] + abs(x - cx[i]) + abs(y - cy[i]);
            if (~res) {
                if (res != tmp) return -1;
            } else
                res = tmp;
        } else if (abs(x - cx[i]) + abs(y - cy[i]) < res)
            return -1;
    }
    return res;
}

i64 ans = -1, tmp, ansx, ansy;

int main() {
    read(n);
    for (i32 i = 1; i <= n; ++i)
        read(p[i].x, p[i].y, p[i].h);
    std::sort(p + 1, p + n + 1, [](poos& a, poos& b) { return a.h > b.h; });
    for (i32 i = 1; i <= n; ++i) {
        cx[i] = p[i].x, cy[i] = p[i].y, h[i] = p[i].h;
    }
    for (i32 i = 0; i <= 100; ++i)
        for (i32 j = 0; j <= 100; ++j) {
            tmp = check(i, j);
            if (tmp > ans) {
                ans = tmp;
                ansx = i;
                ansy = j;
            }
        }
    write(ansx, ' ', ansy, ' ', ans);
    // write(abs(0 - 2), ' ', abs(3 - 100));

    return 0;
}