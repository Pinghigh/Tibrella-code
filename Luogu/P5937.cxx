#pragma GCC target("avx2,fma,avx512f")

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

    istream& operator>>(char* s) {
        char c;
        do
            c = get();
        while ((c == ' ' || c == '\n' || c == '\r') && c != EOF);
        do {
            *(s++) = c;
            c = get();
        } while (c != ' ' && c != '\n' && c != '\r' && c != EOF);
        return *this;
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

#include <algorithm>
#include <vector>

#define all(x) x.begin(), x.end()

#define M 5003

i32 l[M], r[M], op[M];

i32 fa[M << 2];

i32 find(i32 x) {
    return (fa[fa[x]] == fa[x]) ? fa[x] : fa[x] = find(fa[x]);
}

void merge(i32 x, i32 y) {
    x = find(x), y = find(y);
    if (fa[x] != y) fa[x] = y;
}

int main() {
    i32 n, m;
    std::vector<i32> lsh;
    cin >> n >> m;
    for (i32 i = 1; i <= m; ++i) {
        char s[6];
        cin >> l[i] >> r[i] >> s;
        --l[i];
        op[i] = s[0] == 'e';
        lsh.emplace_back(l[i]), lsh.emplace_back(r[i]);
    }
    std::sort(all(lsh));
    lsh.erase(std::unique(all(lsh)), lsh.end());
    for (i32 i = 1; i <= m; ++i)
        l[i] = std::lower_bound(all(lsh), l[i]) - lsh.begin() + 1, r[i] = std::lower_bound(all(lsh), r[i]) - lsh.begin() + 1;

    n = lsh.size();
    for (i32 i = 1; i <= n * 2; ++i)
        fa[i] = i;

    for (i32 i = 1; i <= m; ++i) {
        if (!op[i]) {
            if (find(l[i]) == find(r[i])) {
                cout << i - 1 << '\n';
                return 0;
            } else
                merge(l[i], r[i] + n), merge(l[i] + n, r[i]);
        } else {
            if (find(l[i]) == find(r[i] + n)) {
                cout << i - 1 << '\n';
                return 0;
            } else
                merge(l[i], r[i]), merge(l[i] + n, r[i] + n);
        }
    }
    cout << m << '\n';

    return 0;
}