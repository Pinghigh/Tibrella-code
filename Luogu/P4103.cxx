#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 1000006
#define LG 20

template <typename T>
static void chkmax(T& x, const T& y) {
	if (x < y) x = y;
}

template <typename T>
static void chkmin(T& x, const T& y) {
	if (x > y) x = y;
}

struct edge {
	i32 v, w;
	edge() {}
	edge(const i32& V): v(V) {}
	edge(const i32& V, const i32& W): v(V), w(W) {}
};

std::vector<i32> g[N], keynode;
std::vector<edge> vir[N];

i32 st[LG][N], lg[N];
i32 dfn[N], fa[N], dep[N], tim;
void get_dfn(const i32& u) {
    st[0][dfn[u] = ++tim] = fa[u];
    for (const auto& v : g[u]) {
    	if (v != fa[u]) {
	    	dep[v] = dep[u] + 1;
	    	fa[v] = u;
	        get_dfn(v);
    	}
    }
}

static i32 min(const i32& x, const i32& y) {
	return dfn[x] < dfn[y] ? x : y;
}

void init(const i32& n) {
	for (i32 i = 2; i <= n; ++ i) lg[i] = lg[i>>1] + 1;
	for (i32 i = 1; i <= lg[n]; ++i) 
		for (i32 j = 1; j + (1 << i) - 1 <= n; ++ j)
			st[i][j] = min(st[i-1][j], st[i-1][j + (1 << (i-1))]);
}

i32 get_lca(i32 x, i32 y) {
	if (x == y) return x;
	x = dfn[x], y = dfn[y];
	if (x > y) std::swap(x,y);
	const i32& l = lg[y-x++];
	return min(st[l][x], st[l][y - (1 << l) + 1]);
}

template <typename T>
static void add(T* gra, const i32& u, const i32& v) {
	// cout << u << ' ' << v << '\n';
    gra[u].emplace_back(v);
}


i32 stk[N];

void build() {
	i32 top = 0;
	stk[++top] = 1;
	vir[1].clear();
	if (keynode.front() == 1) keynode.erase(keynode.begin());
	for (const auto& u : keynode) {
		vir[u].clear();
		i32 lca = get_lca(u, stk[top]);
		if (lca != stk[top]) {
			while (dfn[stk[top - 1]] > dfn[lca]) add(vir, stk[top-1], stk[top]), --top;
			if (stk[top-1] != lca) {
				vir[lca].clear();
				add(vir,lca,stk[top]);
				stk[top] = lca;
			} else add(vir,lca,stk[top--]);
		}
		stk[++top] = u;
	}
	for (i32 i = 1; i < top; ++ i) add(vir, stk[i], stk[i+1]);
}

i32 mx[N], mn[N], siz[N];
i32 mxa, mna;
i64 sum;
i32 tot;
std::bitset<N> key;

void dfs(const i32& u) {
	mx[u] = 0, mn[u] = (key[u])?0:0x3f3f3f3f, siz[u] = key[u];
	for (auto& e : vir[u]) {
		const i32& v = e.v;
		if (fa[u] != v) {
			e.w = dep[v] - dep[u];
			// cout << v << ' ' << e.w << '\n';
			dfs(v);
		}
	}
	for (auto& e : vir[u]) {
		const i32& v = e.v;
		if (fa[u] != v) {
			sum += e.w * 1ll * siz[v] * (tot - siz[v]);
			if (siz[u]) {chkmax(mxa, mx[u] + e.w + mx[v]); chkmin(mna, mn[u] + e.w + mn[v]);}
			chkmax(mx[u], mx[v] + e.w); chkmin(mn[u], mn[v] + e.w);
			siz[u] += siz[v];
			siz[v] = mx[v] = mn[v] = 0;
		}
	}
}


int main() {
	i32 n;
	cin >> n;
	for (i32 i = 1; i < n; ++ i) {
		i32 u, v;
		cin >> u >> v;
		add(g, u, v), add(g, v, u);
	}
	get_dfn(1);
	init(n);
	i32 q;
	cin >> q;
	while(q--) {
		sum = 0, mxa = 0, mna = 0x3f3f3f3f;
		for (const auto& x : keynode) key[x] = false;
		keynode.clear();
		key[1] = false;
		cin >> tot;
		for (i32 i = 1; i <= tot; ++ i) {
			i32 x;
			cin >> x;
			keynode.emplace_back(x), key[x] = true;
		}
		std::sort(keynode.begin(), keynode.end(), [](const i32& a, const i32& b) {return dfn[a] < dfn[b];});
		build();
		dfs(1);
		cout << sum << ' ' << mna << ' ' << mxa << '\n';
	}
    return 0;
}