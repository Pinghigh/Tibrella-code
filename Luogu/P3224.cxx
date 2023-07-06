#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define N 200005
#define Q 300005

/*

*
*   线段树部分
*

*/

struct Node {
    Node *lc, *rc;
    int l, r, mid;
    int siz;

    void init(int L, int R) {
        l = L;
        r = R;
        mid = l + r >> 1;
    }

    void push_up() {
        siz = lc->siz + rc->siz;
    }
} tree[N * 11];

Node* root[N];
Node* null = tree;
Node* tot = tree;

void add(Node*& nod, int l, int r, int x) {  // 显然此处只需要单点修改
    nod = ++tot;
    nod->lc = nod->rc = null;
    nod->init(l, r);
    if (l == r) {
        ++nod->siz;  // 记录大小，用于启发式合并（即较小树合并到大树上）
    } else {
        if (x <= nod->mid)
            add(nod->lc, nod->l, nod->mid, x);
        else
            add(nod->rc, nod->mid + 1, nod->r, x);
        nod->push_up();
    }
}

void merge(Node*& l, Node*& r) {  // 把 r 合并到 l 上
    if (l == null) {
        l = r;
        return;
    } else if (r == null)
        return;

    l->siz += r->siz;
    merge(l->lc, r->lc);
    merge(l->rc, r->rc);
}

int query(Node* nod, int kth) {
    if (nod->siz < kth) return -1;
    if (nod->l == nod->r) {
        return nod->l;
    }
    if (kth <= nod->lc->siz)
        return query(nod->lc, kth);
    else
        return query(nod->rc, kth - nod->lc->siz);
}

/*

*
* 并查集部分
*

*/

int fa[N], rk[N];

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void unity(int a, int b) {
    fa[find(b)] = find(a);
}

int n, m, q;
int t1, t2;
int id[N];
int fx, fy;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0)->tie(0);

    null->lc = null->rc = null;

    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> t1;
        id[t1] = i;
        fa[i] = i;
        root[i] = null;
        add(root[i], 1, n, t1);
    }

    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        fx = find(t1);
        fy = find(t2);
        if (fx == fy) continue;
        if (root[fx]->siz > root[fy]->siz)
            merge(root[fx], root[fy]);
        else
            merge(root[fx], root[fy]);
        unity(fx, fy);
    }

    char op;
    cin >> q;
    while (q--) {
        cin >> op >> t1 >> t2;
        if (op == 'B') {
            fx = find(t1);
            fy = find(t2);
            if (fx == fy) continue;
            if (root[fx]->siz > root[fy]->siz)
                merge(root[fx], root[fy]);
            else
                merge(root[fx], root[fy]);
            unity(fx, fy);
        } else {
            fx = find(t1);
            int res = query(root[fx], t2);
            cout << ((!~res) ? -1 : id[res]) << endl;
        }
    }

    return 0;
}