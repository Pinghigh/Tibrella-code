#include <iostream>
#include <string>

using llint = long long int;
using ullint = unsigned long long int;
using sint = short int;
using uint = unsigned int;
using ldouble = long double;

auto max = [](auto a, auto b) { return a > b ? a : b; };
auto min = [](auto a, auto b) { return a < b ? a : b; };

#define N 200001

struct edge {
    edge* nex;
    int to, val;
} graph[N << 1], *fir[N];
edge* tot = graph;
int val[N];
int f[N], s[N];
void add(int a, int b, int c) {
    tot->to = b;
    tot->nex = fir[a];
    tot->val = c;
    fir[a] = tot++;
}

int wson[N], siz[N], dep[N], he[N], fa[N];
void get_wson(int nod) {
    siz[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->to;
        if (to == fa[nod]) continue;
        fa[to] = nod;
        dep[to] = dep[nod] + 1;
        val[to] = e->val;
        get_wson(to);
        siz[nod] += siz[to];
        wson[nod] = (siz[to] > siz[wson[nod]]) ? to : wson[nod];
    }
}

int dfn[N], adfn[N], tim;
void get_dfn(int nod, int head) {
    dfn[nod] = ++tim;
    adfn[tim] = nod;
    he[nod] = head;
    if (wson[nod]) get_dfn(wson[nod], head);
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->to;
        if (to == wson[nod] || to == fa[nod]) continue;
        get_dfn(to, to);
    }
}

struct Node {
    Node *lc, *rc;
    int mx, mn, sum;
    int l, r, mid;
    bool opp;

    void init(int L, int R) {
        l = L, r = R;
        mid = (l + r) >> 1;
    }

    void rev() {
        opp ^= 1;
        std::swap(mn, mx);
        mx = -mx;
        mn = -mn;
        sum = -sum;
    }

    void assign(int v) {
        sum = mx = mn = v;
        opp = false;
    }

    void push_up() {
        mx = max(lc->mx, rc->mx);
        mn = min(lc->mn, rc->mn);
        sum = lc->sum + rc->sum;
    }

    void push_down() {
        if (opp) {
            lc->rev();
            rc->rev();
            opp = false;
        }
    }
} stree[N << 2], *tail, *null, *root;

void build(Node* nod, int l, int r) {
    nod->init(l, r);
    if (l == r) {
        nod->assign(val[adfn[l]]);
        nod->lc = nod->rc = null;
    } else {
        nod->lc = ++tail;
        nod->rc = ++tail;
        build(nod->lc, nod->l, nod->mid);
        build(nod->rc, nod->mid + 1, nod->r);
        nod->push_up();
    }
}

void assign(Node* nod, int p, int v) {
    if (nod->l == nod->r) {
        nod->assign(v);
    } else {
        nod->push_down();
        if (nod->lc->r < p)
            assign(nod->rc, p, v);
        else
            assign(nod->lc, p, v);
        nod->push_up();
    }
}

void oppose(Node* nod, int l, int r) {
    nod->push_down();
    if (nod->l == l && nod->r == r) {
        nod->rev();
    } else {
        if (nod->lc->r >= r)
            oppose(nod->lc, l, r);
        else if (nod->rc->l <= l)
            oppose(nod->rc, l, r);
        else
            oppose(nod->lc, l, nod->lc->r), oppose(nod->rc, nod->rc->l, r);
        nod->push_up();
    }
}

int query_sum(Node* nod, int l, int r) {
    nod->push_down();
    if (nod->l == l && nod->r == r) {
        return nod->sum;
    } else {
        if (nod->lc->r >= r)
            return query_sum(nod->lc, l, r);
        else if (nod->rc->l <= l)
            return query_sum(nod->rc, l, r);
        else
            return query_sum(nod->lc, l, nod->lc->r) + query_sum(nod->rc, nod->rc->l, r);
        nod->push_up(); 
    }
}

int query_min(Node* nod, int l, int r) {
    nod->push_down();
    if (nod->l == l && nod->r == r) {
        return nod->mn;
    } else {
        if (nod->lc->r >= r)
            return query_min(nod->lc, l, r);
        else if (nod->rc->l <= l)
            return query_min(nod->rc, l, r);
        else
            return min(query_min(nod->lc, l, nod->lc->r), query_min(nod->rc, nod->rc->l, r));
        nod->push_up();
    }
}

int query_max(Node* nod, int l, int r) {
    nod->push_down();
    if (nod->l == l && nod->r == r) {
        return nod->mx;
    } else {
        if (nod->lc->r >= r)
            return query_max(nod->lc, l, r);
        else if (nod->rc->l <= l)
            return query_max(nod->rc, l, r);
        else
            return max(query_max(nod->lc, l, nod->lc->r), query_max(nod->rc, nod->rc->l, r));
        nod->push_up();
    }
}

using std::cin;
using std::cout;
using std::swap;

void oppo_line(int x, int y) {
    while (he[x] != he[y]) {
        if (dep[he[x]] < dep[he[y]]) swap(x, y);
        oppose(root, dfn[he[x]], dfn[x]);
        x = fa[he[x]];
    }
    if (dfn[x] < dfn[y]) swap(x, y);
    if (x != y) oppose(root, dfn[y] + 1, dfn[x]);
}

int query_sum_line(int x, int y) {
    int res = 0;
    while (he[x] != he[y]) {
        if (dep[he[x]] < dep[he[y]]) swap(x, y);
        res += query_sum(root, dfn[he[x]], dfn[x]);
        x = fa[he[x]];
    }
    if (dfn[x] < dfn[y]) swap(x, y);
    if (x != y) res += query_sum(root, dfn[y] + 1, dfn[x]);
    return res;
}

int query_min_line(int x, int y) {
    int res = 114514191;
    while (he[x] != he[y]) {
        if (dep[he[x]] < dep[he[y]]) swap(x, y);
        res = min(res, query_min(root, dfn[he[x]], dfn[x]));
        x = fa[he[x]];
    }
    if (dfn[x] < dfn[y]) swap(x, y);
    if (x != y) res = min(res, query_min(root, dfn[y] + 1, dfn[x]));
    return res;
}

int query_max_line(int x, int y) {
    int res = -114514191;
    while (he[x] != he[y]) {
        if (dep[he[x]] < dep[he[y]]) swap(x, y);
        res = max(res, query_max(root, dfn[he[x]], dfn[x]));
        x = fa[he[x]];
    }
    if (dfn[x] < dfn[y]) swap(x, y);
    if (x != y) res = max(res, query_max(root, dfn[y] + 1, dfn[x]));
    return res;
}

std::string beh;
int n;
int t1, t2, t3;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    tail = stree;
    null = tail;
    null->lc = null->rc = tail;
    root = ++tail;
    null->mn = 0x3f3f3f3f;
    null->mx = -0x3f3f3f3f;

    cin >> n;
    for (int i = 1; i < n; ++i) {
        cin >> t1 >> t2 >> t3;
        ++t1, ++t2;
        f[i] = t1;
        s[i] = t2;
        add(t1, t2, t3);
        add(t2, t1, t3);
    }

    get_wson(1);
    get_dfn(1, 0);
    build(root, 1, n);
    for (int i = 1; i < n; ++i)
        if (dep[f[i]] > dep[s[i]]) swap(f[i], s[i]);

    cin >> n;
    while (n--) {
        null->mn = 0x3f3f3f3f3f3f3f3f;
        null->mx = -0x3f3f3f3f3f3f3f3f;
        cin >> beh;
        cin >> t1 >> t2;
        ++t1, ++t2;
        if (beh == "SUM") {
            cout << query_sum_line(t1, t2) << '\n';
        } else if (beh == "MAX") {
            cout << query_max_line(t1, t2) << '\n';
        } else if (beh == "MIN") {
            cout << query_min_line(t1, t2) << '\n';
        } else if (beh == "C") {
            --t2;--t1;
            assign(root, dfn[s[t1]], t2);
        } else {
            oppo_line(t1, t2);
        }
    }

    return 0;
}