#pragma GCC target("avx2,sse4a,lzcnt,popcnt,bmi,bmi2,fma")

#include <cstdio>
#include <string>

namespace Fastio {
    namespace Fread {
        const int SIZE = (1 << 18);
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
#include <bitset>
#include <vector>

using std::min;

#define N 2001
#define M 10001

using u32 = unsigned int;

std::vector<u32> e[N], ord;
u32 n, m;
u32 k[N], cnt[N];
u32 t1, t2;
std::bitset<N> vis, an[N];

void dfs(u32 nod) {
    for (auto& to : e[nod]) {
        if (!vis[to]) {
            vis[to] = true;
            dfs(to);
        }
        if (k[to] <= k[nod]) k[nod] = k[to] - 1;
    }
    ord.emplace_back(nod);
}

u32 calc(u32& nod) {
    u32 res = 0;
    for (int i = ord[n - 1], it = n - 1; ~it; i = ord[--it]) {
        if (!an[nod][i]) {
            ++res;
            if (k[i] <= n - res) return n - res + 1;
        }
    }
    return n - res;
}

int main() {
    cin >> n >> m;
    for (u32 i = 1; i <= n; ++i) {
        cin >> k[i];
    }
    for (u32 i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        e[t1].emplace_back(t2);
        // re[t2].emplace_back(t1);
    }
    for (u32 i = 1; i <= n; ++i) {
        if (!vis[i]) {
            vis[i] = true;
            dfs(i);
        }
    }

    std::sort(ord.begin(), ord.end(), [](u32& a, u32& b) { return k[a] < k[b]; });

    for (auto& i : ord) {
        cout << i << ' ';
    }
    // for (int i = ord[n - 1], it = n - 1; ~it; i = ord[--it]) {
    for (int i : ord) {
        an[i][i] = true;
        for (auto& to : e[i]) {
            an[to] |= an[i];
        }
    }

    cout << endl;

    for (u32 i = 1; i <= n; ++i)
        cout << calc(i) << ' ';

    return 0;
}