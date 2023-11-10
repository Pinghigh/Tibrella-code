#pragma GCC target("fma,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("Ofast")

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 200005

std::vector<i32> g[N];
std::vector<i32> len;
i32 mxdep[N];
i32 dson[N];
i32 fa[N];

i32 n, k;

#define all(a) a.begin(), a.end()

void add(i32 a, i32 b) {
    g[a].emplace_back(b), g[b].emplace_back(a);
}

void get_dson(const i32& nod, const i32& fat) {
    mxdep[nod] = 1;
    fa[nod] = fat;
    i32& son = dson[nod];
    for (const auto& to : g[nod]) {
        if (to != fat) {
            get_dson(to, nod);
            if (mxdep[to] > mxdep[son]) son = to;
        }
    }
    mxdep[nod] = mxdep[son] + 1;
}

void get_line(const i32& nod, const i32& tp) {
    if (dson[nod]) {
        get_line(dson[nod], tp);
        const i32 &son = dson[nod], fa = ::fa[nod];
        for (const auto& to : g[nod])
            if (son != to && fa != to) get_line(to, to);

    } else
        len.emplace_back(mxdep[tp]);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    {
        i32 t1, t2;
        for (i32 i = n; i > true; --i) {
            cin >> t1 >> t2;
            add(t1, t2);
        }
    }

    get_dson(1, 0);
    get_line(1, 1);

    std::sort(all(len), [](const i32& a, const i32& b) -> bool { return a > b; });

    i64 ans = -1145141919810;
    i32 left = n;
    for (i32 r = 1; r <= k; ++r) {
        if (r <= len.size()) left -= len[r - 1];
        i32 b = std::min(n >> 1, left);
        ans = std::max(ans, (n - r - b) * 1ll * (r - b));
    }

    cout << ans;

    return 0;
}