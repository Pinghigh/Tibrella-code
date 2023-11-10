#include <cstdio>
#include <cstdint>

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
    static constexpr u32 SIZE = 1 << 19;
    char buf[SIZE];
    char* cur = buf;
    FILE* dist;

    ostream(FILE* __dist) {
        dist = __dist;
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

#define N 102

u8 a[N][N];
u32 sum[N][4];
u32 n, m;

static bool check(const u32& i) {
	u32 l = 1, r = n;
	for (u32 j = 1; j <= m; ++ j) {
		const u32& tl = sum[j][a[i][j]-1]+1, tr = sum[j][a[i][j]];
	
		// cout << i << ' ' << tl << ' ' << tr << ' ' << l << ' ' << r << '\n';
		if (tr < l || tl > r) return false;
		else r = std::min(r, tr), l = std::min(l, tl);
	}
	return true;
} 

void solve() {
	cin >> n >> m;
	//!TODO 清空
	for (u32 i = 1; i <= n; ++ i) sum[i][3] = sum[i][1] = sum[i][2] = 0;

	for (u32 i = 1; i <= n; ++ i) for (i32 j = 1; j <= m; ++ j) {
		cin >> a[i][j];
		++sum[j][a[i][j]];
	}
	
	
	for (u32 i = 1; i <= m; ++ i) for (u8 c = 1; c < 4; ++ c) sum[i][c] += sum[i][c-1];
	
	// for (u32 i = 1; i <= n; ++ i) cout << sum[i][1] << ' ' << sum[i][2] << ' ' << sum[i][3] << '\n';
	
	for (u32 i = 1; i <= n; ++ i) if (!check(i)) {cout << "NO\n"; return;}
	cout << "YES\n";
}

int main() {
	i32 t;
	cin >> t;
	while (t--) solve();
	
	return 0;
}