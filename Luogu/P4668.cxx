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
#include <bitset>
#include <cstring>
#include <queue>

using std::min;
using std::queue;

#define N 800

using i8 = char;
using i32 = int;
using i64 = long long;

i32 xmn[N][N], ymn[N][N], mn[N][N], mmn[N][N];
std::bitset<N> mp[N];

struct pos {
    i32 x, y;

    bool operator==(pos& c) {
        return c.x == x && c.y == y;
    }
} me, vk, end;

i32 n, m;
char c;

bool valid(i32 x, i32 y) {
    return (x > 0 && x <= n && y > 0 && y <= m && mp[x][y]);
}

int main() {
    memset(mn, -1, sizeof mn);
    memset(mmn, -1, sizeof mmn);
    memset(ymn, 0x3f, sizeof ymn);
    memset(xmn, 0x3f, sizeof xmn);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> c;
            if (c != 'I') {
                mp[i][j] = 1;
            } else
                mn[i][j] = mmn[i][j] = 0x3f3f3f3f;

            if (c == 'T')
                end = { i, j };
            else if (c == 'Y')
                me = { i, j };
            else if (c == 'V')
                vk = { i, j };
        }
    }

    std::queue<pos> q;

    mn[vk.x][vk.y] = 0;
    q.push(vk);
    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        for (int i = 1; i > -2; i -= 2) {
            if (valid(now.x + i, now.y) && !~mn[now.x + i][now.y]) {
                mn[now.x + i][now.y] = mn[now.x][now.y] + 1;
                q.push((pos){ now.x + i, now.y });
            }
            if (valid(now.x, now.y + i) && !~mn[now.x][now.y + i]) {
                mn[now.x][now.y + i] = mn[now.x][now.y] + 1;
                q.push((pos){ now.x, now.y + i });
            }
        }
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (mp[i][j]) xmn[i][j] = min(xmn[i - 1][j], mn[i][j]), ymn[i][j] = min(ymn[i][j - 1], mn[i][j]);

    for (int i = n; i; --i)
        for (int j = m; j; --j)
            if (mp[i][j]) ymn[i][j] = min(ymn[i][j], ymn[i][j + 1]), xmn[i][j] = min(xmn[i][j], xmn[i + 1][j]), mn[i][j] = min(ymn[i][j], xmn[i][j]);

    mmn[me.x][me.y] = 0;
    q.push(me);
    while (!q.empty()) {
        pos now = q.front();
        q.pop();
        // cout << now.x << ' ' << now.y << ' ' << mmn[now.x][now.y] << ' ' << mn[now.x][now.y] << endl;
        if (now == end) {
            cout << ((mmn[now.x][now.y] < mn[now.x][now.y]) ? "YES" : "NO");
            return 0;
        }
        for (i8 i = 1; i > -2; i -= 2) {
            if (valid(now.x + i, now.y) && !~mmn[now.x + i][now.y]) {
                mmn[now.x + i][now.y] = mmn[now.x][now.y] + 1;
                if (mmn[now.x + i][now.y] < mn[now.x + i][now.y]) q.push((pos){ now.x + i, now.y });
            }
            if (valid(now.x, now.y + i) && !~mmn[now.x][now.y + i]) {
                mmn[now.x][now.y + i] = mmn[now.x][now.y] + 1;
                if (mmn[now.x][now.y + i] < mn[now.x][now.y + i]) q.push((pos){ now.x, now.y + i });
            }
        }
    }
    cout << "NO";

    return 0;
}