#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>

using std::bitset;
using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::priority_queue;
using std::vector;

#define N 55
#define K 55
#define M 1005

struct edge {
    int fr, to;
    edge* nex;
    int val;
} graph[M * K * 4];

bitset<N * K> st;
edge* fir[N * K * 2];
edge* tot = graph;
int dist[N * K * 2];
int t1, t2, t3;
auto comp = [](pair<int, int> a, pair<int, int> b) { return a.second > b.second; };
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(comp);

auto add = [](int a, int b, int c) {
    ++tot;
    tot->fr = a;
    tot->to = b;
    tot->val = c;
    tot->nex = fir[a];
    fir[a] = tot;
};
auto min = [](auto& a, auto& b) { return a < b ? a : b; };

#define endl '\n'
int n, m, k;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        cin >> t1 >> t2 >> t3;
        // cout << t1 << ' ' << t2 << ' ' << t3 << endl;
        // add(t1, t2, t3);
        // add(t2, t1, t3);
        // for (int j = 1; j <= k; ++j) {
        //     add(t1 + (j - 1) * n, t2 + j * n, t3 / 2);
        //     add(t1 + j * n, t2 + (j - 1) * n, t3 / 2);
        //     add(t1 + j * n, t2 + j * n, t3);
        //     add(t2 + j * n, t1 + j * n, t3);
        //     // cout << t1 + (j - 1) * n << ' ' << t2 + j * n << ' ' << t3 / 2 << endl;
        // }
        for (int j = 0; j <= k; ++j) {
            add(t1 + j * n, t2 + j * n, t3);
            add(t2 + j * n, t1 + j * n, t3);
        }
        for (int j = 0; j < k; ++j) {
            add(t1 + j * n, t2 + (j + 1) * n, t3 / 2);
            add(t2 + j * n, t1 + (j + 1) * n, t3 / 2);
        }
    }

    memset(dist, 0x3f, sizeof dist);
    q.push(make_pair(1, 0));
    dist[1] = 0;
    int idx;
    while (!q.empty()) {
        // cout << "---" << q.top().first << ' ' << q.top().second << ' ' << dist[q.top().first] << endl;
        idx = q.top().first;
        q.pop();
        if (st[idx]) continue;
        st[idx] = 1;
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (dist[e->to] > dist[idx] + e->val) {
                dist[e->to] = dist[idx] + e->val;
                q.push(make_pair(e->to, dist[e->to]));
            }
            // cout << idx << ' ' << e->to << ' ' << dist[e->to] << ' ' << e->val << '\n';
        }
    }

    int res = 0x3f3f3f3f;
    for (int i = 0; i <= k; ++i) {
        res = min(res, dist[n + i * n]);
    }
    cout << res << '\n';
    return 0;
}