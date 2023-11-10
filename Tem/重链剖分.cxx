#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::swap;

const int N = 100005;

int n, m, r, p;

struct edge {
    edge* nex;
    int fr, to;
} graph[N << 2];
edge *fir[N], *tot = graph;
int rig[N];
void add(int a, int b) {
    tot->fr = a;
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot;
    ++tot;
}

int siz[N], wson[N];
int depth[N];
int fa[N];

void init(int nod) {  // 统计重儿子
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
int he[N];  // 链头

void get_dfn(int nod, int head) {
    dfn[nod] = ++tim;
    adfn[tim] = nod;
    he[nod] = head;

    if (wson[nod]) get_dfn(wson[nod], head);

    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == wson[nod] || e->to == fa[nod]) continue;

        get_dfn(e->to, e->to);  // 每一个轻链的链头,都是自己,而且重儿子的开头都是轻链.
    }
}

struct Node {
    Node *lc, *rc;
    int l, r;
    int mid;
    int lazy;
    int u, val;

    void init(int L, int R) {
        l = L;
        r = R;
        mid = (l + r) >> 1;
    }
    void push_up() {
        val = (lc->val + rc->val) % p;
    }
    void push_down() {
        if (!lazy) return;
        (lc->val += lazy * (lc->r - lc->l + 1) % p) %= p;
        (rc->val += lazy * (rc->r - rc->l + 1) % p) %= p;
        (lc->lazy += lazy) %= p;
        (rc->lazy += lazy) %= p;
        lazy = 0;
    }
} stree[N << 2], *null, *root;

Node* tail = stree;

void build(Node* nod, int L, int R) {
    nod->init(L, R);
    if (L == R) {
        nod->lc = nod->rc = null;
        nod->val = rig[adfn[L]] % p;
    } else {
        nod->lc = ++tail;
        nod->rc = ++tail;

        build(nod->lc, nod->l, nod->mid);
        build(nod->rc, nod->mid + 1, nod->r);
        nod->push_up();
    }
}

void modify(Node* nod, int L, int R, int v) {
    if (L == nod->l && R == nod->r) {
        (nod->lazy += v) %= p;
        (nod->val += v * (nod->r - nod->l + 1) % p) %= p;
    } else {
        nod->push_down();
        if (nod->lc->r >= R)
            modify(nod->lc, L, R, v);
        else if (nod->rc->l <= L)
            modify(nod->rc, L, R, v);
        else {
            modify(nod->lc, L, nod->lc->r, v);
            modify(nod->rc, nod->rc->l, R, v);
        }
        nod->push_up();
    }
}

int query(Node* nod, int L, int R) {
    nod->push_down();
    if (L == nod->l && R == nod->r) {
        return nod->val;
    } else {
        if (nod->lc->r >= R)
            return query(nod->lc, L, R);
        else if (nod->rc->l <= L)
            return query(nod->rc, L, R);
        else
            return query(nod->lc, L, nod->lc->r) + query(nod->rc, nod->rc->l, R);
    }
}

int qline(int a, int b) {
    int res = 0;
    while (he[a] != he[b]) {
        if (depth[he[a]] < depth[he[b]]) swap(a, b);
        res += query(root, dfn[he[a]], dfn[a]);  // 访问这条重链,dfn[he[a]]是链头,dfn[a]是当前节点
        res %= p;
        a = fa[he[a]];
    }
    if (dfn[a] < dfn[b]) swap(a, b);  // 保证a深度比b深度,深.保证后面查询l<r
    res += query(root, dfn[b], dfn[a]);
    res %= p;
    return res;
}

void mline(int a, int b, int v) {
    while (he[a] != he[b]) {
        if (depth[he[a]] < depth[he[b]]) swap(a, b);  // 要求 a 是深度较大节点
        modify(root, dfn[he[a]], dfn[a], v);
        a = fa[he[a]];
    }
    if (dfn[a] < dfn[b]) swap(a, b);
    modify(root, dfn[b], dfn[a], v);
}

int x, y, z;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    null = stree;
    root = ++tail;
    null->lc = null->rc = null;

    cin >> n >> m >> r >> p;

    for (int i = 1; i <= n; ++i)
        cin >> rig[i];

    for (int i = 1; i < n; ++i) {
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }

    init(r);
    get_dfn(r, r);
    build(root, 1, n);

    int beh;
    while (m--) {
        cin >> beh;
        if (beh == 1) {
            cin >> x >> y >> z;
            mline(x, y, z);
        } else if (beh == 2) {
            cin >> x >> y;
            cout << qline(x, y) % p << '\n';
        } else if (beh == 3) {
            cin >> x >> z;
            modify(root, dfn[x], dfn[x] + siz[x] - 1, z);
        } else {
            cin >> x;
            cout << query(root, dfn[x], dfn[x] + siz[x] - 1) % p<< '\n';
        }
    }

    return 0;
}