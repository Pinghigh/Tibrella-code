#include <cstdio>

using i8 = char;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using i32 = int;
using i64 = long long;
using f64 = double;

struct istream {
    const static size_t SIZE = 1 << 18;
    char buf[SIZE], *cur, *end;
    char get() {
        if (cur == end) {
            cur = buf;
            end = buf + fread(buf, 1, SIZE, stdin);
        }
        return (cur != end) ? *(cur++) : EOF;
    }

    istream& operator>>(char& c) {
        do
            c = get();
        while (c == ' ' || c == '\n' || c == '\r');
        return *this;
    }

    template <typename T>
    istream& operator>>(T& x) {
        x = 0;
        char c;
        do
            c = get();
        while (c < 48 || c > 57);
        do {
            x = (x << 3) + (x << 1) + (c ^ 48);
            c = get();
        } while (c > 47 && c < 58);
        return *this;
    }
} cin;


struct ostream {
    static constexpr u32 SIZE = 1 << 19;
    char buf[SIZE];
    char* cur = buf;
    FILE* dist;

    void put(const char& c) {
        if (cur - buf == SIZE) {
            fwrite(buf, 1, SIZE, stdout);
            cur = buf;
        }
        *(cur++) = c;
    }
    void flush() {
        fwrite(buf, 1, cur - buf, stdout);
        cur = buf;
    }

    ostream& operator<<(const char& c) {
        put(c);
        return *this;
    }
    template <typename T>
    ostream& operator<<(T x) {
        if (x < 0) put('-'), x = -x;
        static char stk[20];
        char top = 0;
        do {
            stk[++top] = x % 10 ^ 48;
            x /= 10;
        } while (x);
        do
            put(stk[top]);
        while (--top);
        return *this;
    }

    ~ostream() {
        flush();
    }
} cout;

#include <algorithm>

#define N 100001
#define C 21

using u16 = unsigned short;
using u32 = unsigned int;
using i32 = int;
using i64 = long long;

constexpr u16 mod = 1e4 + 7;

static void add(u16& a, const u16& b) {
    a += b;
    if (a >= mod) a -= mod;
}

i32 lc[N << 1], rc[N << 1];
u16 f[N << 1][C];
i32 tot = 1;

i32 n, c;

i32 a[N], b[N];

static void push_up(const i32& u) {
    u16 *lc = f[::lc[u]], *rc = f[::rc[u]], *nod = f[u];
    for(i32 i = 0; i <= c; ++i) f[u][i] = 0;
    for (i32 i = 0; i <= c; ++i) for (i32 j = 0; j <= c; ++j) 
        add(nod[std::min(i+j,c)], lc[i] * (u32)rc[j] % mod);
}

void build(const i32& u, const i32& l, const i32& r) {
    if (l == r) f[u][1] = a[l]%mod, f[u][0] = b[l]%mod;
    else {
        i32 mid = (l + r) >> 1;
        lc[u] = ++tot, rc[u] = ++tot;
        build(lc[u], l, mid);
        build(rc[u], mid+1, r);
        push_up(u);
    }
}

void modify(const i32& u, const i32& l, const i32& r, const i32& pos) {
    if (l == r) f[u][1] = a[l]%mod, f[u][0] = b[l]%mod;
    else {
        i32 mid = (l + r) >> 1;
        if (pos <= mid) modify(lc[u], l, mid, pos);
        else modify(rc[u], mid+1, r, pos);
        push_up(u);
    }
}

int main() {
    cin >> n >> c;

    for (i32 i = 1; i <= n; ++i)
        cin >> a[i];
    for (i32 i = 1; i <= n; ++i)
        cin >> b[i];

    build(1, 1, n);

    i32 q;
    cin >> q;
    while (q--) {
        i32 x;
        cin >> x >> a[x] >> b[x];
        modify(1, 1, n, x);
        cout << f[1][c] << '\n';
    }   

    return 0;
}