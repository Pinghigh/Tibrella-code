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
    static constexpr u32 SIZE = 10;
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

using i32 = int;

constexpr i32 mod = 1e9 + 7;

#define N 200001

u32 f[N];

static void add(u32& a, const u32& b) {
    if ((a += b) >= mod) a -= mod;
}

int main() {
    u32 n, ans = 1;
    cin >> n;
    for (u32 lst, now; n--;) {
        cin >> now;
        u32& x = f[now];
        if (x && now != lst) add(ans, x);
        x = ans;
        lst = now;
    }
    cout << ans;

    return 0;
}