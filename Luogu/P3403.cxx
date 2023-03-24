#include <bitset>
#include <cstring>
#include <iostream>
#include <queue>

using std::bitset;
using std::cin;
using std::cout;
using std::greater;
using std::make_pair;
using std::vector;

#define endl '\n'
#define N 100005
#define M 500005
#define PII std::pair<llint, llint>
#define llint long long

struct edge {
    edge* nex;
    llint to, val;
} graph[M];
bitset<N> st;
edge* fir[N];
llint dist[N];
edge* tot = graph;
std::priority_queue<PII, vector<PII>, greater<PII>> q;

auto add = [](llint a, llint b, llint c) {
    ++tot;
    tot->val = c;
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot;
};

llint h;
llint x, y, z;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> h >> x >> y >> z;

    // if (x == 1 || y == 1 || z == 1) {
    //     cout << h << endl;
    //     return 0;
    // }

    for (llint i = 0; i < x; ++i) {
        add(i, (i + y) % x, y);
        add(i, (i + z) % x, z);
    }

    q.push(make_pair(0, 0));
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 1;
    while (q.size()) {
        llint idx = q.top().second;
        q.pop();
        if (st[idx]) continue;
        st[idx] = 1;
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (dist[e->to] > dist[idx] + e->val) {
                dist[e->to] = dist[idx] + e->val;
                q.push(make_pair(dist[e->to], e->to));
            }
        }
    }

    llint res = 0;
    for (llint i = 0; i < x; ++i) {
        if (dist[i] <= h) res += ((h - dist[i]) / x + 1);
    }

    cout << res << endl;

    return 0;
}