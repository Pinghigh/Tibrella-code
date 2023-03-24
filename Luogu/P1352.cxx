#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

#define N 6010

struct edge {
    int u,v;
    edge* nex=NULL;
} graph[N];

int n;
int hap[N];
int ind[N];
int f[N][2];
int tmp1, tmp2;
edge* fir[N];
edge* tail=graph;
int root;

void add(int a, int b);
void dfs(int nod);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    for (int i = 1; i <= n; ++ i) {
        cin >> hap[i];
    }
    for (int i = 1; i < n; ++ i) {
        cin >> tmp1 >> tmp2;
        add(tmp1,tmp2);
    }

    for (int i = 1; i <= n; i ++) {
        if (ind[i] == 0) {
            root=i;
            break;
        }
    }
    // cout << "[root] " << root << endl;
    dfs(root);
    cout << max(f[root][1], f[root][0]) << endl;

    return 0;
}

void add(int a, int b) {
    ++ tail;
    tail->u = b;
    tail->v = a;
    tail->nex = fir[b];
    fir[b] = tail;
    ++ ind[a]; 
    // cout << "[ADD] U: " << tail->u << " V: " << tail->v << endl;
}

void dfs(int nod) {
    f[nod][1] = hap[nod];
    f[nod][0] = 0;

    for (edge* i = fir[nod]; i != NULL; i = i->nex) {
        // cout << "[dfs] node: " << nod << endl;
        int tmp3 = i->v;
        dfs(tmp3);
        f[nod][0] += max(f[tmp3][1], f[tmp3][0]);
        f[nod][1] += f[tmp3][0];
        // cout << "[search] node " << tmp3 << " 不选 " << f[tmp3][0] << " 选" << f[tmp3][1] << endl;
        // cout << "[modify] node " << nod << " 不选 " << f[nod][0] << " 选" << f[nod][1] << endl;
    }
}