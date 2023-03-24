#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::lower_bound;
using std::queue;
using std::vector;

#define endl '\n'
#define N 200
#define P 50000

struct edge {
    edge *nex, *opp;
    int to, w;
    short int flag;
} graph[N * N * 2 + P * 2];
edge *fir[N * 2 + P * 2], *cur[N * 2 + P * 2];
edge* tot = graph;
int s, t;
int depth[N * 2 + P * 2];
int nxt[N * 2 + P * 2];
queue<int> q;
auto min = [](auto a, auto b) { return a < b ? a : b; };

void add(int a, int b, int c) {
    ++tot;
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
}

bool bfs() {
    while (q.size())
        q.pop();
    memset(depth, 0, sizeof depth);

    cur[s] = fir[s];
    depth[s] = 1;
    q.push(s);
    while (q.size()) {
        int idx = q.front();
        q.pop();
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (!depth[e->to] && e->w) {
                q.push(e->to);
                cur[e->to] = fir[e->to];
                depth[e->to] = depth[idx] + 1;
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
        if (depth[e->to] == depth[nod] + 1 && e->w) {
            int d = dfs(e->to, min(val, e->w));
            if (d > 0) {
                e->w -= d;
                e->opp->w += d;
                nxt[nod] = e->to - P;  // 还原成正常点
                return d;
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

int n;
int ans;
vector<int> sqa(1);

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    s = 0;
    t = n + P + P + 1;
    for (int i = 1; i <= 7000; ++i) {
        sqa.push_back(i * i);
    }
    int now = 1;  // 添加的点数
    for (;;) {
        int pipw = lower_bound(sqa.begin() + 1, sqa.end(), now) - sqa.begin();
        add(s, now, 1);
        add(now + P, t, 1);
        for (int j = 2 * pipw; j > 0; --j) {
            int k = sqa[j] - now;  // 找差值
            if (k < now && k > 0) {
                add(k, now + P, 1);
            }
        }
        ans += dinic();
        if (now - ans > n) break;
        ++now;
    }
    cout << now - 1 << endl;
    for (edge* e = fir[t]; e; e = e->nex) {
        if (e->opp->w) {
            int p = e->to - P;
            if (p == now) continue;
            while (p) {
                cout << p << ' ';
                p = nxt[p];
            }
            cout << endl;
        }
    }

    return 0;
}