#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using std::cin;
using std::cout;

#define N 10004

using i32 = int;
using i64 = long long;

struct tp {
    i32 x, y;
    i32 val;

    tp(i32 x, i32 y, i32 z):x(x),y(y),val(z){};
};

struct edge { 
    edge* nex;
    i32 to, val;
} graph[N], *fir[N];
edge* tot = graph;
void add(const i32&x, const i32&y, const i32&z) {
    tot->to = y, tot->val = z, tot->nex = fir[x];
    fir[x] = tot++;
}
std::vector<tp> krus;
i32 n, m;

namespace kruskal {
    i32 fa[N], siz[N];
    int find(const i32& a) {
        if (fa[a] != a) fa[a] = find(fa[a]);
        return fa[a];
    }
    bool merge(i32 x, i32 y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (siz[x] > siz[y]) 
            siz[x] += siz[y], fa[y] = x;
        else siz[y] += siz[x], fa[x] = y;
        return true;
    }
    bool in_one(const i32& x, const i32& y) {
        return find(x) == find(y);
    }
    void init() {
        for (i32 i = 1; i <= n; ++ i) siz[i] = 1, fa[i] = i;
    }
}

namespace hld { // Light-Heavy Decomposition
    i32 dfn[N], adfn[N], siz[N], dep[N], fa[N], top[N], wson[N], tim = 0;
    i32 er[N]; // edge right
    
    void get_wson(const i32& x, const i32& fa) {
        siz[x] = 1;
        hld::fa[x] = fa;
        for (edge* e = fir[x]; e; e = e->nex) {
            const i32& to = e->to;
            if (to != fa) {
                er[to] = e->val;
                dep[to] = dep[x] + 1;
                get_wson(to, x);
                siz[x] += siz[to];
                if (siz[to] > siz[wson[x]]) wson[x] = to;
            }
        }
    }

    void get_dfn(const i32& x, const i32& top) {
        dfn[x] = ++tim;
        adfn[tim] = x;
        // std::cerr << x << ' ' << tim << std::endl;
        hld::top[x] = top;
        if (wson[x]) {
            get_dfn(wson[x], top);
            for (edge* e = fir[x]; e; e = e->nex) {
                const i32& to = e->to;
                if (to != fa[x] && to != wson[x]) get_dfn(to, to);
            }
        }
    }
    template <typename T>
    T log2(const T& x) {
        return sizeof(T) * __CHAR_BIT__ - 1 - __builtin_clz(x);
    }

    namespace st {
        #define LG 25

        i32 st[LG][N];
        void init_st() {
            memset(st, 0x3f, sizeof st);
            for (i32 i = 1; i <= n; ++ i) st[0][i] = er[adfn[i]];
            for (i32 lg = 1; lg < LG; ++ lg) 
                for (i32 i = 1; i + (1<<lg) - 1 <= n; ++i)
                    st[lg][i] = std::min(st[lg-1][i], st[lg-1][i+(1<<(lg-1))]);
        }

        i32 query(const i32& l, const i32& r) {
            // cout << l << ' ' << r << '\n';
            if (r < l) {
                return 0x3f3f3f3f;
            }
            else {
                const i32& lg = log2(r-l+1);
                return std::min(st[lg][l], st[lg][r-(1<<lg)+1]);
            }
            
        }
    }

    i32 query(i32 x, i32 y) {
        i32 res = 0x3f3f3f3f;
        if (!kruskal::in_one(x, y)) return -1;
        while (top[x] != top[y]) {
            if (dep[top[x]]<dep[top[y]]) std::swap(x, y);
            // cout << x << ' ' << fa[top[x]] << ' ' << st::query(dfn[top[x]], dfn[x]) << '\n';
            res = std::min(res, st::query(dfn[top[x]], dfn[x]));
            x = fa[top[x]];
        }
        if (dep[x] < dep[y]) std::swap(x, y);
        // cout << x << ' ' << y << ' ' << st::query(dfn[y]+1, dfn[x]) << '\n';
        return std::min(res, st::query(dfn[y]+1, dfn[x]));
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i32 i = 1; i <= m; ++ i) {
        i32 x, y, z;
        cin >> x >> y >> z;
        krus.emplace_back(x,y,z);
    }
    kruskal::init();

    std::sort(krus.begin(), krus.end(), [](const auto& a, const auto& b)->bool {return a.val < b.val;});

    {
        i32 cnt = 0;
        while (cnt < n - 1 && krus.size()) {
            const auto& e = krus.back();
            if (kruskal::merge(e.x, e.y)) {
                ++cnt;
                add(e.x, e.y, e.val); add(e.y, e.x, e.val);            
                // cout << e.x << ' ' << e.y << ' ' << e.val << '\n';
            }
            krus.pop_back();
        }
    // std::cerr << cnt << std::endl;
    }

    // cout << hld::wson[1];
    // hld::get_wson(1,1);
    for (i32 i = 1; i <= n; ++ i) if (!hld::siz[i]) hld::get_wson(i, i);
    for (i32 i = 1; i <= n; ++ i) if (!hld::dfn[i]) hld::get_dfn(i, i);
    // for (i32 i = 1; i <= n; ++ i) cout << hld::dfn[i] << ' ';
    // hld::get_dfn(1, 1);

    hld::st::init_st();

    i32 q;
    cin >> q;
    while (q--) {
        i32 x, y;
        cin >> x >> y;
        cout << hld::query(x, y) << '\n';
    }

    return 0;
}