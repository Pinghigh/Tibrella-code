#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <vector>

using std::bitset;
using std::cin;
using std::cout;
using std::max;
using std::min;
using llint = long long int;
using ullint = unsigned long long int;
using sint = short int;

#define N 1005
#define M 505

struct edge {
    edge* nex;
    int to;
} graph[M];

edge *fir[N], *tot = graph;
std::vector<std::vector<int>> vcc(N);
int vcc_cnt;
int dfn[N], low[N];
int root, tim;
bitset<N> cut;
int stk[N], top;
int n, m;
int t1, t2;
ullint ans1, ans2;

void add(int a, int b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot;
    ++tot;
}

void init() {
    n = 0;
    cut.reset();
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(fir, 0, sizeof fir);
    tim = top = vcc_cnt = ans1 = 0;
    tot = graph;
    ans2 = 1;
    vcc.resize(N);
    for (auto& vec : vcc)
        vec.resize(0);
}

void tarjan(int nod) {
    dfn[nod] = low[nod] = ++tim;
    stk[++top] = nod;
    if (!fir[nod]) {
        vcc[vcc_cnt].emplace_back(nod);
        ++vcc_cnt;
        return;
    }
    int cnt = 0;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (!dfn[e->to]) {
            tarjan(e->to);
            low[nod] = min(low[nod], low[e->to]);
            if (dfn[nod] <= low[e->to]) {
                ++cnt;
                if (nod != root || cnt > 1) cut[nod] = 1;
                do {
                    vcc[vcc_cnt].emplace_back(stk[top]);
                } while (stk[top--] != e->to);
                vcc[vcc_cnt].emplace_back(nod);
                ++vcc_cnt;
            }
        } else {
            low[nod] = min(low[nod], dfn[e->to]);
        }
    }
}

int t;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while ((cin >> m), m) {
        init();
        for (int i = 1; i <= m; ++i) {
            cin >> t1 >> t2;
            add(t1, t2);
            add(t2, t1);
            n = max(max(t1, t2), n);
        }
        for (root = 1; root <= n; ++root) {
            if (!dfn[root]) tarjan(root);
        }
        vcc.resize(vcc_cnt);
        for (auto& vec : vcc) {
            // cout << vec.size() << ' ';
            int cut_cnt = 0;
            for (auto& i : vec) {
                if (cut[i]) ++cut_cnt;
                // cout << i << ' ' ;
            }
            // cout << '\n';
            if (!cut_cnt) {
                if (vec.size() > 1) {
                    ans1 += 2;
                    ans2 *= (vec.size() * (vec.size() - 1) / 2);
                } else {
                    ++ans1;
                }
            } else if (cut_cnt == 1) {
                ++ans1;
                ans2 *= (vec.size() - 1);  // 除了割点哪都能放
            }
        }
        // cout << '\n';
        // cout << vcc_cnt << ' ';
        cout << "Case " << ++t << ": " << ans1 << ' ' << ans2 << '\n';
    }

    return 0;
}