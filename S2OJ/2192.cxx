#include <cstdio>

#define getchar getchar_unlocked
#define putchar putchar_unlocked

char __input_ch;
#define ch __input_ch

template <typename T>
void read(T& x) {
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename T, typename... Args>
void read(T& x, Args&... args) {
    read(x), read(args...);
}

#undef ch

char __output_stk[40], __top;

#define stk __output_stk
#define top __top

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

template <typename T, typename... Args>
void write(T x, char ch, Args... args) {
    write(x), putchar(ch), write(args...);
}

#include <bitset>
#include <cstdint>

#define N 100005

using u32 = uint32_t;
using u64 = uint64_t;

u32 n;
u64 prime[N], tt;
std::bitset<N> tag;
u32 tong[N], a[N];
u32 cnt[N], tot;
u32 t1;

int main() {
    read(n);
    for (u32 i = 2; i <= 100000; ++i) {
        if (!tag[i]) prime[++tt] = i;
        for (u32 j = 1; j <= tt && prime[j] * i <= n; ++j) {
            tag[prime[j] * i] = true;
            if (!(i % prime[j])) break;
        }
    }
    for (u32 i = 1; i <= n; ++i) {
        read(a[i]);
        ++tong[a[i]];
    }

    for (u32 i = 2; i <= 100000; ++i) {
        if (tong[i]) {
            u32 tmp = i;
            for (u32 j = 1; j <= tt; ++j)
                while (!(tmp % prime[j])) {
                    ++tot;
                    cnt[prime[j]] += tong[i];
                    tmp /= prime[j];
                }
        }
    }

    u32 dv = 2;
    for (; tot > 1; ++dv) {
        u32 tmp = dv;
        for (u32 j = 1; j <= tt; ++j)
            while (!(tmp % prime[j]) && cnt[prime[j]]) {
                --tot;
                --cnt[prime[j]];
                tmp /= prime[j];
            }
    }
    if (tot)
        for (u32 i = 2; i <= 100000; ++i) {
            if (cnt[i]) {
                while (dv % i)
                    ++dv;
            }
        }

    write(dv);

    return 0;
}