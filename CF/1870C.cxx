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
} cout(stdout);

#define N 100005

#include <algorithm>
#include <set>

i32 a[N], pm[N], sm[N];

void solve() {
    i32 n, k;
    cin >> n >> k;
    std::multiset<i32> s;
    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
        s.emplace(a[i]);
    }
    pm[1] = a[1], sm[n] = a[n];
    for (i32 i = 2; i <= n; ++i)
        pm[i] = std::max(pm[i - 1], a[i]);
    for (i32 i = n - 1; i > 0; --i)
        sm[i] = std::max(sm[i + 1], a[i]);
    std::reverse(sm + 1, sm + n + 1);
    for (i32 i = 1; i <= k; ++i) {
        if (s.find(i) != s.end()) {
            i32 l = std::lower_bound(pm + 1, pm + n + 1, i) - pm;
            i32 r = std::lower_bound(sm + 1, sm + n + 1, i) - sm;
            r = n - r + 1;
            cout << (r - l + 1) * 2 << ' ';
        } else cout << "0 ";
    }
    cout << '\n';
}

int main() {
    i32 t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}