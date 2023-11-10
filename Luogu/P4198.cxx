#include <iostream>

using std::cin;
using std::cout;

#define N 100001

using i32 = int;
using i64 = long long;

struct Node {
    Node *lc, *rc;
    i32 mx, cnt;

    i32 l, r, mid;

    void init(i32 L, i32 R) {
        l = mx = L, r = R, mid = (L + R) >> 1;
    }
} stree[N << 1];

i32 h[N];

Node *tot = stree, *null = stree, *root;

void build(Node* nod, i32 l, i32 r) {
    nod->init(l, r);
    if (l == r)
        nod->lc = nod->rc = null;
    else {
        nod->lc = ++tot;
        build(nod->lc, l, nod->mid);
        nod->rc = ++tot;
        build(nod->rc, nod->mid + 1, r);
    }
}

inline bool gt(int p1, int p2) {  // s[p1] is greater than s[p2]
    if (!p2) return h[p1];
    return 1ll * h[p1] * p2 > 1ll * h[p2] * p1;
}

i32 calc(Node* nod, i32 pre) {
    if (nod->l == nod->r)
        return gt(nod->mx, pre);
    else if (gt(nod->lc->mx, pre))
        return calc(nod->lc, pre) + nod->cnt;
    else
        return calc(nod->rc, pre);
}

void modify(Node* nod, i32 pos) {
    if (nod->l == nod->r) return;
    if (pos <= nod->mid)
        modify(nod->lc, pos);
    else
        modify(nod->rc, pos);

    nod->mx = gt(nod->rc->mx, nod->lc->mx) ? nod->rc->mx : nod->lc->mx;
    nod->cnt = calc(nod->rc, nod->lc->mx);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, m;

    cin >> n >> m;

    root = ++tot;
    build(tot, 1, n);
    h[0] = 1;

    while (m--) {
        i32 x, y;
        cin >> x >> y;
        h[x] = y;
        modify(root, x);
        // cout << "MODED\n";
        cout << calc(root, 0) << '\n';
        // cout << root->cnt << '\n';
    }

    return 0;
}