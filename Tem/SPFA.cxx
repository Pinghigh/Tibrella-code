#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#include <bitset>

using namespace std;

// 真·模板
template <class T>
T max(T a, T b) {
    return (a > b ? a : b);
}
template <class T>
T min(T a, T b) {
    return (a < b ? a : b);
}

#define M 514000
#define N 15140

struct edge {
    int u, v;
    int w;
    edge* nex;
} graph[M];

edge* fir[N];
edge* tot = graph;
int n, m, s;
int t1,t2,t3;
int dist[N];
queue<int> q;
bitset<N> st;

void add(int a, int b, int c) {
    ++tot;
    tot->u = a;
    tot->v = b;
    tot->w = c;
    tot->nex = fir[a];
    fir[a] = tot;
}

void spfa(int nod);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> s;
    for (int i = 0; i < m; ++i) {
        cin >> t1 >> t2 >> t3;
        add(t1,t2,t3); 
    }

    spfa(s);

    for (int i = 1; i <= n; ++ i) cout << dist[i] << ' ';

    return 0;
}

void spfa(int nod) {
    int to;
    st.reset();
    for (int i = 0; i <= n; ++ i) {
        dist[i] = INT_MAX;
    }

    dist[nod] = 0;
    q.push(nod);

    st[nod] = 1;

    while (!q.empty()) {
        nod = q.front();
        q.pop();
        st[nod] = 0;
        for (edge* i = fir[nod]; i; i = i->nex) {
            to = i->v;
            if (dist[nod] + i->w < dist[to]) {
                dist[to] = dist[nod] + i->w;
                if (st[to] == 0) {
                    q.push(to);
                    st[to] = 1;
                }
            }
        }
    }
}