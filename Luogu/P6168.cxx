#include <iostream>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;

using i32 = long long;
using i64 = long long;

#define N 400005

namespace dsu {
    i32 fa[N<<1], siz[N<<1];
    void init(const i32& n) {
        for (i32 i = 1; i <= n; ++ i) fa[i] = i, siz[i] = 1;
    }
    i32 find(const i32& a) {
        return (fa[a] == fa[fa[a]]) ? fa[a] : (fa[a] = find(fa[a]));
    }
    static void merge(i32 x, i32 y) {
        x = find(x); y = find(y);
        if (x != y) {
            if (siz[x] < siz[y]) fa[x] = y, siz[y] += siz[x];
            else fa[y] = x, siz[x] += siz[y];
        }
    }
}
using dsu::find;
using dsu::merge;

i32 s[N], t[N], d[N]; // s, t, diff

struct edge {
    i32 u, v, w;
    const bool operator<(const edge& b) const& {
        return w < b.w;
    }
    edge(const i32& a, const i32& b, const i32& c):u(a),v(b),w(c){}
};

#define all(x) x.begin(), x.end()

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, m;
    cin >> n >> m;
    ++n;
    s[n] = 0x3f3f3f3f3f3f3f3f;
    t[n] = 1;
    std::vector<i32> lsh;
    for (i32 i = 1; i < n; ++ i) {
        cin >> s[i] >> t[i];
        lsh.emplace_back(s[i]);
        lsh.emplace_back(t[i]);
    }
    lsh.emplace_back(s[n]), lsh.emplace_back(t[n]);
    std::sort(all(lsh));
    lsh.erase(std::unique(all(lsh)), lsh.end());
    dsu::init(lsh.size() + 3);
    for (i32 i = 1; i <= n; ++ i) {
        s[i] = std::lower_bound(all(lsh), s[i]) - lsh.begin() + 1;
        t[i] = std::lower_bound(all(lsh), t[i]) - lsh.begin() + 1;
        ++d[s[i]]; --d[t[i]];
        merge(s[i], t[i]);
    }
    i64 ans = 0;
    for (i32 i = 1; i <= lsh.size(); ++ i)
        d[i] += d[i-1];
    for (i32 i = 1; i <= lsh.size(); ++ i){ 
        if (d[i] != 0) {
            merge(i, i+1); // d[i] 不为 0 就需要连边
            if (d[i] > 0) ans += d[i] * (lsh[i] - lsh[i-1]);
        }
    }
    std::vector<edge> e;
    for (i32 i = 1; i < lsh.size(); ++ i) 
        if (find(i) != find(i + 1)) e.emplace_back(i, i+1, lsh[i] - lsh[i-1]);
    std::sort(all(e));
    for (const auto& [u, v, w] : e) {
        if (find(u) != find(v)) {
            merge(u, v);
            ans += w;
        }
    }
    cout << ans << '\n';

    return 0;
}