#include <climits>
#include <cstring>
#include <queue>
#include <cstdio>

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

using std::queue;

#define endl '\n'
#define N 5140
#define E 551400

struct edge {
    edge *nex, *opp;
    int to, w;
} graph[((E + N + N) << 2)];

edge *fir[N << 2], *tot = graph, *cur[N << 2];
int depth[N];
queue<int> q;
auto min = [](int a, int b) { return a < b ? a : b; };
int n, m, e;
int t1, t2;

void add(int a, int b, int c) {
    ++tot;
    tot->to = b;
    tot->w = c;
    tot->nex = fir[a];
    fir[a] = tot;
    tot->opp = tot + 1;

    ++tot;
    tot->to = a;
    tot->w = 0;
    tot->nex = fir[b];
    fir[b] = tot;
    tot->opp = tot - 1;
}

bool bfs() {
    while (q.size())
        q.pop();
    memset(depth, 0, sizeof depth);
    cur[0] = fir[0];
    depth[0] = 1;
    q.push(0);
    while (q.size()) {
        int idx = q.front();
        q.pop();
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (!depth[e->to] && e->w) {
                depth[e->to] = depth[idx] + 1;
                q.push(e->to);
                cur[e->to] = fir[e->to];
            }
        }
    }

    if (depth[n + m + 1]) return true;
    return false;
}

int dfs(int nod, int val) {
    if (nod == n + m + 1) return val;
    for (edge* e = cur[nod]; e; e = e->nex) {
        cur[nod] = e;

        if (depth[nod] + 1 == depth[e->to] && e->w) {
            int res = dfs(e->to, min(e->w, val));
            if (res > 0) {
                e->w -= res;
                e->opp->w += res;
                return res;
            }
        }
    }
    return 0;
}

int dinic() {
    int res = 0;
    while (bfs()) {
        while (int d = dfs(0, INT_MAX)) {
            res += d;
        }
    }
    return res;
}

int main() {
    read(n, m, e);
    for (int i = 0; i < e; ++i) {
        read(t1, t2);
        add(t1, n + t2, 1);
    }
    for (int i = 1; i <= n; ++i)
        add(0, i, 1);
    for (int i = n + 1; i <= m + n; ++i)
        add(i, n + m + 1, 1);

    write(dinic());

    return 0;
}