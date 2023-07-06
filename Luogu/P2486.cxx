#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::swap;

#define N 100005
#define endl '\n'

struct edge {
    edge* nex;
    int fr, to;
} graph[N << 2];
edge *fir[N], *tot = graph;
void add(int a, int b) {
    tot->fr = a;
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

int siz[N], wson[N];
int depth[N];
int fa[N];

void init(int nod) {
    siz[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa[nod]) continue;
        depth[e->to] = depth[nod] + 1;
        fa[e->to] = nod;
        init(e->to);
        siz[nod] += siz[e->to];
        if (siz[e->to] > siz[wson[nod]]) {
            wson[nod] = e->to;
        }
    }
}

int dfn[N], adfn[N], tim;
int he[N];
int col[N];

void get_dfn(int nod, int head) {
    dfn[nod] = ++tim;
    adfn[tim] = nod;
    he[nod] = head;

    if (wson[nod]) get_dfn(wson[nod], head);

    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == wson[nod] || e->to == fa[nod]) continue;

        get_dfn(e->to, e->to);
    }
}

struct Node {
    Node *lc, *rc;
    int l, r;
    int mid;
    int sum, lazy;

    void init(int L, int R) {
        l = L, r = R;
        mid = (l + r) >> 1;
    }

    void push_up() {
        sum = lc->sum + rc->sum;
        if (col[lc->r] == col[rc->l]) --sum;
    }

    void push_down() {
        if (!lazy) return;
        lc->lazy = rc->lazy = col[lc->r] = col[rc->l] = lazy;
        lc->sum = rc->sum = 1;
        lazy = 0;
    }
} segtree[N << 2];
Node *tail = segtree, *root, *null;

void build(Node* nod, int L, int R) {
    nod->init(L, R);
    if (L == R) {
        nod->lc = nod->rc = null;
        nod->sum = 1;
    } else {
        nod->lc = ++tail;
        nod->rc = ++tail;

        build(nod->lc, nod->l, nod->mid);
        build(nod->rc, nod->mid + 1, nod->r);
        nod->push_up();
    }
}

void modify(Node* nod, int L, int R, int c) {
    if (L == nod->l && R == nod->r) {
        // cout << "[stree] " << adfn[nod->l] << ' ' << adfn[nod->r] << ' ' << c << endl;
        col[nod->l] = col[nod->r] = nod->lazy = c;

        nod->sum = 1;
    } else {
        nod->push_down();
        if (L >= nod->rc->l)
            modify(nod->rc, L, R, c);
        else if (R <= nod->lc->r)
            modify(nod->lc, L, R, c);
        else {
            modify(nod->lc, L, nod->lc->r, c);
            modify(nod->rc, nod->rc->l, R, c);
        }
        nod->push_up();
    }
}

int query(Node* nod, int L, int R) {
    nod->push_down();
    if (L == nod->l && R == nod->r) return nod->sum;
    int res = 0;
    if (L >= nod->rc->l)
        res = query(nod->rc, L, R);
    else if (R <= nod->lc->r)
        res = query(nod->lc, L, R);
    else {
        res = query(nod->lc, L, nod->lc->r) + query(nod->rc, nod->rc->l, R);
        if (col[nod->lc->r] == col[nod->rc->l]) --res;
    }
    return res;
}

void mod(int a, int b, int c) {
    while (he[a] != he[b]) {
        if (depth[he[a]] < depth[he[b]]) swap(a, b);
        modify(root, dfn[he[a]], dfn[a], c);
        // cout << "---" << he[a] <<' ' << a << endl;
        a = fa[he[a]];
    }
    if (dfn[a] < dfn[b]) swap(a, b);
    // cout << "---" << b <<' ' << a << endl;
    modify(root, dfn[b], dfn[a], c);
}

int answer(int a, int b) {
    int u = a, v = b;
    int res = 0;
    while (he[a] != he[b]) {
        if (depth[he[a]] < depth[he[b]]) swap(a, b);
        res += query(root, dfn[he[a]], dfn[a]);
        a = he[a];
        // if (col[dfn[a]] == col[dfn[fa[a]]]) --res;
        a = fa[a];
    }
    if (dfn[a] < dfn[b]) swap(a, b);
    res += query(root, dfn[b], dfn[a]);
    while (he[u] != he[v]) {
        if (depth[he[u]] < depth[he[v]]) swap(u, v);
        if (col[dfn[he[u]]] == col[dfn[fa[he[u]]]]) --res;
        u = fa[he[u]];
    }
    return res;
}

int n, m;
int t1, t2, t3;
int ori[N];
char op;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> ori[i];
    }
    for (int i = 1; i < n; ++i) {
        cin >> t1 >> t2;
        add(t1, t2);
        add(t2, t1);
    }

    init(1);
    get_dfn(1, 1);
    for (int i = 1; i <= n; ++i)
        col[i] = ori[adfn[i]];

    null = tail;
    root = ++tail;
    null->lc = null->rc = null;
    build(root, 1, n);

    while (m--) {
        cin >> op;
        if (op == 'Q') {
            cin >> t1 >> t2;
            cout << answer(t1, t2) << endl;
        } else {
            cin >> t1 >> t2 >> t3;
            // cout << "[mod] " << t1 << ' ' << t2 << ' ' << t3 << endl;
            mod(t1, t2, t3);
        }
    }

    // for (int i = 1; i <= n; ++ i) cout << col[i] << ' ';

    return 0;
}