#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

#define N 1145
#define M 114514

struct edge {
    int u,v;
    // int w;
    int nex;
} graph[M];

int n,m;
int fir[N], tail;
int a[N];
int tmp1, tmp2;
int f[N];
int ind[N];

void add(int u,int v) {
    graph[++tail].v = v;
    graph[tail].u = u;
    graph[tail].nex = fir[u];
    fir[u] = tail;
    ind[v] ++;
}

void dfs(int nod) {
    f[nod] = INT_MAX;
    for (int i = fir[nod]; ~i; i =graph[i].nex) {
        tmp1 = graph[i].v;
        dfs(tmp1); // 通过 dfs 能得到以 v 为根的子树的结果
        f[nod] = min(f[nod],f[tmp1]+a[nod]);
    }
};

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; ++ i) {
        cin >> tmp1 >> tmp2;
        add(tmp1,tmp2);
    }

    for (int i = 1; i <= n; ++ i) {
        if (ind[i] == 0) {
            dfs(i);
        }
    }

    return 0;
}