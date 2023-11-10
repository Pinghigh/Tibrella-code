#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

template <typename _Tp>
static void chkmin(_Tp& a, const _Tp& b) {
	if (b<a)a=b;
}

#define N 500005
#define M 2000001

struct edge {
	i32 v;
	edge *opp, *nxt;
} graph[M<<1], *fir[N];
edge *tot = graph + 1, *null = graph;

void add(const i32& u, const i32& v) {
	tot->v = v,
	tot->nxt = fir[u],
	tot->opp = tot + 1;
	fir[u] = tot++;
	
	tot->v = u,
	tot->nxt = fir[v],
	tot->opp = tot - 1;
	fir[v] = tot++;
}

std::list<std::vector<i32>> ans;

i32 dfn[N], low[N], tim;
i32 stk[N], top;

void tarjan(const i32& u, const edge* las) {
	dfn[u] = low[u] = ++tim;
	stk[++top] = u;
	for (edge* e = fir[u]; e; e = e->nxt) {
		i32 v = e->v;
		// cout << u << ' ' << e.v << ' ' << e.id << ' ' << las << ' ' << '\n';
		if (e == las->opp) continue;
		else if (!dfn[v]) {
			tarjan(v, e);
			chkmin(low[u], low[v]);
		} else chkmin(low[u], dfn[v]);
	}
	// cout << u << ' ' << dfn[u] << ' ' << low[u] << '\n';
	if (dfn[u] == low[u]) {
		ans.emplace_back(std::vector<i32>(1, u));
		auto& ecc = ans.back();
		while (stk[top] != u) ecc.emplace_back(stk[top--]); 
		--top;
	}
}

int main() {
    std::ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	i32 n, m;
	cin >> n >> m;
	for (i32 i = 1; i <= m; ++ i) {
		i32 x, y;
		cin >> x >> y;
		add(x, y);
	}
	
	for (i32 i = 1; i <= n; ++ i) if (!dfn[i]) tarjan(i, null);
	
	cout << ans.size() << '\n';
	
	for (const auto& vec : ans) {
		cout << vec.size() << ' ';
		for (const auto& nod : vec) cout << nod << ' ';
		cout << '\n';	
	}

    return 0;
}