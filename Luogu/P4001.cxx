#pragma GCC target("avx2,sse4a,lzcnt,popcnt,bmi,bmi2,fma")

#include <cstdio>
#include <string>

namespace Fastio {
    namespace Fread {
        const int SIZE = (1 << 20);
        char buf[SIZE], *S, *T;
        inline char getchar() {
            if (S == T) {
                T = (S = buf) + fread(buf, 1, SIZE, stdin);
                if (S == T) return '\n';
            }
            return *S++;
        }
    }  // namespace Fread
    namespace Fwrite {
        const int SIZE = (1 << 20);
        char buf[SIZE], *S = buf, *T = buf + SIZE;
        inline void flush() {
            fwrite(buf, 1, S - buf, stdout);
            S = buf;
        }
        inline void putchar(char c) {
            *S++ = c;
            if (S == T) flush();
        }
        struct NTR {
            ~NTR() {
                flush();
            }
        } ztr;
    }  // namespace Fwrite
#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif
    struct Reader {
        char c;
        template <typename T>
        Reader& operator>>(T& x) {
            T dp = 1;
            do {
                c = getchar();
                if (c == '-') dp = -1;
            } while (c < '0' || c > '9');
            x = 0;
            do {
                x = x * 10 + (c ^ '0'), c = getchar();
            } while (c > 47 && c < 58);
            x *= dp;
            return *this;
        }
        Reader& operator>>(char& ch) {
            ch = getchar();
            while (ch == ' ' || ch == '\n')
                ch = getchar();
            return *this;
        }
        Reader& operator>>(char* str) {
            int len = 0;
            c = getchar();
            while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
                c = getchar();
            while (c != ' ' && c != '\n' && c != '\r' && c != '\t')
                str[len++] = c, c = getchar();
            str[len] = '\0';
            return *this;
        }
        Reader& operator>>(std::string& str) {
            str.resize(0);
            do {
                c = getchar();
            } while (c == ' ' || c == '\n');
            do {
                str += c, c = getchar();
            } while (c != ' ' && c != '\n' && c != '\r');
            // str += '\0';
            return *this;
        }
        inline Reader() {}
    } cin;
    const char endl = '\n';
    static char __output_sta[40];
    int __output_top;

#define sta __output_sta
#define top __output_top

    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (x < 0) putchar('-'), x = -x;
            top = 0;
            do {
                sta[++top] = x % 10 ^ 48, x /= 10;
            } while (x);
            do {
                putchar(sta[top--]);
            } while (top);
            return *this;
        }
        Writer& operator<<(char c) {
            putchar(c);
            return *this;
        }
        Writer& operator<<(char* str) {
            int cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        Writer& operator<<(const char* str) {
            int cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        Writer& operator<<(const std::string& str) {
            for (auto& c : str)
                putchar(c);
            return *this;
        }
        inline Writer() {}
#undef sta
#undef top
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
}  // namespace Fastio
using namespace Fastio;

#include <algorithm>
#include <cstring>

#include <queue>

using std::max;
using std::min;

using i32 = int;

#define N 2000

i32 n, m;
i32 s, t;

i32 hash(i32 x, i32 y) {
    return x * (n + 10) + y;
}

struct edge {
    edge *nex, *opp;
    i32 to, w;
} graph[((N + 5) * (N + 5)) << 2], *fir[(N + 5) * (N + 5)], *cur[(N + 5) * (N + 5)];
edge* tot = graph;

void add(i32 a, i32 b, i32 w) {
    tot->to = b;
    tot->w = w;
    tot->nex = fir[a];
    tot->opp = (tot + 1);
    fir[a] = tot++;

    tot->to = a;
    tot->w = w;
    tot->nex = fir[b];
    tot->opp = (tot - 1);
    fir[b] = tot++;
}

i32 dep[N * N];

bool bfs() {
    std::queue<i32> q;
    memset(dep, 0, sizeof dep);
    q.push(s);
    cur[s] = fir[s];
    dep[s] = 1;
    while (q.size()) {
        i32 nod = q.front();
        q.pop();
        for (edge* e = fir[nod]; e; e = e->nex) {
            i32 to = e->to;
            if (e->w && !dep[to]) {
                dep[to] = dep[nod] + 1;
                q.push(to);
                cur[to] = fir[to];
            }
        }
    }
    return (dep[t] != 0);
}

i32 dfs(i32 nod, i32 flow) {
    if (nod == t) return flow;
    for (edge* e = cur[nod]; e; e = e->nex) {
        cur[nod] = e;
        i32 to = e->to;
        if (dep[to] == dep[nod] + 1 && e->w) {
            i32 res = dfs(to, min(flow, e->w));
            if (res) {
                e->w -= res;
                e->opp->w += res;
                return res;
            }
        }
    }
    return 0;
}

i32 dinic() {
    i32 res = 0;
    s = hash(1, 1), t = hash(n, m);
    while (bfs()) {
        while (i32 tmp = dfs(s, 0x3f3f3f3f))
            res += tmp;
    }
    return res;
}

i32 t1;

int main() {
    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i)
        for (i32 j = 1; j < m; ++j) {
            cin >> t1;
            add(hash(i, j), hash(i, j + 1), t1);
        }

    for (i32 i = 1; i < n; ++i)
        for (i32 j = 1; j <= m; ++j) {
            cin >> t1;
            add(hash(i, j), hash(i + 1, j), t1);
        }

    for (i32 i = 1; i < n; ++i)
        for (i32 j = 1; j < m; ++j) {
            cin >> t1;
            add(hash(i, j), hash(i + 1, j + 1), t1);
        }

    cout << dinic();

    return 0;
}