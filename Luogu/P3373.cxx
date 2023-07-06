#include <iostream>

using namespace std;

#define N 100015
#define ll long long

struct Node {
    ll v;
    Node *lc, *rc;
    int l, r, mid;
    ll a = 0, c = 1;  // 懒标记
    void init(int L, int R) {
        l = L;
        r = R;
        mid = (l + r) >> 1;
    }
} tr[N * 4];

int n, m;
int x, y, k;
ll ori[N];
int p;
char beh;
ll t1, t2, t3;
Node* tail = tr;

void push_up(Node* nod) {
    nod->v = (nod->lc->v % p + nod->rc->v % p) % p;
}

void build(Node* nod, int L, int R) {
    nod->init(L, R);
    if (L == R) {
        nod->v = ori[L] % p;
        nod->lc = nod->rc = tr;
        return;
    }
    nod->lc = ++tail;
    nod->rc = ++tail;
    build(nod->lc, L, nod->mid);
    build(nod->rc, nod->mid + 1, R);
    push_up(nod);
}

void push_down(Node* nod) {
    if (nod->a == 0 && nod->c == 1) return;
    if (nod->lc) {
        nod->lc->c = nod->lc->c % p * nod->c % p;
        nod->lc->a = nod->lc->a % p * nod->c % p;
        nod->lc->a = (nod->lc->a % p + nod->a % p) % p;
    }
    if (nod->rc) {
        nod->rc->c = nod->rc->c%p * nod->c % p;
        nod->rc->a = nod->rc->a%p * nod->c % p;
        nod->rc->a = (nod->rc->a%p + nod->a%p) % p;
    }
    nod->lc->v = (nod->lc->v%p * nod->c % p + (ll)(nod->lc->r - nod->lc->l + 1) % p * nod->a%p) % p;
    nod->rc->v = (nod->rc->v%p * nod->c % p + (ll)(nod->rc->r - nod->rc->l + 1) % p * nod->a%p) % p;
    nod->a = 0;
    nod->c = 1;
}

void modifya(Node* nod, int L, int R, ll v) {
    if (L == nod->l && R == nod->r) {
        nod->a += v;
        nod->a %= p;
        nod->v += (nod->r - nod->l + 1) * v % p;
        nod->v %= p;
    } else {
        push_down(nod);
        if (nod->lc->r >= R) {
            modifya(nod->lc, L, R, v % p);
        } else if (nod->rc->l <= L) {
            modifya(nod->rc, L, R, v % p);
        } else {
            modifya(nod->lc, L, nod->lc->r, v % p);
            modifya(nod->rc, nod->rc->l, R, v % p);
        }
        push_down(nod);
        push_up(nod);
    }
}

void modifyc(Node* nod, int L, int R, ll v) {
    if (L == nod->l && R == nod->r) {
        nod->c *= v;
        nod->c %=p;
        nod->a *= v;
        nod->a %= p;
        nod->v *= v;
        nod->v %= p;
    } else {
        push_down(nod);
        if (nod->lc->r >= R) {
            modifyc(nod->lc, L, R, v % p);
        } else if (nod->rc->l <= L) {
            modifyc(nod->rc, L, R, v % p);
        } else {
            modifyc(nod->lc, L, nod->lc->r, v % p);
            modifyc(nod->rc, nod->rc->l, R, v % p);
        }
        push_down(nod);
        push_up(nod);
    }
}

ll query(Node* nod, int L, int R) {
    push_down(nod);
    if (nod->r == R && nod->l == L) {
        return nod->v;
    }

    if (nod->lc->r >= R) {
        return query(nod->lc, L, R) % p;
    } else if (nod->rc->l <= L) {
        return query(nod->rc, L, R) % p;
    } else {
        return (query(nod->lc, L, nod->lc->r) % p + query(nod->rc, nod->rc->l, R) % p) % p;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> p;
    for (int i = 1; i <= n; ++i) {
        cin >> ori[i];
    }
    build(++tail, 1, n);
    while (m--) {
        cin >> beh;
        if (beh == '1') {
            cin >> t1 >> t2 >> t3;
            modifyc(tr + 1, t1, t2, t3 % p);
        } else if (beh == '3') {
            cin >> t1 >> t2;
            cout << query(tr + 1, t1, t2) % p << endl;
        } else {
            cin >> t1 >> t2 >> t3;
            modifya(tr + 1, t1, t2, t3 % p);
        }
    }

    return 0;
}