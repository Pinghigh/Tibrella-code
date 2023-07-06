#include <climits>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::queue;
using sint = short int;

#define N 250
#define M 50005
#define SEED 400
#define endl '\n'

sint a[N][N];
int m, n;
struct edge {
    edge *nex, *opp;
    int to, w;
} graph[M << 2];
int s, t;
edge *fir[M << 2], *cur[M << 2];
edge* tot = graph;
queue<int> q;
int depth[M << 2];
int wall[N][N][2];  // 记录一个空块最下（0）和最右（1）的墙旁边的空块，避免枚举空地时查找次数过多

auto min = [](auto x, auto y) { return x < y ? x : y; };

void add(int x, int y, int z) {
    tot->to = y;
    tot->w = z;
    tot->nex = fir[x];
    fir[x] = tot;
    tot->opp = tot + 1;
    ++tot;

    tot->to = x;
    tot->w = 0;
    tot->nex = fir[y];
    fir[y] = tot;
    tot->opp = tot - 1;
    ++tot;
}

int uni_xy(int x, int y) {
    return x * SEED + y;
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
                depth[e->to] = depth[idx] + 1;
                q.push(e->to);
                cur[e->to] = fir[e->to];
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

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(a, -1, sizeof a);

    cin >> m >> n;
    char ch;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> ch;
            a[i][j] = (ch == '*') ? 0 : 2;
        }
    }
    s = 0;
    t = (M << 1) + 10;

    // 四周加墙
    for (int i = 0; i <= m + 1; ++i) {
        a[i][0] = a[i][n + 1] = 2;
    }
    for (int i = 0; i <= n + 1; ++i) {
        a[0][i] = a[m + 1][i] = 2;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i][j] != 2) {
                int w = uni_xy(i, j);
                if (a[i + 1][j] == 2) {
                    add(s, w, 1);
                    // cout << i << ' ' << j << ' ' << w << endl;
                    for (int k = i; a[k][j] != 2; --k) {
                        wall[k][j][0] = w;
                    }
                }
                if (a[i][j + 1] == 2) {
                    add(w + M, t, 1);
                    for (int k = j; a[i][k] != 2; --k) {
                        wall[i][k][1] = w;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (!a[i][j]) {
                // cout << i << ' ' << j << ' ' << wall[i][j][0] / SEED << ' ' << wall[i][j][1]%SEED << endl;
                add(wall[i][j][0], wall[i][j][1] + M, 1);
                // add(wall[i][j][0], wall[i][j][0] + M, 1);
                // add(wall[i][j][1], wall[i][j][1] + M, 1);
            }
        }
    }

    cout << dinic() << endl;

    return 0;
}