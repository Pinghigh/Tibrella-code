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
    static constexpr u32 SIZE = 1 << 6;
    char buf[SIZE], *cur, *end;
    FILE *dist;

    istream(FILE *__dist) {
        dist = __dist;
    }

    istream(const char *&__dist) {
        dist = fopen(__dist, "r");
    }

    char get() {
        if (cur == end) cur = buf, end = buf + fread(buf, 1, SIZE, dist);
        return *(cur++);
    }

    template <typename T>
    istream &operator>>(T &x) {
        char c;
        bool s = false;
        x = 0;
        do {
            c = get();
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
    static constexpr u32 SIZE = 1 << 3;
    char buf[SIZE];
    char *cur = buf;
    FILE *dist;

    ostream(FILE *__dist) {
        dist = __dist;
    }

    ostream(const char *&__dist) {
        dist = fopen(__dist, "r");
    }

    void put(const char &c) {
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
    ostream &operator<<(const char *s) {
        for (u64 i = 0; s[i]; ++i) put(s[i]);
        return *this;
    }

    ostream &operator<<(const char &c) {
        put(c);
        return *this;
    }
    template <typename T>
    ostream &operator<<(T x) {
        static char stk[20];
        char top = 0;
        do {
            stk[++top] = x % 10 ^ 48;
            x /= 10;
        } while (x);
        do put(stk[top]);
        while (--top);
        return *this;
    }

    ~ostream() {
        flush();
    }
} cout(stdout);

#define N 1000001

namespace dsu {
    i32 fa[N], siz[N];
    static inline i32 find(const i32& x) {
        return (fa[x] != fa[fa[x]]) ? (fa[x] = find(fa[x])): fa[x];
    }
    static inline void merge(i32 x, i32 y) {
        x = find(x), y = find(y);
        fa[x] = y;
    }
}

int main() {
    i32 n;
    cin >> n;
    for (i32 i = 1; i <= n; ++ i) dsu::fa[i] = i, dsu::siz[i] = 1;
    for (i32 i = 1; i <= n; ++ i) {
        i32 x;
        cin >> x;
        dsu::merge(i,x);
    }
    i32 ans = 0;
    for (i32 i = 1; i <= n; ++ i) ans += (dsu::find(i) == i);
    cout << ans;

    return 0;
}