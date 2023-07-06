#include <bitset>
#include <cstring>
#include <iostream>
#include <vector>

using std::bitset;
using std::cin;
using std::cout;
using std::vector;
using llint = long long int;

#define M 1000005
#define N 200005

llint min(llint& a, llint& b) {
    return a < b ? a : b;
};

const char endl = '\n';

struct edge {
    edge* nex;
    llint fr, to;
} graph[M];
edge *fir[N], *tot = graph;

void add(llint a, llint b) {
    tot->fr = a;
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot;
    ++tot;
}

llint n, m;
llint t1, t2;
llint res;

llint dfn[N], low[N], tim;
bitset<N> cut;
llint ecc_cnt;
llint stk[N], top;
llint root;
llint ans[N];
llint siz[N];

void tarjan(llint nod) {
    dfn[nod] = low[nod] = ++tim;  // tarjan 先打时间戳
    siz[nod] = 1;
    stk[++top] = nod;             // 然后入栈

    llint cnt = 0, sum = 0;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (!dfn[e->to]) {
            tarjan(e->to);
            low[nod] = min(low[nod], low[e->to]);
            siz[nod] += siz[e->to];
            if (dfn[nod] <= low[e->to]) {
                ++cnt;
                if (nod != root || cnt > 1) {
                    cut[nod] = 1;
                    sum += siz[e->to];
                    ans[nod] += (siz[e->to]) * (n - siz[e->to]);
                }
            }
        } else {
            low[nod] = min(dfn[e->to], low[nod]);
        }
    }

    if (cut[nod])
        ans[nod] += (n - sum - 1) * (sum + 1) + (n - 1);
    else
        ans[nod] += (n - 1) << 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    for (llint i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        add(t1, t2);
        add(t2, t1);
    }

    for (root = 1; root <= n; ++root)
        if (!dfn[root]) tarjan(root);

    // for (auto vec : ecc) {
    //     for (auto i : vec) {
    //         cout << i << ' ';
    //     }
    //     cout << endl;
    // }

    for (llint i = 1; i <= n; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}