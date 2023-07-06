#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>

#pragma GCC target("vx2,popcnt,lzcnt,fma,sse4.1,sse4.2,bmi,bmi2,abm,sse2,sse3,sse4,mmx")

using std::bitset;
using std::cin;
using std::cout;
using std::greater;
using std::make_pair;
using std::pair;
using std::priority_queue;
using std::vector;

constexpr int N = 1.5e5 + 514;
typedef pair<int, int> PII;

struct edge {
    int to;
    edge* nex;
    int val;
} graph[N * 2];

edge* fir[N];
edge* tot = graph;
int dist[N];
bitset<N> st;
priority_queue<PII, vector<PII>, greater<PII>> edge_heap;
int n, m, start; // 点数 边数 起点
int x, y, z; // 输入一个边：起点 终点 权值
int idx; // 当前点编号

void add(int from, int to, int val) {
    ++tot;
    tot->to = to;
    tot->val = val;
    tot->nex = fir[from];
    fir[from] = tot;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(dist, 0x3f, sizeof dist); // 一定要记得 memset，你一天下午连着打了两会板子每次都忘写

    cin >> n >> m >> start;
    while (m--) {
        cin >> x >> y >> z;
        add(x, y, z);
    }
    dist[start] = 0;
    edge_heap.push(make_pair(0,start));
    while (edge_heap.size()) {
        idx = edge_heap.top().second;
        edge_heap.pop();
        if (st[idx]) {
            continue;
        }
        st[idx] = 1;
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (dist[e->to] > e->val + dist[idx]) { // 不要想当然全都打成 dist 数组了...有一个是边权
                dist[e->to] = e->val + dist[idx];
                edge_heap.push(make_pair(dist[e->to],e->to));
            }
        }
    }

    for (int i = 1; i <= n; ++ i) {
        cout << dist[i] << ' ';
    }

    return 0;
}