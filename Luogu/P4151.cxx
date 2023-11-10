#include <bitset>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

using u32 = unsigned int;
using u64 = unsigned long long;

#define N 50005
#define M 100005

struct edge {
    u32 to;
    u64 val;
};

std::vector<edge> g[N];

u32 n, m;
u64 t1, t2, t3;

void add(u32 fr, u32 to, u64 val) {
    g[fr].emplace_back((edge){ to, val });
    g[to].emplace_back((edge){ fr, val });
}

struct basis {
    u64 val[64];
    void insert(u64 x) {
        // cout << "INSERT " << x << '\n';
        for (u32 i = 63; ~i; --i)
            if ((1ll << i) & x) {
                if (val[i])
                    x ^= val[i];
                else
                    return val[i] = x, void();
            }
    }

    u64 qmax(u64 x) {
        for (u32 i = 63; ~i; --i)
            if (val[i] && !((1ll << i) & x)) x ^= val[i];
        return x;
    }
} bas;

std::bitset<N> vis;

u64 tmp;
u64 dis[N];

void dfs(u32 nod, u32 fa) {
    // std::cerr << nod << ' ' << tmp << '\n';
    vis[nod] = true;
    dis[nod] = tmp;
    for (const auto& e : g[nod]) {
        const u32& to = e.to;
        if (vis[to]) {
            if (to != fa) bas.insert(tmp ^ e.val ^ dis[to]);
        } else {
            tmp ^= e.val;
            dfs(to, nod);
            tmp ^= e.val;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        cin >> t1 >> t2 >> t3;
        add(t1, t2, t3);
    }
    dfs(1, 0);
    cout << bas.qmax(dis[n]);
    // cout << dis[n];

    return 0;
}