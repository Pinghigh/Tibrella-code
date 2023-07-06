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
            T dp = 1;
            while (c < '0' || c > '9') {
                if (c == '-') dp = -1;
                c = getchar();
            }
            x = 0;
            while (c >= '0' && c <= '9')
                x = x * 10 + (c - '0'), c = getchar();
            x *= dp;
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
            if (x < 0) putchar('-'), x = -x;
            static char sta[40];
            int top = 0;
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

using i64 = long long;

const int mod = 1e9 + 7;

#define N 200005

i64 fact[N];
i64 n, k, t;

i64 binpow(i64 x, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) res = res * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return res;
}

void exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    i64 tmp = x;
    x = y;
    y = tmp - a / b * y;
}

i64 inv(i64 a, i64 p) {
    i64 x, y;
    x = y = 0;
    exgcd(a, p, x, y);
    return (x + mod) % mod;
}

i64 C(i64 a, i64 b) {
    if (a < b) return 0;
    return (fact[a] * inv(fact[b], mod) % mod * inv(fact[a - b], mod) % mod);
}

i64 tmp, ans;

int main() {
    fact[0] = 1;
    for (int i = 1; i <= 2e5; ++i) {
        fact[i] = fact[i - 1] * i % mod;
    }
    cin >> t;
    while (t--) {
        cin >> n >> k;
        ans = tmp = 0;
        for (int i = 0; i < n; i += 2)
            tmp = (tmp + C(n, i)) % mod;
        if (n & 1) {                   // 奇数，只可能相等
            ans = binpow(tmp + 1, k);  // 都为一： 1；有偶数零：tmp。实际上这里求的是两个数的关系。
        } else {
            for (int i = 0; i < k; ++i)
                ans = (ans + binpow(tmp, i) * binpow(binpow(2, n), k - i - 1)) % mod;
            ans = (ans + binpow(tmp, k)) % mod;
        }
        cout << ans << endl;
    }

    return 0;
}