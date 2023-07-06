#include <algorithm>
#include <iostream>
#include <vector>

#define N 500005

const int mod = 201314;

using std::cin;
using std::cout;
using std::sort;
using std::swap;

const char endl = '\n';

struct edge {
    edge* nex;
    int to;
} graph[N], *fir[N];
edge* tot = graph;
void add(int a, int b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

int wson[N], siz[N], fa[N], dep[N];
void get_wson(int nod) {
    siz[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->to;
        dep[to] = dep[nod] + 1;
        get_wson(to);
        siz[nod] += siz[to];
        if (siz[wson[nod]] < siz[to]) wson[nod] = to;
    }
}

int dfn[N], tim, adfn[N], top[N];

void get_dfn(int nod, int hd) {
    dfn[nod] = ++tim;
    adfn[tim] = nod;
    top[nod] = hd;
    if (wson[nod]) get_dfn(wson[nod], hd);
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->to;
        if (to == wson[nod]) continue;
        get_dfn(to, to);
    }
}

struct Node {
    Node *lc, *rc;
    int l, r, mid;
    int sum, laz;

    void init(int L, int R) {
        l = L, r = R;
        mid = (l + r) >> 1;
    }

    void push_up() {
        sum = (lc->sum + rc->sum) % mod;
    }
} tree[N << 2];
Node *null, *tail = tree, *root;

void push_down(Node* nod) {
    if (nod->laz == 0) return;
    nod->lc->sum += (nod->lc->r - nod->lc->l + 1) * nod->laz;
    nod->rc->sum += (nod->rc->r - nod->rc->l + 1) * nod->laz;
    nod->rc->laz += nod->laz;  // 别写成 = 号了，这里懒标记是叠加
    nod->lc->laz += nod->laz;
    nod->laz = 0;
}

void build(Node* nod, int l, int r) {
    nod->init(l, r);
    if (l == r) {
        nod->lc = nod->rc = null;
    } else {
        nod->lc = ++tail;
        nod->rc = ++tail;
        build(nod->lc, nod->l, nod->mid);
        build(nod->rc, nod->mid + 1, nod->r);
        nod->push_up();
    }
}

void modify(Node* nod, int l, int r, int val) {
    if (nod->l == l && nod->r == r) {
        nod->sum += val * (r - l + 1) % mod;
        nod->sum %= mod;
        nod->laz += val;
        nod->laz %= mod;
    } else {
        push_down(nod);
        if (l >= nod->rc->l)
            modify(nod->rc, l, r, val);
        else if (r <= nod->lc->r)
            modify(nod->lc, l, r, val);
        else
            modify(nod->lc, l, nod->lc->r, val), modify(nod->rc, nod->rc->l, r, val);
        nod->push_up();
    }
}

int query(Node* nod, int l, int r) {
    push_down(nod);
    if (nod->l == l && nod->r == r) {
        return nod->sum % mod;
    } else {
        if (l >= nod->rc->l)
            return query(nod->rc, l, r);
        else if (r <= nod->lc->r)
            return query(nod->lc, l, r);
        else
            return (query(nod->lc, l, nod->lc->r) + query(nod->rc, nod->rc->l, r)) % mod;
    }
}

void mod_line(int x, int y, int val) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        modify(root, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if (dfn[x] < dfn[y]) swap(x, y);
    modify(root, dfn[y], dfn[x], val);
}

int qry_line(int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        res += query(root, dfn[top[x]], dfn[x]);
        res %= mod;
        x = fa[top[x]];
    }
    if (dfn[x] < dfn[y]) swap(x, y);
    res += query(root, dfn[y], dfn[x]);
    res %= mod;
    return res;
}

int n, m;
int t1, t2, t3;

int ans[N];

struct que {
    int id;
    int l, r, z;
    bool is_l;
};
std::vector<que> q;

int mr = 0;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    q.reserve((m + 1) << 1);

    for (int i = 2; i <= n; ++i) {
        cin >> fa[i];
        ++fa[i];
        add(fa[i], i);
    }

    null = tail;
    root = ++tail;
    null->lc = null->rc = null;
    get_wson(1);
    get_dfn(1, 1);

    build(root, 1, n);

    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t2 >> t3;
        ++t1, ++t2, ++t3;
        q.emplace_back((que){ i, 1, t1 - 1, t3, true });
        q.emplace_back((que){ i, 1, t2, t3, false });
    }
    sort(q.begin(), q.end(), [](que& a, que& b) { return a.r < b.r; });
    for (auto& a : q) {
        while (mr < a.r) {
            ++mr;
            mod_line(1, mr, 1);
        }
        int tmp = qry_line(1, a.z);
        if (a.is_l)
            ans[a.id] -= tmp;
        else
            ans[a.id] += tmp;
    }

    for (int i = 1; i <= m; ++i)
        cout << ans[i] % mod << endl;

    return 0;
}