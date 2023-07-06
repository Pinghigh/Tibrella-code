#pragma GCC target("avx2,sse4a,bmi,bmi2,lzcnt,popcnt")

#include <cstdint>
#include <cstring>

using u64 = int_fast64_t;
using u8 = int8_t;

#include <cstdio>
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
        template <typename T>
        Reader& operator>>(T& x) {
            char c = getchar();
            while (c < '0' || c > '9') {
                c = getchar();
            }
            x = 0;
            while (c > 47 && c < 58)
                x = x * 10 + (c ^ '0'), c = getchar();
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
    const char endl = '\n';
    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (!x) {
                putchar('0');
                return *this;
            }
            static char sta[40];
            u8 top = 0;
            while (x)
                sta[++top] = x % 10 ^ 48, x /= 10;
            while (top)
                putchar(sta[top]), --top;
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
#define endl Fastio::endl
}  // namespace Fastio
using namespace Fastio;

const u64 p10[] = { 10000000000000, 1000000000000, 100000000000, 10000000000, 1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1, 0 };

#define N 15

u64 f[10][N];
u8 trans[N];
u64 mi[N];

u64 dfs(u8 bit, u8 num, bool is_zero, bool limit) {
    if (bit == 13) return 0;
    if (!is_zero && !limit && ~f[num][bit]) return f[num][bit];
    u64 cnt = 0;
    u8 lim = (limit) ? trans[bit] : 9;  // 枚举数字的范围，如果到达上限则设为原数原位，否则枚举 1~9
    for (u8 i = 0; i <= lim; ++i) {
        cnt += dfs(bit + 1, num, is_zero && !i, limit && i == lim);
        if ((!is_zero || i) && num == i) {
            if (limit && lim == i)
                cnt += mi[bit + 1] + 1;
            else
                cnt += p10[bit + 1];
        }
    }
    if (!is_zero && !limit) f[num][bit] = cnt;
    return cnt;
}

u64 solve(u64 bit, u64 num) {
    for (u8 top = 12; top; --top) {
        trans[top] = num % 10;
        num /= 10;
        mi[top] = mi[top + 1] + trans[top] * p10[top + 1];
    }

    return dfs(1, bit, 1, 1);
}

u64 a, b;

int main() {
    memset(f, -1, sizeof f);
    cin >> a >> b;
    for (u8 i = 0; i < 10; ++i)
        cout << solve(i, b) - solve(i, a - 1) << ' ';

    // unzip(114514);
    // for (int i = 12; i ; -- i) cout << mi[i] << ' ';

    return 0;
}