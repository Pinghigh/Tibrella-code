#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

template <typename T>
static void chkmax(T& a, const T& b) {
    if (a < b) a = b;
}

template <typename T>
static void chkmin(T& a, const T& b) {
    if (a > b) a = b;
}

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 500001
#define M 2000001

struct edge {
    edge* nxt;
    i32 v;
} graph[M << 1], *fir[N];
edge* tot = graph;
std::list<std::vector<i32>> vdcc;

static void add(const i32& u, const i32& v) {
    *(tot) = { fir[u], v };
    fir[u] = tot++;
}

i32 dfn[N], low[N];
i32 stk[N];
i32 rt;

void tarjan(const i32& u, const i32& fa) {
    static i32 top = 0, tim = 0;

    dfn[stk[++top] = u] = low[u] = ++tim;

    if (u == rt && !fir[u]) return vdcc.emplace_back(std::vector<i32>(1, rt)), void();

    for (edge* e = fir[u]; e; e = e->nxt) {
        const i32& v = e->v;
        if (v == fa) continue;
        if (!dfn[v]) {
            tarjan(v, u);
            chkmin(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                vdcc.emplace_back(std::vector<i32>());
                auto &vec = vdcc.back();
                do vec.emplace_back(stk[top]); while(stk[top--] != v);
                vec.emplace_back(u);
            }
        } else chkmin(low[u], dfn[v]);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, m;
    cin >> n >> m;
    for (i32 i = 1; i <= m; ++i) {
        i32 u, v;
        cin >> u >> v;
        if (u != v)
            add(u, v), add(v, u);
    }

    for (i32 i = 1; i <= n; ++ i) if (!dfn[i]) tarjan(rt = i, 0);
    
    cout << vdcc.size() << '\n';
    for (const auto& vec : vdcc) {
        cout << vec.size() << ' ';
        for (const auto& u : vec) cout << u << ' ';
        cout << '\n';
    }

    return 0;
}