#include <iostream>
#include <climits>
#include <bitset>

#define N 1145141

using namespace std;

int max(int a, int b) {
    return (a>b?a:b);
}

void dfs(int nod, int fa);
void add(int a, int b);

struct edge {
    int u,v;
    edge* nex;
} graph[N];

edge* tot = graph;
edge* fir[N];
bitset<N> st;
int n;
int tin1, tin2;
int ans;
int f[N][2];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    
    for (int i = 1; i < n; ++ i) {
        cin >> tin1 >> tin2;
        add(tin1,tin2);
        add(tin2,tin1);
    }

    dfs(1, 0);

    cout << ans << endl;

    return 0;
}

void dfs(int nod, int fa) {
    f[nod][0] = 1;
    // st[nod] = 1;
    int to;

    for (edge *i = fir[nod]; i != NULL; i = i->nex) {
        to = i->v;
        // if (st[to]) continue;
        if (to == fa) continue;
        dfs(to, nod);
        if (f[nod][0] < f[to][0] + 1) {
            f[nod][1] = f[nod][0];
            f[nod][0] = f[to][0] + 1;
        } else {
            f[nod][1] = max(f[nod][1], f[to][0] + 1);
        }
        // f[nod][1] = max(f[nod][1], f[to][1]+1);
    }
    ans = max(ans, f[nod][1] + f[nod][0]);
}

void add(int a, int b) {
    ++ tot;
    tot->u = a;
    tot->v = b;
    tot->nex = fir[a];
    fir[a] = tot;
}