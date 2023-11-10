#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>

using std::cin;
using std::cout;

#define N 100001

using i32 = int;
using i64 = long long;

std::vector<i32> g[N], vir[N];
i32 n, q;

static void add(std::vector<i32>* gr, const i32& u, const i32& v) {
	// if (gr == vir) cout << u << ' ' << v << '\n';
	gr[u].emplace_back(v);
}

i32 dfn[N], wson[N], top[N], siz[N], dep[N], fa[N], tim;
void get_wson(const i32& u, const i32& fa) {
	siz[u] = 1;
	::fa[u] = fa;
	for (const auto& v : g[u]) {
		if (v != fa) {
			dep[v] = dep[u] + 1;
			get_wson(v, u);
			if (siz[v] > siz[wson[u]]) wson[u] = v;
			siz[u] += siz[v]; 
		}
	}
}
void get_dfn(const i32& u, const i32& top) {
	dfn[u] = ++tim;
	::top[u] = top;
	if (wson[u]) {
		get_dfn(wson[u], top);
		for (const auto& v : g[u]) 
			if (v != fa[u] && v != wson[u]) get_dfn(v, v);
	}
}
i32 get_lca(i32 x, i32 y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

#define all(x) x.begin(), x.end()

std::vector<i32> keynode;
i32 stk[N];
std::bitset<N> key;

void build() {
	i32 tt = 0;
	vir[1].clear();
	stk[++tt] = 1;
	if (keynode.front() == 1) keynode.erase(keynode.begin());
	for (const i32& nod : keynode) {
		i32 lca = get_lca(stk[tt], nod);
		if (lca != stk[tt]) {
			while (dfn[stk[tt-1]] > dfn[lca]) add(vir, stk[tt-1], stk[tt]), --tt;
			if (stk[tt-1] != lca) {
				vir[lca].clear();
				add(vir, lca, stk[tt]);
				stk[tt] = lca;
			} else add(vir, lca, stk[tt--]);
		}
		vir[nod].clear();
		stk[++tt] = nod;
	}
	for (i32 i = 1; i < tt; ++ i) add(vir, stk[i], stk[i+1]);
}

i32 ans;

bool dfs(const i32& u) {
	i32 res = key[u];
	if (key[u]) for (const auto& v : vir[u]) {if (dfs(v)) ++ans;}
	else for (const auto& v : vir[u]) if (dfs(v)) {
		// cout << v << ' ';
		if (res == 1) {++ans, res = -1;}
		else if (res == 0) res = true;
	}
	if (res == -1) return false;
	return res;
	
}

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n;
	for (i32 i = 1; i < n; ++ i) {
		i32 u, v;
		cin >> u >> v;
		add(g,u,v), add(g,v,u);
	}
	get_wson(1, 0);
	get_dfn(1, 1);
	// for (i32 i = 1; i <= n; ++ i) cout << get_lca(2,4) << ' ';
	cin >> q;
	while(q--) {
		for (const auto& nod : keynode) key[nod] = false;
		key[1] = false;
		// key.reset();
		keynode.clear();
		i32 x;
		cin >> x;
		for (i32 i = 1; i <= x; ++ i) {
			i32 k;
			cin >> k;
			keynode.emplace_back(k);
			key[k] = true;
		}
		std::sort(all(keynode),[](const i32& a, const i32& b) {return dfn[a] < dfn[b];});
		keynode.erase(std::unique(all(keynode)), keynode.end());
		for (const auto& nod : keynode) if (key[fa[nod]]) goto failed; 
		build();
		ans = 0;
		dfs(1);
		cout << ans << '\n';
		continue;
failed: cout << "-1\n";
	}
	// for (i32 i = 1; i <= n; ++ i) cout << fa[i] << ' ';
	// for (const auto& x : vir[2]) cout << x << '\n';
	
	return 0;
}