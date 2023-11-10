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

#define N 10001
#define M 2001

#include <algorithm>
#include <cstring>

template <typename T>
static inline void chkmax(T& a, const T& b) {
    if (a < b) a = b;
}
template <typename T>
static inline void chkmin(T& a, const T& b) {
    if (a > b) a = b;
}

i32 f[N][M];
i32 t[N], b[N];
i32 up[N], down[N];

constexpr i32 INF = 0x3f3f3f3f;

int main() {
    memset(f, 0x3f, sizeof f);

    i32 n, m, k;
    cin >> n >> m >> k;

    for (i32 i = 1; i <= n; ++i)
        cin >> up[i] >> down[i];
    for (i32 i = 1; i <= k; ++i) {
        i32 x;
        cin >> x;
        cin >> b[x] >> t[x];
        ++b[x], --t[x];
    }

    for (i32 i = 1; i <= m; ++i)
        f[0][i] = 0;
    for (i32 i = 1; i <= n; ++i) {
        for (int j = up[i] + 1; j <= m + up[i]; ++j)
            f[i][j] = std::min(f[i - 1][j - up[i]] + 1, f[i][j - up[i]] + 1);
        for (int j = m + 1; j <= m + up[i]; ++j)
            f[i][m] = std::min(f[i][m], f[i][j]);
        for (i32 j = 1; j <= m - down[i]; ++j)
            chkmin(f[i][j], f[i - 1][j + down[i]]);
        if (t[i]) {
            for (i32 j = 1; j < b[i]; ++j)  // b[i] = 0 不影响，所以不用判
                f[i][j] = INF;
            for (i32 j = t[i] + 1; j <= m; ++j)
                f[i][j] = INF;
        }
    }
    i32 ans = INF;
    for (i32 i = 1; i <= m; ++i)
        chkmin(ans, f[n][i]);

    if (ans != INF) {   
        cout << "1\n" << ans;
    } else {
        cout << "0\n";

        int i, j;
        for (i = n; i >= 1; i--) {
            for (j = 1; j <= m; ++j) {
                if (f[i][j] < INF) break;
            }
            if (j <= m) break;
        }
        ans = 0;
        for (int j = 1; j <= i; ++j) {
            if (t[j]) ans++;
        }

        cout << ans;
    }

    return 0;
}