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
            for (const auto& c : str)
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

#define N 2000005

using u32 = unsigned int;

u32 n, k;
u32 l, r, p, op;

template <typename T> 
static inline void chkmax(T& a, const T& b) {
    if (a < b) a = b;
}

template <typename T> 
static inline void chkmin(T& a, const T& b) {
    if (a > b) a = b;
}

constexpr u32 inf = 0x3f3f3f3f;

struct Node {
    u32 l, r, mid;
    Node *lc, *rc;
    u32 h, mx, mn;

    void init(const u32& L, const u32& R) {
        l = L, r = R, mid = (L+R)>>1,
        mn = inf, mx = 0;
    }

    void movmax(const u32& h) {
        chkmax(mx, h), chkmax(mn, h);
    }

    void movmin(const u32& h) {
        chkmin(mx, h), chkmin(mn, h);
    }

    void push_down() {
        if (lc) lc->movmax(mx), lc->movmin(mn);
        if (rc) rc->movmax(mx), rc->movmin(mn);
        mn = inf, mx = 0; // re init
    }
} space[N<<2],*tot, *root;

void build(Node* nod, const u32& l, const u32& r) {
    nod->init(l, r);
    if (l != r) {
        nod->lc = tot++;
        nod->rc = tot++;
        build(nod->lc, l, nod->mid), build(nod->rc, nod->mid+1, r);
    }
}

void modify(Node* nod, const u32& l, const u32& r, const u32& p, const bool& mode /* IS_MAX */) {
    if (l == nod->l && r == nod->r) 
        mode?nod->movmax(p):nod->movmin(p);
    else {
        nod->push_down();
        if (l > nod->mid) modify(nod->rc, l, r, p, mode);
        else if (r <= nod->mid) modify(nod->lc, l, r, p, mode);
        else modify(nod->lc, l, nod->mid, p, mode), modify(nod->rc, nod->mid+1, r, p, mode);
    }
    
}

void query(Node* nod, const u32& l, const u32& r) {
    if (l == r) cout << nod->mx << '\n';
    else {
        nod->push_down();
        if (nod->lc) query(nod->lc, l, nod->mid);
        if (nod->rc) query(nod->rc, nod->mid+1, r);
    }
}

int main() {
    cin >> n >> k;
    tot = space;
    root = tot++;
    build(root, 1, n);
    while (k--) {
        cin >> op >> l >> r >> p;
        ++l,++r, --op;
        op^=1;
        modify(root, l, r, p, op);
    }
    query(root,1,n);

    return 0;
}