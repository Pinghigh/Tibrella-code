#include <iostream>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;

#define N 500001
#define LG 20

using i8 = char;
using i32 = int;
using i64 = long long;

#define log2 llog2

std::vector<i32> g[N];

i8 log2[N];
i32 st[LG][N];

void init() {}

i32 dfn[N], tim, dep[N], fa[N], adfn[N];
void dfs(const i32& u) {
	st[0][dfn[u] = ++tim] = fa[u];
	adfn[tim] = u;
	for (const auto& v : g[u]) 
		if (fa[u] != v) {
			dep[v] = dep[u] + 1;
			fa[v] = u;
			dfs(v);
		}
}

static i32 min(const i32& a, const i32& b) {
	return dfn[a] < dfn[b] ? a : b;
}

void init(const i32& n) {
	for (i32 i = 2; i <= n; ++ i) log2[i] = log2[i>>1] + 1;
	for (i8 i = 1, lim = log2[n]; i <= lim; ++ i) 
		for (i32 j = 1; j + (1<<i) - 1 <= n; ++ j)
			st[i][j] = min(st[i-1][j], st[i-1][j + (1 << (i-1))]);
}
i32 get_lca(i32 a, i32 b) {
	if (a == b) return a; 
	a=dfn[a], b=dfn[b];
	if (a>b) std::swap(a,b);
	const i8& lg = log2[b-a++];
	return min(st[lg][a], st[lg][b - (1<<lg) + 1]);
}

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	i32 root, q;
	i32 n;
	cin >> n >> q >> root;
	for (i32 i = 1; i < n; ++ i) {
		i32 u, v;
		cin >> u >> v;
		g[u].emplace_back(v), g[v].emplace_back(u);
	}
	// fa[root] = root;
	dfs(root);
	init(n);
	while (q--) {
		i32 x, y;
		cin >> x >> y;
		cout << get_lca(x, y) << '\n';
	}
	
	return 0;
}