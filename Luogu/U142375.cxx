#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>

using std::min;
using std::max;
using std::cin;
using std::cout;
using std::endl;

#define N 114514

void add(int a, int b);
void dfs(int nod);

struct edge {
    int u,v;
    edge* nex;
} graph[N];

edge* fir[N];
edge* tot = graph;
int ans;
int mn[N], mx[N]; // 以 i 为根的子树中最大编号以及最小编号
int size[N]; // 以 i 为根节点的子树的节点数
int ind[N]; // 入度
int n;
int root;
int tmp1, tmp2; // 输入

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i < n; ++ i) {
        cin >> tmp1 >> tmp2;
        add(tmp1, tmp2);
    }

    for (int i = 1; i <= n; ++ i) {
        if (!ind[i]) {
            root = i;
            break;
        }    
    }

    dfs(root);

    cout << ans;

    return 0;
}

void add(int a, int b) {
    ++ tot;
    tot->u = a;
    tot->v = b;
    tot->nex = fir[a];
    fir[a] = tot;
    ++ind[b];
}

void dfs(int nod) {
    ++ size[nod];
    mn[nod] = mx[nod] = nod;
    int to;
    for (edge *i = fir[nod]; i; i = i->nex) {
        to = i->v;
        dfs(to);
        size[nod] += size[to];
        mx[nod] = max(mx[nod], mx[to]);
        mn[nod] = min(mn[nod], mn[to]);
    }
    if (mx[nod] - mn[nod] + 1 == size[nod]) {
        ++ ans;
        // cout << "[SUC] " << nod << endl;
    }
}