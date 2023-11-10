#pragma GCC target("avx2,ssse3,lzcnt,popcnt,bmi,bmi2,fma,avx512f")

#include <cstdio>
#include <string>

namespace Fastio {
    namespace Fread {
        const int SIZE = (1 << 19);
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
        const int SIZE = 18;
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
            do {
                c = getchar();
            } while (c < '0' || c > '9');
            x = 0;
            do {
                x = x * 10 + (c ^ '0'), c = getchar();
            } while (c > 47 && c < 58);
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
            top = 0;
            do {
                sta[++top] = x % 10 ^ 48;
                x /= 10;
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

#define N 2001

using i32 = int;
using i64 = long long;

template <typename T>
T max(const T& a, const T& b) {
    return a > b ? a : b;
}
template <typename T>
T min(const T& a, const T& b) {
    return a < b ? a : b;
}

struct edge {
    edge* nex;
    i32 to, w;
} graph[N << 1], *fir[N];
edge* tot = graph;


i32 n, k;
i32 siz[N];
i64 f[N][N];

void dfs(const i32 nod, const i32 fa) {
    siz[nod] = 1;
    // f[nod][0] = f[nod][1] = 0;
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to != fa) {
            dfs(to, nod);
            for (i32 i = min(k, siz[nod]); i != -1; --i)
                for (i32 j = min(siz[to], k - i); ~j; --j) {
                    f[nod][i + j] = max(f[nod][i + j], f[nod][i] * 1ll + f[to][j] + j * 1ll * (k - j) * e->w + (siz[to] - j) * 1ll * (n - k + j - siz[to]) * e->w);
                }
            siz[nod] += siz[to];
        }
    }
}

int main() {
    // memset(f, -1, sizeof f);
    cin >> n >> k;
    for (i32 i = 1; i < n; ++i) {
        i32 a, b, w;
        cin >> a >> b >> w;
        tot->to = b;
        tot->w = w;
        tot->nex = fir[a];
        fir[a] = tot++;

        tot->to = a;
        tot->w = w;
        tot->nex = fir[b];
        fir[b] = tot++;
        // cout << (tot - 1)->w << std::endl;
    }

    dfs(1, 0);

    cout << f[1][k];

    return 0;
}