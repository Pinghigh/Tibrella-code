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

auto max = [](auto a, auto b) { return a > b ? a : b; };
auto min = [](auto a, auto b) { return a < b ? a : b; };

#include <utility>

using i8 = char;
using i16 = short int;
using i32 = long int;
using i64 = long long int;
using i128 = __int128;
using pii = std::pair<int, int>;

#define N 1000005

struct edge {
    edge* nex;
    i32 to;
} graph[N], *fir[N];
edge* tot = graph;
void add(i32 a, i32 b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}
i32 depth[N], cnt[N];
pii stk[N];
i32 top;

void dfs(i32 nod, i32 fa) {
    ++cnt[depth[nod]];
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to == fa) continue;
        depth[to] = depth[nod] + 1;
        dfs(to, nod);
    }
}

int main() {
    i32 t1, t2, n;
    read(n);
    for (i32 i = 1; i < n; ++i) {
        read(t1, t2);
        add(t1, t2);
        add(t2, t1);
    }

    dfs(1, 0);
    i32 mxdep = 0;
    i32 ans = 0, sum = 0;
    for (int i = 1; i <= n; ++i)
        mxdep = max(mxdep, depth[i]);
    stk[++top] = { cnt[1], 1 };
    sum = cnt[1];
    for (int dep = 2; dep <= mxdep; ++dep) {
        if (stk[top].first <= cnt[dep]) {
            stk[++top] = { cnt[dep], 1 };
            sum += cnt[dep];
        } else {
            ans = max(ans, sum);
            i32 note = 1;
            while (top && cnt[dep] < stk[top].first) {
                sum -= stk[top].second * stk[top].first;
                note += stk[top].second; // 此处不能只自加
                --top;
            }
            sum += note * cnt[dep];
            stk[++top] = { cnt[dep], note };
        }
    }

    write(max(ans, sum) + 1, '\n');

    return 0;
}