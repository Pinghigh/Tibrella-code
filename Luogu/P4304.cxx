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
    } while (ch && (ch != '0') && (ch != '1'));
}

template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    bool f = 0;
    static char ch;
    do {
        ch = getchar();
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

#include <bitset>

using i64 = long long int;

#define N 2005
#define M 4000005

struct edge {
    edge *nex, *opp;
    i64 to, left, fr;
} graph[M << 2], *fir[M], *cur[M];
edge* tot = graph;
void add(i64 a, i64 b, i64 w) {
    tot->to = b;
    tot->fr = a;
    tot->left = w;
    tot->nex = fir[a];
    tot->opp = tot + 1;
    fir[a] = tot++;

    tot->to = a;
    tot->fr = b;
    tot->left = 0;
    tot->nex = fir[b];
    tot->opp = tot - 1;
    fir[b] = tot++;
}

#include <algorithm>
#include <climits>
#include <queue>

using std::max;
using std::min;

std::bitset<N> ob[N];

i64 n, m, s, t, t1, t2;
i64 tmpx, tmpy;
char op;

const i64 mov[][2] = { { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 }, { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 } };

i64 trans(i64 x, i64 y) {
    return x * n + y;
}

i64 dep[M], gap[M];
bool end = false;

void bfs() {
    std::queue<i64> q;
    dep[t] = 1;
    gap[1] = 1;
    q.push(t);
    cur[t] = fir[t];
    while (q.size()) {
        i64 idx = q.front();
        q.pop();
        for (edge* e = fir[idx]; e; e = e->nex) {
            i64 to = e->to;
            if (!dep[to]) {
                dep[to] = dep[idx] + 1;
                ++gap[dep[to]];
                cur[to] = fir[to];
                q.push(to);
            }
        }
    }
}

i64 ans = 0;

i64 dfs(i64 nod, i64 flow) {
    if (nod == t) {
        ans += flow;
        return flow;
    }
    i64 used = 0;
    for (edge* e = cur[nod]; e; e = e->nex) {
        i64 to = e->to;
        if (e->left && dep[to] + 1 == dep[nod]) {
            i64 res = dfs(to, min(flow - used, e->left));
            if (res) {
                e->left -= res;
                e->opp->left += res;
                used += res;
            }
            if (used == flow) return flow;
        }
    }

    if (!--gap[dep[nod]]) end = true;
    ++gap[++dep[nod]];
    return used;
}

i64 ISAP() {
    ans = 0;
    bfs();
    while (!end)
        dfs(s, 0x3f3f3f3f);
    return ans;
}

int main() {
    read(n);
    for (i64 i = 1; i <= n; ++i) {
        for (i64 j = 1; j <= n; ++j) {
            read(op);
            ob[i][j] = op == '1';
        }
        m += ob[i].count();
    }

    s = trans(n + 1, n + 5);
    t = trans(n + 1, n + 6);

    for (i64 i = 1; i <= n; ++i) {
        for (i64 j = 1; j <= n; ++j) {
            if (ob[i][j]) continue;
            if ((i + j) & 1) {
                for (i64 k = 0; k < 8; ++k) {
                    tmpx = i + mov[k][0];
                    tmpy = j + mov[k][1];
                    if (tmpx <= n && tmpy <= n && tmpx > 0 && tmpy > 0 && !ob[tmpx][tmpy]) {
                        add(trans(i, j), trans(tmpx, tmpy), 1);
                    }
                }
                add(s, trans(i, j), 1);
            } else
                add(trans(i, j), t, 1);
        }
    }

    write(n * n - m - ISAP(), '\n');

    // for (auto e = graph; e->to; ++e)
    //     write(e->fr, ' ', e->to, '\n');

    return 0;
}