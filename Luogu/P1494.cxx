#pragma GCC target("avx2,ssse3,lzcnt,popcnt,bmi,bmi2,fma")

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
#include <cmath>

using std::swap;

using i64 = long long;

i64 gcd(i64 a, i64 b) {
    if (!a || !b) return 0;
    while (b) {
        a = a % b;
        swap(a, b);
    }
    return a;
}

#define N 50005

struct ask {
    i64 l, r;
    i64 id;
} a[N];

i64 ans1[N], ans2[N];
i64 bel[N];

i64 n, m;
i64 c[N];
i64 block_len;
i64 cnt[N];

i64 ans;

void add(i64 pos) {
    ans -= cnt[c[pos]] * (cnt[c[pos]] - 1);
    ++cnt[c[pos]];
    ans += cnt[c[pos]] * (cnt[c[pos]] - 1);
}

void del(i64 pos) {
    ans -= cnt[c[pos]] * (cnt[c[pos]] - 1);
    --cnt[c[pos]];
    ans += cnt[c[pos]] * (cnt[c[pos]] - 1);
}

void solve() {
    i64 l = 1, r = 0;
    add(++r);
    for (i64 i = 1; i <= m; ++i) {
        i64 ql = a[i].l, qr = a[i].r;
        while (r < qr)
            add(++r);
        while (l > ql)
            add(--l);
        while (r > qr)
            del(r--);
        while (l < ql)
            del(l++);

        ans1[a[i].id] = ans;
        ans2[a[i].id] = (qr - ql + 1) * (qr - ql);
    }
}

int main() {
    cin >> n >> m;
    for (i64 i = 1; i <= n; ++i)
        cin >> c[i];
    for (i64 i = 1; i <= m; ++i) {
        cin >> a[i].l >> a[i].r;
        a[i].id = i;
    }

    block_len = cbrt(n) * cbrt(n);

    for (i64 i = 1, cnt = 1, id = 1; i <= n; cnt = (cnt < block_len) ? (cnt + 1) : (++id, 1), ++i)
        bel[i] = id;

    // cout << block_len << ' ';
    // for (i64 i = 1; i <= n; ++i)
    //     cout << bel[i] << ' ';

    std::sort(a + 1, a + m + 1, [](const ask& a, const ask& b) -> bool { return bel[a.l] < bel[b.l] || (bel[a.l] == bel[b.l] && ((bel[a.l] & 1) ? a.r < b.r : a.r > b.r)); });

    solve();

    for (i64 i = 1; i <= m; ++i) {
        i64 g = gcd(ans1[i], ans2[i]);
        if (g) {
            ans1[i] /= g, ans2[i] /= g;
            cout << ans1[i] << '/' << ans2[i] << '\n';
        } else
            cout << "0/1\n";
    }

    return 0;
}