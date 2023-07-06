#include <cmath>
#include <cstdio>

#define endl '\n'

namespace Fastio {
    namespace Fread {
        const int SIZE = (1 << 21);
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
        const int SIZE = (1 << 21);
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
        template <typename T>
        Reader& operator>>(T& x) {
            char c = getchar();
            while (c < 48 || c > 57) {
                c = getchar();
            }
            x = 0;
            while (c > 47 && c < 58) {
                x = (x << 3) + (x << 1) + (c ^ 48);
                c = getchar();
            }
            return *this;
        }
        Reader& operator>>(char& c) {
            c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            return *this;
        }
        Reader& operator>>(char* str) {
            int len = 0;
            char c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            while (c != ' ' && c != '\n' && c != '\r')
                str[len++] = c, c = getchar();
            str[len] = '\0';
            return *this;
        }
        inline Reader() {}
    } cin;
    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (!x) {
                putchar('0');
                return *this;
            }
            static int sta[111];
            int top = 0;
            while (x)
                sta[++top] = x % 10, x /= 10;
            while (top)
                putchar(sta[top] ^ 48), --top;
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
        inline Writer() {}
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
}  // namespace Fastio
using namespace Fastio;

template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

constexpr int N = 1e5 + 514;
constexpr int LOG = log2(N) + 1;
int n, m;
int l, r;
int f[LOG][N];
int logn[N];

void init_log() {
    logn[1] = 0;
    logn[2] = 1;
    for (int i = 3; i <= n; ++i) {
        logn[i] = logn[i >> 1] + 1;
    }
}

void init_st() {
    for (int i = 1; i <= logn[n]; ++i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
        }
    }
}

int query(int lef, int rig) {
    int len = rig - lef + 1;
    return max(f[logn[len]][lef], f[logn[len]][r - (1 << logn[len]) + 1]);
}

int main() {
    cin >> n >> m;
    init_log();
    for (int i = 1; i <= n; ++i) {
        cin >> f[0][i];
    }
    init_st();
    while (m--) {
        cin >> l >> r;
        cout << query(l, r) << endl;
    }

    return 0;
}