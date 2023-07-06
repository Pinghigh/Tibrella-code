#include <cstdio>

#ifdef __WINDOWS__
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef __LINUX__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

void read(char& ch) {
    do {
        ch = getchar();
    } while (ch && ch != 'Q' && ch != 'R');
}

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

#define N 133338
#define TOP 1000006

u32 cnt[TOP];
u32 lis[N], mod[N], ans[N];
u32 n, m;
u32 block;
u32 mod_cnt;
u32 l, r, res, t;
u32 bel[N];
u32 modpos[N];

struct ele {
    u32 l, r, t;
    u32 id;

    void get(u32 idx, u32 mod) {
        id = idx, t = mod;
        read(l, r);
    }
} q[N];

struct Compare {
    bool operator()(const ele& a, const ele& b) {
        if (bel[a.l] == bel[b.l]) {
            if (bel[a.r] == bel[b.r])
                return bel[a.t] < bel[b.t];
            else
                return bel[a.r] < bel[b.r];
        } else
            return bel[a.l] < bel[b.l];
    }
} cmp;

u32 qcnt, mcnt;
char op;

int main() {
    read(n, m);
    block = cbrt(1.0 * n * n);
    for (int i = 1; i <= n; ++i) {
        read(lis[i]);
        bel[i] = (i - 1) / block + 1;
    }
    for (int i = 1; i <= m; ++i) {
        read(op);
        switch (op) {
            case ('Q'):
                ++qcnt;
                q[qcnt].get(qcnt, mcnt);
                break;
            default:
                ++mcnt;
                read(modpos[mcnt]);
                read(mod[mcnt]);
                break;
        }
    }
    std::sort(q + 1, q + qcnt + 1, cmp);

    l = 1;
    for (u32 i = 1; i <= m; ++i) {
        u32 qr = q[i].r, ql = q[i].l, qt = q[i].t;
        while (r < qr)
            res += !(cnt[lis[++r]]++);
        while (l > ql)
            res += !(cnt[lis[--l]]++);
        while (l < ql)
            res -= !(--cnt[lis[l++]]);
        while (r > qr)
            res -= !(--cnt[lis[r--]]);
        while (t < qt) {
            ++t;
            if (ql <= modpos[t] && qr >= modpos[t]) {
                res += !(cnt[mod[t]]++) - !(--cnt[lis[modpos[t]]]);
            }
            std::swap(mod[t], lis[modpos[t]]);
        }
        while (t > qt) {
            if (ql <= modpos[t] && qr >= modpos[t]) {
                res += !(cnt[mod[t]]++) - !(--cnt[lis[modpos[t]]]);
            }
            std::swap(mod[t], lis[modpos[t]]);
            --t;
        }
        ans[q[i].id] = res;
    }
    for (int i = 1; i <= qcnt; ++i)
        write(ans[i], '\n');

    return 0;
}