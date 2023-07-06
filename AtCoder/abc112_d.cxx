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
void write(T x, Args... args) {
    write(x), write(args...);
}

#undef stk
#undef top

#include <algorithm>
#include <cmath>
#include <vector>

using i32 = int;
using i64 = long long;

i64 n, m;
std::vector<i32> dv;

int main() {
    read(n, m);
    for (i32 i = 1, lim = sqrt(m); i <= lim; ++i) {
        if (!(m % i)) {
            dv.emplace_back(i);
            if (m / i != i) dv.emplace_back(m / i);
        }
    }
    sort(dv.begin(), dv.end());
    // for (auto i : dv)
    //     write(i, ' ');
    auto it = std::lower_bound(dv.begin(), dv.end(), n);
    if (it == dv.end())
        puts("1");
    else
        write(m / (*it));

    return 0;
}