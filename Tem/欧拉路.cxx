#include <algorithm>
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
        cur = end = 0;
        dist = __dist;
    }

    istream(const char*& __dist) {
        cur = end = 0;
        dist = fopen(__dist, "r");
    }

    char get() {
        if (cur == end) {
            cur = buf, end = buf + fread(buf, 1, SIZE, dist);
            if (cur == end) return EOF;
        }
        return *cur++;
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
        if (x < 0) put('-'), x = -x;
        static char stk[30];
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

#include <cassert>
#include <vector>

#define N 2000004
#define all(x) x.begin(), x.end()

int n, m;
int st, en;  // 起点
int t1, t2;
int ind[N], oud[N];
int cnt;
std::vector<i32> g[N];
std::vector<i32> ans;

static inline void add(int a, int b) {
    g[a].emplace_back(b);
    ++oud[a], ++ind[b];
}

void dfs(const i32& u) {
    if (ans.size() > m) return;
    for (; g[u].size();) {
        assert(g[u].size());
        i32 v = g[u].back();
        g[u].pop_back();
        dfs(v);
    }
    ans.push_back(u);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        i32 a, b;
        cin >> a >> b;
        add(a, b);
    }
    for (i32 i = 1; i <= n; ++i)
        std::sort(all(g[i]), [](const i32& a, const i32& b) { return a > b; });
    for (int i = 1; i <= n; ++i) {
        if (oud[i] - ind[i] == 1) {
            st = i;
            ++cnt;
        } else if (oud[i] == ind[i] - 1) {
            en = i;
            ++cnt;
        } else if (oud[i] != ind[i]) {
            cout << "No";
            return 0;
            // ++cnt;
        }
    }
    if (cnt == 0) {
        st = en = 1;
    } else if (cnt != 2) {
        cout << "No";
        return 0;
    }

    if (n == 2) {
        for (int i = 0; i <= m; ++i)
            cout << 1 + (i % 2) << ' ';
        return 0;
    }

    dfs(st);

    std::reverse(all(ans));
    for (auto x : ans)
        cout << x << ' ';

    return 0;
}