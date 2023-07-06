#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;

const int N = 50005, M = 100005, K = 12;

struct pair {
    int to;
    int dis;
};

struct comp {
    bool operator()(const pair& a, const pair& b) {
        return a.dis > b.dis;
    }
};

std::priority_queue<pair, std::vector<pair>, comp> q;
struct edge {
    edge* nex;
    int fr, to, w;
    bool up, ori;
} graph[M * K];
edge *fir[N * K], *tot = graph;
int dist[N * K];
std::bitset<N * K> vis;
std::bitset<N> st, nod;

int n, m, k, s, t;
int t1, t2, t3;

void add(int a, int b, int c) {
    if (a <= n && b <= n) tot->ori = true;
    tot->fr = a;
    tot->to = b;
    tot->w = c;
    tot->nex = fir[a];
    fir[a] = tot;
    ++tot;
}

void addb(int a, int b, int c) {
    if (a <= n && b <= n) tot->ori = true;
    tot->fr = a;
    tot->to = b;
    tot->w = c;
    tot->nex = fir[a];
    fir[a] = tot;
    tot->up = true;
    ++tot;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> k >> s >> t;
    // if (k) {
    //     cout << "-1" << '\n';
    //     return 0;
    // }
    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t2 >> t3;
        for (int j = 0; j <= k; ++j)
            add(t1 + j * n, t2 + j * n, t3);
    }
    for (int i = 1; i <= k; ++i) {
        cin >> t1;
        nod[t1] = 1;
    }
    for (edge* e = graph; e->to; ++e) {
        if (e->ori && nod[e->to]) {
            for (int j = 1; j <= k; ++j)
                addb(e->fr + n * (j - 1), e->to + n * j, e->w);
        }
    }

    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    q.push((pair){ s, 0 });
    while (q.size()) {
        int idx;
        idx = q.top().to;
        q.pop();
        if (vis[idx]) continue;
        st[idx % n] = true;
        vis[idx] = true;
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (e->up && st[e->to % n]) continue;
            if (dist[e->to] > dist[idx] + e->w) {
                dist[e->to] = dist[idx] + e->w;
                q.push((pair){ e->to, dist[e->to] });
            }
        }
    }

    cout << dist[t + k * n] << '\n';
    // for (int i = 0; i <= k; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         cout << dist[j + i * n] << ' ';
    //     }
    //     cout << '\n';
    // }

    return 0;
}