#include <cstdio>

#ifdef __WINDOWS__
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef __LINUX__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    bool f = 0;
    static char ch;
    do {
        ch = getchar();
        if (ch == '-') {
            f = 1;
        }
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

#include <algorithm>
#include <cmath>

using u32 = unsigned int;

#define N 50005

u32 n, m, k;
u32 cnt[N], ans[N], l, r, res;
u32 block;
u32 lis[N];
u32 bel[N];

class ele {
public:
    u32 l, r;
    u32 id, block_id;

    void get(u32& idx) {
        read(l, r);
        id = idx;
        block_id = bel[l];
    }
} q[N];

void ins(int x) {
    cnt[x]++;
    res += cnt[x] * cnt[x] - (cnt[x] - 1) * (cnt[x] - 1);
}
void del(int x) {
    cnt[x]--;
    res += cnt[x] * cnt[x] - (cnt[x] + 1) * (cnt[x] + 1);
}

int main() {
    read(n, m, k);
    block = sqrt(1.0 * n * n / m);
    for (u32 i = 1; i <= n; ++i) {
        bel[i] = (i - 1) / block + 1;
        read(lis[i]);
    }
    for (u32 i = 1; i <= m; ++i)
        q[i].get(i);

    std::sort(q + 1, q + m + 1, [](const ele& a, const ele& b) {
        if (a.block_id == b.block_id) {
            return (a.block_id & 1) ? a.r < b.r : a.r > b.r;
        } else {
            return a.l < b.l;
        }
    });

    l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        u32 ql = q[i].l, qr = q[i].r;
        while (r < qr)
            ins(lis[++r]);
        while (l > ql)
            ins(lis[--l]);
        while (r > qr)
            del(lis[r--]);
        while (l < ql)
            del(lis[l++]);
        ans[q[i].id] = res;
    }

    for (u32 i = 1; i <= m; ++i)
        write(ans[i], '\n');

    return 0;
}