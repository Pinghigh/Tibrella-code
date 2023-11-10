#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using std::cin;
using std::cout;

#define all(x) x.begin(), x.end()
#define lsh(x) sort(all(x)); x.erase(std::unique(all(x)), x.end())

using i32 = int;
using i64 = long long;

#define N 200001

bool eq[N];
i32 a[N], b[N];

i32 fa[N << 1], siz[N << 1];

i32 find(const i32& x) {
    if (fa[x] != fa[fa[x]]) return fa[x] = find(fa[x]);
    return fa[x];
}

static void merge(i32 x, i32 y) {
    x = find(x); y = find(y);
    if (x != y) {
        if (siz[x] > siz[y]) fa[y] = x, siz[x] += siz[y];
        else fa[x] = y, siz[y] += siz[x];
    }
}

static void solve() {
    i32 n;
    cin >> n;
    static std::vector<i32> vec;
    vec.clear();
    for (i32 i = 1; i <= n; ++ i) {
        cin >> a[i] >> b[i] >> eq[i];
        vec.emplace_back(a[i]); vec.emplace_back(b[i]);
    }
    static std::vector<i32> eeq, neq;
    neq.clear(); eeq.clear();
    lsh(vec);
    for (i32 i = 1; i <= n; ++ i) {
        a[i] = std::lower_bound(all(vec), a[i]) - vec.begin() + 1;
        b[i] = std::lower_bound(all(vec), b[i]) - vec.begin() + 1;
        (eq[i]?eeq:neq).emplace_back(i);
        // cout << a[i] << ' ' << b[i] << '\n';
    }
    const size_t& V = vec.size();
    // cout << V << '\n';
    for (i32 i = 1; i <= V; ++ i) fa[i] = i, siz[i] = 1;
    for (const auto& q : eeq) merge(a[q], b[q]);
    for (const auto& q : neq) 
        if (find(a[q]) == find(b[q])) return (cout << "NO\n"), void();
        
    cout << "YES\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 t;
    cin >> t;
    while (t--) solve();

    return 0;
}