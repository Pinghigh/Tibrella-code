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

using i32 = int;
using i64 = long long;

inline i64 lowbit(i64 x) {
    return x & -x;
}

#define N 100005

i64 id[N], d[N];

i32 n, m;
i32 t1, t2, t3, op;

inline void mod(i32 pos, i64 val) {
    for (i32 i = pos; i <= n; i += lowbit(i)) {
        id[i] += pos * val;
        d[i] += val;
    }
}

inline i64 que(i32 pos) {
    i64 res = 0;
    for (i32 i = pos; i; i -= lowbit(i)) {
        res += d[i] * (pos + 1) - id[i];
    }
    return res;
}

inline void modify(i32 l, i32 r, i64 val) {
    mod(l, val);
    mod(r + 1, -val);
}

inline i64 query(i32 l, i32 r) {
    return que(r) - que(l - 1);
}

int main() {
    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i) {
        cin >> t1;
        modify(i, i, t1);
    }
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> t1 >> t2 >> t3;
            modify(t1, t2, t3);
        } else {
            cin >> t1 >> t2;
            cout << query(t1, t2) << endl;
        }
    }

    return 0;
}