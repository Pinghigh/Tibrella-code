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
    static constexpr u32 SIZE = 1 << 15;
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
    static constexpr u32 SIZE = 1 << 15;
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

#define ctz(x) __builtin_ctz(x)

template <typename T>
static T gcd(T a, T b) {
    u8 az = ctz(a), bz = ctz(b), z = az > bz ? bz : az;
    T diff;
    b >>= bz;
    while (a) {
        a >>= az;
        diff = b - a;
        az = __builtin_ctz(diff);
        if (a < b) b = a;
        a = diff < 0 ? -diff : diff;
    }
    return b << z;
}


// template <typename T>
// static T gcd(T a, T b) {
//     u8 az = __builtin_ctz(a), bz = __builtin_ctz(b), z = az > bz ? bz : az;
//     T diff;
//     b >>= bz;
//     while (a) {
//         a >>= az;
//         if (a < b) {
//             diff = b - a;
//             b = a;
//             a = diff;
//         } else a = a - b;
//         az = __builtin_ctz(a);
//     }
//     return b << z;
// }

#define N 5001

i32 a[N], b[N];

constexpr u32 mod = 998244353;

int main() {
    u16 n;
    cin >> n;
    for (u16 i = 1; i <= n; ++i)
        cin >> a[i];
    for (u16 i = 1; i <= n; ++i)
        cin >> b[i];

    for (u16 i = 1; i <= n; ++i) {
        u64 xx = i, ans = 0;
        for (u16 j = 1; j <= n; ++j) {
            ans = (ans + gcd(a[i], b[j]) * xx) % mod;
            xx = xx * i % mod;
        }
        cout << ans << '\n';
    }

    return 0;
}