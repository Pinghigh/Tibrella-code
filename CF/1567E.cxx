#pragma GCC optimize("Ofast,unroll-loops,inline")
#pragma GCC target("tune=native,avx2,fma,bmi,bmi2,lzcnt,popcnt")

#include <cstdint>
#include <cstdio>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

struct istream {
    static constexpr u32 SIZE = 1 << 19;
    char buf[SIZE], *cur, *end;
    FILE* dist;
    bool eof;

    istream(FILE* __dist) {
        dist = __dist;
        eof = false;
        cur = end = nullptr;
    }

    istream(const char*& __dist) {
        dist = fopen(__dist, "r");
        eof = false;
        cur = end = nullptr;
    }

    char get() {
        if (cur == end) {
            cur = buf, end = buf + fread(buf, 1, SIZE, dist);
            if (cur == end) return EOF;
        }
        return *(cur++);
    }

    template <typename T>
    istream& operator>>(T& x) {
        char c;
        x = 0;
        do {
            c = get();
        } while (c < 48 || c > 57);
        do {
            x = x * 10 + (c ^ 48);
            c = get();
        } while (c > 47 && c < 58);
        return *this;
    }
} cin(stdin);

struct ostream {
    static constexpr u32 SIZE = 1 << 18;
    char buf[SIZE];
    char* cur = buf;
    FILE* dist;

    ostream(FILE* __dist) {
        dist = __dist;
    }

    ostream(const char*& __dist) {
        dist = fopen(__dist, "r");
    }

    void put(const char& c) {
        if (cur - buf == SIZE) {
            fwrite(buf, 1, SIZE, dist);
            cur = buf;
        }
        *(cur++) = c;
    }
    void flush() {
        fwrite(buf, 1, cur - buf, dist);
        cur = buf;
    }
    ostream& operator<<(const char* s) {
        for (u64 i = 0; s[i]; ++i)
            put(s[i]);
        return *this;
    }

    ostream& operator<<(const char& c) {
        put(c);
        return *this;
    }
    template <typename T>
    ostream& operator<<(T x) {
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
} cout(stdout);
#define N 200005

using i32 = int;
using i64 = long long;

template <typename T>
static void chkmax(T& x, const T& y) {
    if (x < y) x = y;
}

i32 a[N];

struct Node {
    Node *lc, *rc;
    i64 cnt;
    i32 llen, rlen;
    i32 l, r, mid;

    void init(i32 L, i32 R) {
        l = L, r = R, mid = (L + R) >> 1;
    }

    void push_up() {
        cnt = lc->cnt + rc->cnt;
        llen = (a[lc->r] <= a[rc->l] && lc->llen == (lc->r - lc->l + 1)) ? lc->llen + rc->llen : lc->llen;
        rlen = (a[lc->r] <= a[rc->l] && rc->rlen == (rc->r - rc->l + 1)) ? rc->rlen + lc->rlen : rc->rlen;

        if (a[lc->r] <= a[rc->l]) cnt += lc->rlen * 1ll * rc->llen;
    }

    Node operator+(const Node& b) const& {
        Node res;
        res.l = l, res.r = b.r;
        res.cnt = cnt + b.cnt;
        res.llen = (a[r] <= a[b.l] && llen == (r - l + 1)) ? llen + b.llen : llen;
        res.rlen = (a[r] <= a[b.l] && b.rlen == (b.r - b.l + 1)) ? b.rlen + rlen : b.rlen;

        if (a[r] <= a[b.l]) res.cnt += rlen * 1ll * b.llen;
        return res;
    }

    Node() {
        lc = nullptr, rc = nullptr;
    }
} stree[N << 1];
Node *null = stree, *root, *tot = stree;

void build(Node* nod, i32 l, i32 r) {
    nod->init(l, r);
    if (l == r) {
        nod->lc = nod->rc = null;
        nod->cnt = nod->llen = nod->rlen = 1;
    } else {
        nod->lc = ++tot;
        build(nod->lc, l, nod->mid);
        nod->rc = ++tot;
        build(nod->rc, nod->mid + 1, r);
        nod->push_up();
    }
}

Node query(Node* nod, i32 l, i32 r) {
    if (nod->l == l && nod->r == r)
        return *nod;
    else {
        if (r <= nod->mid)
            return query(nod->lc, l, r);
        else if (l > nod->mid)
            return query(nod->rc, l, r);
        else
            return query(nod->lc, l, nod->mid) + query(nod->rc, nod->mid + 1, r);
    }
}

void modify(Node* nod, i32 pos, i32 val) {
    if (nod->l == nod->r)
        return a[pos] = val, void();
    else {
        if (pos > nod->mid)
            modify(nod->rc, pos, val);
        else
            modify(nod->lc, pos, val);
        nod->push_up();
    }
}

int main() {
    root = ++tot;

    i32 n, q;
    cin >> n >> q;
    for (i32 i = 1; i <= n; ++i)
        cin >> a[i];
    build(root, 1, n);

    while (q--) {
        i32 op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
            modify(root, x, y);
        else
            cout << query(root, x, y).cnt << '\n';
    }

    return 0;
}