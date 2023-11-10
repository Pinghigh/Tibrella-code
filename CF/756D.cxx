#include <iostream>
#include <string>

using std::cin;
using std::cout;

using i8 = int;
using i32 = int;
using i64 = long long;

#define N 5001

constexpr i32 mod = 1e9+7;

template <typename T>
static void add(T& a, const T& b) {
	if ((a += b) >= mod) a -= mod;
}

i32 f[N][26], g[N][26], sum[N], ssum[N];

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	std::string s, t;
	i32 n;
	cin >> n >> s;
	t = s;
	s.erase(std::unique(s.begin(),s.end()),s.end());
	for (i32 i = 1; i <= s.size(); ++ i) {
		i8 c = s[i-1] - 'a';
		for (i32 j = 1; j <= n; ++ j) {
			sum[j] = ((i64)sum[j] - f[j][c]) % mod;
			f[j][c] = (ssum[j-1] - g[j-1][c] + 1) % mod;
			g[j][c] = (f[j][c] + g[j-1][c]) % mod;
			sum[j] = ((i64)sum[j] + f[j][c]) % mod;
			ssum[j] = (ssum[j-1] + sum[j]) % mod;
		}
	}
	add(sum[n]%=mod, mod);
	cout << sum[n];
	
	return 0;
}