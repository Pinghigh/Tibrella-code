#include <algorithm>
#include <iostream>

#define lc(u) (u << 1)
#define rc(u) (u << 1 | 1)
#define ptr(u) (stree + (u))

using std::cin;
using std::cout;
using std::max;
using std::min;

using i32 = int;

const i32 null = -0x3f3f3f3f;

#define N 50005

struct Node {
    i32 l, r, mid;
    i32 lmx, rmx, sum, mx;
    i32 tag;

    void init(i32 L, i32 R) {
        l = L, r = R;
        mid = (l + r) >> 1;
        tag = null;
    }

    void assign(i32 v) {
        lmx = rmx = mx = sum = v;
    }
} stree[N << 2];

i32 a[N];

void push_up(i32 u) {
    Node *nod = ptr(u), *lc = ptr(lc(u)), *rc = ptr(rc(u));
    nod->lmx = max(lc->lmx, lc->sum + rc->lmx);
    nod->rmx = max(rc->rmx, rc->sum + lc->rmx);
    nod->mx = max({ lc->mx, rc->mx, rc->lmx + lc->rmx });
    nod->sum = lc->sum + rc->sum;
}

void build(i32 u, i32 l, i32 r) {
    Node* nod = ptr(u);
    nod->init(l, r);
    if (l == r) {
        nod->assign(a[l]);
    } else {
        build(lc(u), l, nod->mid);
        build(rc(u), nod->mid + 1, r);
        push_up(u);
    }
}

void modify(i32 u, i32 pos, i32 v) {
    Node* nod = ptr(u);
    if (nod->l == nod->r) {
        nod->assign(v);
    } else {
        if (pos > nod->mid)
            modify(rc(u), pos, v);
        else
            modify(lc(u), pos, v);
        push_up(u);
    }
}

Node operator+(Node a, Node b) {
    Node res;
    Node *nod = &res, *lc = &a, *rc = &b;
    nod->init(lc->l, rc->r);
    nod->lmx = max(lc->lmx, lc->sum + rc->lmx);
    nod->rmx = max(rc->rmx, rc->sum + lc->rmx);
    nod->mx = max({ lc->mx, rc->mx, rc->lmx + lc->rmx });
    nod->sum = lc->sum + rc->sum;
    return res;
}

Node query(i32 u, i32 l, i32 r) {
    Node* nod = ptr(u);
    if (l == nod->l && r == nod->r) {
        return *nod;
    } else {
        if (l > nod->mid)
            return query(rc(u), l, r);
        else if (r <= nod->mid)
            return query(lc(u), l, r);
        else
            return query(lc(u), l, nod->mid) + query(rc(u), nod->mid + 1, r);
    }
}

i32 n, m;
i32 t1, t2, t3;

int main() {
    cin >> n;
    for (i32 i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, 1, n);

    cin >> m;
    while (m--) {
        cin >> t1 >> t2 >> t3;
        if (t1) {
            cout << query(1, t2, t3).mx << '\n';
        } else {
            modify(1, t2, t3);
        }
    }

    return 0;
}