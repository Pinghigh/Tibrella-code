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

constexpr i32 mod = 998244353;

#define N 200005

i32 a[N];
i32 f[N][2], g[N][2]/* 前缀和 */;
i32 stk[N], top;	

#include <initializer_list> 

int main() {
	i32 n;
	cin >> n;
	for (i32 i = 1; i <= n; ++ i) cin >> a[i];
	f[0][0] = g[0][0] = 1;
	
	for (i32 i = 1; i <= n; ++ i) {
		while (top && a[stk[top]] >= a[i]) --top;
		
		if (!top) for (const bool& j : {false, true}) f[i][j] = g[i-1][j^1] * (i64)a[i] % mod;
		else 
			for (const bool& j : {false, true}) 
				f[i][j] = (f[stk[top]][j] + (g[i-1][j^1] - g[stk[top]-1][j^1]) * (i64)a[i] % mod) % mod;
				
		for (const bool& j : {false, true}) g[i][j] = (g[i-1][j] + f[i][j]) % mod;
		stk[++top] = i;
	}
	
	cout << ((n & 1) ? ((f[n][1] - f[n][0])%mod + mod) % mod : ((f[n][0] - f[n][1])%mod + mod) % mod);
	
	return 0;
}