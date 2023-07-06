#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

#define N 1000006

using i32 = int;
using i64 = long long;

i32 n, m;
i32 a[N];

struct Node {
    Node *lc, *rc;
    i32 val;
    i32 l, r, mid;

    void init(i32 L, i32 R) {
        l = L, r = R;
        mid = (l + r) >> 1;
    }
} tree[N << 5], *root[N];
Node* tot = tree - 1;
i32 ver = -1;

Node* build(i32 l, i32 r) {
    Node* nod = ++tot;
    nod->init(l, r);
    if (l == r)
        nod->val = a[l];
    else {
        nod->lc = build(l, nod->mid);
        nod->rc = build(nod->mid + 1, r);
    }
    return nod;
}

Node* modify(Node* pre, i32 l, i32 r, i32 pos, i32 val) {
    Node* nod = ++tot;
    nod->init(l, r);
    if (l == r)
        nod->val = val;
    else if (pos <= nod->mid) {
        nod->lc = modify(pre->lc, l, nod->mid, pos, val);
        nod->rc = pre->rc;
    } else {
        nod->lc = pre->lc;
        nod->rc = modify(pre->rc, nod->mid + 1, r, pos, val);
    }
    return nod;
}

i32 query(Node* nod, i32 pos) {
    if (nod->l == nod->r)
        return nod->val;
    else if (pos <= nod->mid)
        return query(nod->lc, pos);
    else
        return query(nod->rc, pos);
}

i32 v, op, pos, val;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i)
        cin >> a[i];
    root[++ver] = build(1, n);

    while (m--) {
        cin >> v >> op >> pos;
        if (!--op) {
            cin >> val;
            root[++ver] = modify(root[v], 1, n, pos, val);
        } else {
            cout << query(root[v], pos) << '\n';
            root[++ver] = root[v];
        }
    }

    return 0;
}