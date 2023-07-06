#include <bitset>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>

template <typename T>
void read(T& x) {
    x = 0;
    static char ch;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

using std::bitset;
using std::queue;

#define endl '\n'
#define N 75005
#define E N

queue<int> q;
struct edge {
    int to, w;
    edge *opp, *nex;
} graph[E];
edge *fir[N], *cur[N], *tot = graph;
int depth[N];
bitset<N> iden;
bitset<N> back;
int T, n;
int s, t;
int t1;
auto min = [](int a, int b) { return a < b ? a : b; };

void add(int a, int b, int c) {
    ++tot;
    tot->to = b;
    tot->w = c;
    tot->nex = fir[a];
    tot->opp = tot + 1;
    fir[a] = tot;

    ++tot;
    tot->to = a;
    tot->w = 0;
    tot->nex = fir[b];
    tot->opp = tot - 1;
    fir[b] = tot;
}

bool bfs() {
    while (q.size())
        q.pop();
    memset(depth, 0, sizeof depth);
    depth[s] = 1;
    q.push(s);
    cur[s] = fir[s];
    while (q.size()) {
        int idx = q.front();
        q.pop();
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (!depth[e->to] && e->w) {
                cur[e->to] = fir[e->to];
                depth[e->to] = depth[idx] + 1;
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
            int res = dfs(e->to, min(val, e->w));
            if (res > 0) {
                e->w -= res;
                e->opp->w += res;
                return res;
            }
        }
    }
    return 0;
}

int dinic() {
    int res = 0;
    while (bfs()) {
        while (int d = dfs(s, INT_MAX)) {
            res += d;
        }
    }
    return res;
}

int cnt;

int main() {
    read(T);
    while (T--) {
        cnt = 0;
        tot = graph;
        memset(fir, 0, sizeof fir);
        read(n);
        s = (n << 1) + 1;
        t = (n << 1) + 2;
        iden.reset();
        back.reset();
        for (int i = 1; i <= n; ++i) {
            read(t1);
            iden[i] = t1;
        }
        for (int i = 1; i <= n; ++i) {
            read(t1);
            back[i] = t1 & 1;
            if (!iden[i]) back[i] = 0;
            if (!back[i]) ++cnt;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                read(t1);
                if (back[i]) continue;
                if (t1 || (i == j && iden[i])) add(i, j + n, 1);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (!back[i]) add(s, i, 1);
            if (iden[i]) add(i + n, t, 1);
        }

        // printf("%d", dinic());

        if (dinic() == cnt) {
            puts("^_^");
        } else {
            puts("T_T");
        }
    }

    return 0;
}