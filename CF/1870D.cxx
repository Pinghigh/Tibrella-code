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
    static constexpr u32 SIZE = 1 << 18;
    char buf[SIZE], *cur, *end;
    FILE* dist;

    istream(FILE* __dist) {
        dist = __dist;
    }

    istream(const char*& __dist) {
        dist = fopen(__dist, "r");
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
        bool s = false;
        x = 0;
        do {
            c = get();
            if (c == '-') s = true;
        } while (c < 48 || c > 57);
        do {
            x = x * 10 + (c ^ 48);
            c = get();
        } while (c > 47 && c < 58);
        x = s ? -x : x;
        return *this;
    }
} cin(stdin);

struct ostream {
    static constexpr u32 SIZE = 1 << 19;
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
} cout(stdout), cerr(stderr);

#include <algorithm>
#include <cstring>
#include <queue>

#define N 200005

struct pair {
    i32 cost, c;

    bool operator>(const pair& b) const& {
        return cost > b.cost;
    }
};

i32 a[N];

struct p {
    i32 cost;
    i32 c;
} c[N];

void solve() {
    i32 n;
    cin >> n;
    memset(a, 0, sizeof(i32) * (n + 2));
    for (i32 i = 1; i <= n; ++i) {
        i32 x;
        cin >> x;
        c[i] = { x, i };
    }
    std::sort(c + 1, c + n + 1, [](const p& a, const p& b) { return a.cost < b.cost || (a.cost == b.cost && a.c > b.c); });
    std::priority_queue<pair, std::vector<pair>, std::greater<pair>> q;
    i32 k;
    cin >> k;
    q.emplace((pair){ c[1].cost, c[1].c });
    a[c[1].c] = k / c[1].cost;
    k = k % c[1].cost;
    i32 cur = 2;
    while (k && cur <= n) {
        i32 cnt = 0;
        if (q.top().c >= c[cur].c) {
            ++cur;
            continue;
        }
        while (k && a[q.top().c] && c[cur].cost <= k + q.top().cost) {
            --a[q.top().c];
            ++a[c[cur].c];
            k -= c[cur].cost - q.top().cost;
            // cout << k << ' ';
            // cout.flush();
        }
        q.pop();
        q.emplace((pair){ c[cur].cost, c[cur].c });
        ++cur;
    }
    for (i32 i = n - 1; i; --i)
        a[i] += a[i + 1];
    for (i32 i = 1; i <= n; ++i)
        cout << a[i] << ' ';
    cout << '\n';
}

int main() {
    i32 t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}