#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>

using namespace std;

#define N 15144

int min(int a, int b) { return (a > b ? b : a); }

void add(int a, int b);
void dfs(int nod);

struct edge {
    int u, v;
    edge* nex;
} graph[N];

edge* fir[N];
edge* tot = graph;
int ind[N];
int root;
int n;
int num, k, r;
int f[N][2];
bitset<N> st;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // memset(f, 0x3f, sizeof f);

    cin >> n;
    while (n--) {
        cin >> num >> k;
        while (k--) {
            cin >> r;
            add(num, r);
            add(r, num);
        }
    }

    dfs(0);

    cout << min(f[0][0], f[0][1]);

    return 0;
}

void dfs(int nod) {
    int to;
    if (st[nod]) return;
    st[nod] = 1;
    f[nod][1] = 1;

    for (edge* i = fir[nod]; i != NULL; i = i->nex) {
        to = i->v;
        if (st[to]) continue;
        dfs(to);
        f[nod][1] += min(f[to][0], f[to][1]);
        f[nod][0] += f[to][1];
    }
}

void add(int a, int b) {
    ++tot;
    ++ind[b];
    tot->u = a;
    tot->v = b;
    tot->nex = fir[a];
    fir[a] = tot;
    // cout << "[ADD] u:" << a << " v: " << b << endl;
}