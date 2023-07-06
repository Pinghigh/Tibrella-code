#include <iostream>

using std::cin;
using std::cout;
#define N 1000514
#define int long long
#define endl '\n'
#define KOGASA 

struct Node {
    int u, v;
    Node *lc, *rc;
    int l, r, mid;
    int lazy;
    void init(int a, int b) {
        l = a;
        r = b;
        mid = l + r >> 1;
    }
} tr[N * 4];

int n, m;
int x, y, k;
int ori[N];      // 原数列
char beh;        // 操作
int t1, t2, t3;  // 输入缓存
Node* tail = tr;

void push_up(Node* nod) {
    nod->v = nod->lc->v + nod->rc->v;
}

void build(Node* nod, int L, int R) {
    nod->init(L, R);
    if (L == R) {  // 边界回溯
        nod->lc = nod->rc = tr;
        nod->v = ori[L];
    } else {
        nod->lc = ++tail;
        nod->rc = ++tail;

        build(nod->lc, L, nod->mid);
        build(nod->rc, nod->mid + 1, R);
        push_up(nod);
    }
}

void push_down(Node* nod) {
    if (nod->lazy == 0) return;
    nod->lc->v += (nod->lc->r - nod->lc->l + 1) * nod->lazy;
    nod->rc->v += (nod->rc->r - nod->rc->l + 1) * nod->lazy;
    nod->rc->lazy += nod->lazy; // 别写成 = 号了，这里懒标记是叠加
    nod->lc->lazy += nod->lazy;
    nod->lazy = 0;
}

void modify(Node* nod, int L, int R, int v) {6
    if (L == nod->l && R == nod->r) {
        nod->lazy += v;
        nod->v += (nod->r - nod->l + 1) * v;
    } else {
        push_down(nod);
        if (nod->lc->r >= R) {
            modify(nod->lc, L, R, v);
        } else if (nod->rc->l <= L) {
            modify(nod->rc, L, R, v);
        } else {
            modify(nod->lc, L, nod->lc->r, v);
            modify(nod->rc, nod->rc->l, R, v);
        }
        push_up(nod);
    }
}

int query(Node* nod, int L, int R) {
    push_down(nod);
    if (L == nod->l && R == nod->r) {
        return nod->v;
    } else {
        if (nod->lc->r >= R) {
            return KOGASA query(nod->lc, L, R);
        } else if (nod->rc->l <= L) {
            return query(nod->rc, L, R);
        } else {
            return query(nod->lc, L, nod->lc->r) + query(nod->rc, nod->rc->l, R);
        }
    }
}

signed main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> ori[i];
    }
    build(++tail, 1, n);
    while (m--) {
        cin >> beh;
        if (beh == '1') {
            cin >> t1 >> t2 >> t3;
            modify(tr + 1, t1, t2, t3);
        } else {
            cin >> t1 >> t2;
            cout << query(tr + 1, t1, t2) << endl;
        }
    }

    return 0;
}