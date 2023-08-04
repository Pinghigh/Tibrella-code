#pragma GCC target("avx2,ssse3,lzcnt,popcnt,bmi,bmi2,fma")
#include <algorithm>
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

using std::max;
using std::min;

using i32 = int;
using i64 = long long;

#define N 500005

struct Node {
    i32 lc, rc;
    i64 d[2];  // 各维度数据
    i64 val, sum;
    i64 mx[2], mn[2];  // 各维度最大最小值
} data[N], tree[N];

void push_up(i32 u) {
    Node* nod = tree + u;
    Node *lc = tree + nod->lc, *rc = tree + nod->rc;

    nod->sum = lc->sum + rc->sum + nod->val;
    for (i32 i = 0; i < 2; ++i) {
        nod->mx[i] = max(nod->d[i], max(lc->mx[i], rc->mx[i]));
        nod->mn[i] = min(nod->d[i], min(lc->mn[i], rc->mn[i]));
    }
}

i32 build(i32 l, i32 r, i32 d) {
    i32 mid = (l + r) >> 1;
    Node* nod = tree + mid;

    std::nth_element(data + l, data + mid, data + r + 1, [&d](const Node& a, const Node& b) { return a.d[d] < b.d[d]; });

    *nod = data[mid];
    if (l < mid) nod->lc = build(l, mid - 1, d ^ 1);
    if (r > mid) nod->rc = build(mid + 1, r, d ^ 1);
    push_up(mid);
    return mid;
}

i64 a, b, c;
bool calc(const Node& nod) {
    return a * nod.d[0] + b * nod.d[1] < c;
}
bool calc(const i64& x, const i64& y) {
    return a * x + b * y < c;
}
i64 query(i64 u) {
    Node* nod = tree + u;

    i32 tmp = 0;
    tmp = calc(nod->mx[0], nod->mx[1]) + calc(nod->mn[0], nod->mx[1]) + calc(nod->mx[0], nod->mn[1]) + calc(nod->mn[0], nod->mn[1]);

    if (tmp == 4) return nod->sum;
    if (!tmp) return 0;

    i64 res = 0;
    if (calc(*nod)) res += nod->val;
    if (nod->lc) res += query(nod->lc);
    if (nod->rc) res += query(nod->rc);
    return res;
}

i32 n, m;
i32 root;

int main() {
    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i)
        cin >> data[i].d[0] >> data[i].d[1] >> data[i].val;

    root = build(1, n, 0);

    while (m--) {
        cin >> a >> b >> c;
        cout << query(root) << '\n';
    }

    return 0;
}