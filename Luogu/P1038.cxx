#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 110;
constexpr int M = N * N;

struct edge {
    int u, v;
    edge* nex;
    int w;
} graph[M];

edge* fir[N];
edge* tot = graph;
int n, p;
bool flag;
int u[N];
int c[N];
queue<int> q;
int ind[N];
int t1, t2, t3;
int nod;
int oud[N];

void add(int u, int v, int w) {
    ++tot;
    tot->u = u;
    tot->v = v;
    tot->w = w;
    tot->nex = fir[u];
    fir[u] = tot;
    ++ind[v];
    ++oud[u];
}

int main() {
    cin >> n >> p;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i] >> u[i];
        if (c[i]) {
            u[i] = 0;
            q.push(i);
        }
        c[i] -= u[i];
    }
    for (int i = 1; i <= p; ++i) {
        cin >> t1 >> t2 >> t3;
        add(t1, t2, t3);
    }

    while (!q.empty()) {
        nod = q.front();
        q.pop();
        for (edge* e = fir[nod]; e; e = e->nex) {
            --ind[e->v];
            if (ind[e->v] == 0) {
                q.push(e->v);
            }
            if (c[nod] > 0) {
                c[e->v] += ((e->w) * c[nod]);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (oud[i] == 0 && c[i] > 0) {
            flag = 1;
            cout << i << ' ' << c[i] << endl;
        }
    }
    if (!flag) cout << "NULL" << endl;
    return 0;
}