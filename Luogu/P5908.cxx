#include <iostream>
#include <bitset>
#include <vector>
#include <queue>

using std::cin;
using std::cout;

#define N 100005

using i32 = int;
using i64 = long long;

std::vector<i32> g[N];
std::bitset<N> vis;
i32 dist[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, d;
    cin >> n >> d;
    for (i32 i = 1; i < n; ++i) {
        i32 x, y;
        cin >> x >> y;
        g[x].emplace_back(y),g[y].emplace_back(x);
    }

    std::queue<i32> q;
    q.emplace(1);
    while(!q.empty()) {
        i32 nod = q.front();
        vis[nod]=true;
        q.pop();
        if (dist[nod]<d)
        for (const auto& to : g[nod]) 
            if (!vis[to]) q.emplace(to), dist[to] = dist[nod]+1, vis[to] = true;
    }

    cout << vis.count() - 1;    

    return 0;
}