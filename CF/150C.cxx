#pragma GCC optimize("Ofast,unroll-loops,inline")
#pragma GCC target("avx2,sse4a,lzcnt,popcnt,fma,bmi,bmi2,arch=cannonlake,tune=cannonlake")

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

using i32 = int;
using i64 = long long;
using f64 = double;

#define N 150000

i32 n, m, c;

f64 a[N];

#define lc(u) ((u) << 1)
#define rc(u) ((u) << 1 | 1)

struct Node {
    f64 lmx, rmx, mx, sum;
    i32 l, r, mid;

    Node() {
        lmx = rmx = mx = sum = 0;
        l = r = mid = 0;
    }

    void init(i64 L, i64 R) {
        l = L, r = R;
        mid = (l + r) >> 1;
    }

} stree[N << 2];

Node operator+(Node a, Node b) {
    Node res, *lc = &a, *rc = &b;
    res.init(lc->l, rc->r);
    res.sum = lc->sum + rc->sum;
    res.lmx = max(lc->lmx, lc->sum + rc->lmx);
    res.rmx = max(rc->rmx, rc->sum + lc->rmx);
    res.mx = max({ lc->mx, rc->mx, lc->rmx + rc->lmx });
    return res;
}

void push_up(i32 u) {
    stree[u] = stree[lc(u)] + stree[rc(u)];
    // Node *nod = stree + u, *lc = stree + lc(u), *rc = stree + rc(u);
    // nod->sum = lc->sum + rc->sum;
    // nod->lmx = max(lc->lmx, lc->sum + rc->lmx);
    // nod->rmx = max(rc->rmx, rc->sum + lc->rmx);
    // nod->mx = max({ nod->mx, lc->mx, rc->mx, lc->rmx + rc->lmx });
}

void build(i32 u, i32 l, i32 r) {
    Node* nod = stree + u;
    nod->init(l, r);
    if (l == r) {
        nod->lmx = nod->rmx = nod->mx = nod->sum = a[l];
    } else {
        // nod->lmx = nod->rmx = nod->mx = -INF;
        build(lc(u), l, nod->mid);
        build(rc(u), nod->mid + 1, r);
        push_up(u);
    }
}

Node query(i32 u, i32 l, i32 r) {
    Node* nod = stree + u;
    if (l == nod->l && r == nod->r) {
        return *nod;
    } else {
        if (r <= nod->mid)
            return query(lc(u), l, r);
        else if (l > nod->mid)
            return query(rc(u), l, r);
        else
            return query(lc(u), l, nod->mid) + query(rc(u), nod->mid + 1, r);
    }
}

f64 pc, ans;

i64 pos[N], len;

i32 t1, t2;

int main() {
    cin >> n >> m >> c;
    for (int i = 1; i <= n; ++i)
        cin >> pos[i];

    for (int i = 2; i <= n; ++i) {
        len = pos[i] - pos[i - 1];
        cin >> pc;
        pc /= 100;
        a[i - 1] = pc * (len / 2.0 - c) + (1 - pc) * (len / 2.0);
        // cout << a[i] << '\n';
    }

    build(1, 1, n - 1);

    f64 ans = 0, tmp;

    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        tmp = query(1, t1, t2 - 1).mx;
        if (tmp > 0) ans += tmp;
    }

    // cout << std::fixed << ans;
    printf("%lf", ans);

    return 0;
}