#include <iostream>
#include <climits>

using namespace std;

int max(int a, int b) {
    return (a>b?a:b);
}

#define N 16110

struct edge {
    int u,v;
    edge* nex;
} graph[N];

edge* fir[N];
edge* tot = graph;
int ind[N];
int f[N]; // f[i] 以 i 根的树的最大和 
int n;
int root;
int tin1, tin2;
int ans = INT_MIN;

void add(int a, int b);
void dfs(int nod);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        cin >> f[i];
    }
    for (int i = 1; i < n; ++ i) {
        cin >> tin1 >> tin2;
        add(tin1,tin2);
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

void dfs(int nod) {
    int to;
    for (edge *i = fir[nod]; i != NULL; i = i->nex) {
        to = i->v;
        dfs(to);
        f[nod] += max(0,f[to]);
        ans = max(ans, f[nod]);
        // cout << "[search] node " << to << f[to] << endl;
    }
}

void add(int a, int b) {
    // cout << "[ADD] u:" << a << " v: " << b << endl; 
    ++ tot;
    tot->u = b;
    tot->v = a;
    ++ ind[a];
    tot->nex = fir[b];
    fir[b] = tot;
}