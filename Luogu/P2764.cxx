#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>

using std::bitset;
using std::cin;
using std::cout;
using std::queue;

#define endl '\n'
#define N 200
#define M 6514

struct edge {
    edge *nex, *opp;
    int to, w;
} graph[M * 2 + N * 4];

edge *fir[N * 4], *cur[N * 4];
edge* tot = graph;
int depth[N * 4];
int nxt[N];
bitset<N * 4> have_nxt;
queue<int> q;
int n, m, s, t;

void add(int a, int b, int c) {
    tot->to = b;
    tot->w = c;
    tot->nex = fir[a];
    fir[a] = tot;
    tot->opp = tot + 1;
    ++tot;

    tot->to = a;
    tot->w = 0;
    tot->nex = fir[b];
    fir[b] = tot;
    tot->opp = tot - 1;
    ++tot;
}

auto min = [](auto& a, auto& b) { return a < b ? a : b; };

bool bfs() {
    while (q.size())
        q.pop();
    memset(depth, 0, sizeof depth);
    q.push(s);
    depth[s] = 1;
    cur[s] = fir[s];
    while (q.size()) {
        int idx = q.front();
        q.pop();
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (!depth[e->to] && e->w) {
                depth[e->to] = depth[idx] + 1;
                cur[e->to] = fir[e->to];
                q.push(e->to);
            }
        }
    }
    if (depth[t])
        return true;
    else
        return false;
}

int dfs(int nod, int val) {
    if (nod == t) return val;
    for (edge* e = cur[nod]; e; e = e->nex) {
        cur[nod] = e;
        if (depth[nod] + 1 == depth[e->to] && e->w) {
            int d = dfs(e->to, min(e->w, val));
            if (d > 0) {
                e->w -= d;
                e->opp->w += d;
                nxt[nod] = e->to - n;  // 还原成正常点
                if (nod != s) have_nxt[nod] = 1;
                return d;
            }
        }
    }
    return 0;
}

int dinic() {
    int res = 0;
    while (bfs()) {
        while (int d = dfs(s, 0x3f3f3f3f)) {
            res += d;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t1, t2;
    cin >> n >> m;
    s = 0;
    t = n + n + 1;
    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        add(t1, t2 + n, 1);
    }
    for (int i = 1; i <= n; ++i) {
        add(s, i, 1);
        add(i + n, t, 1);
    }
    int res = dinic();
    for (edge* e = fir[t]; e; e = e->nex) {
        if (e->opp->w) {          // i 点到汇点反边的反边有残量（只会是一）说明没有点流向 i 点，即起点
            int nod = e->to - n;  // 还原成正常点
            while (nod) {
                cout << nod << ' ';
                nod = nxt[nod];
            }
            cout << endl;
        }
    }
    cout << n - res << endl;

    return 0;
}