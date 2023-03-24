#include <iostream>

#pragma GCC target ("bmi,bmi2")

using std::cin;
using std::cout;
#define endl '\n'

#define N 50514

template <typename type>
type max(type a, type b) {
    return (a>b?a:b);
}

struct Node {
    Node * lc;
    Node * rc;
    int mx; // 区间最长连续空房数量
    int len; // 区间长度
    int lmx, rmx; // 从左/右端点开始的最长空房数量、
    int lazy;
    int l,r,mid;
} tree[N*4];

Node* tot = tree;
int n,m;
int ltmp;
int beh;
int x,y;

void build(Node* nod, int L, int R) {
    nod->l = L;
    nod->r = R;
    if (L == R) {
        nod->mx = nod->lmx = nod->rmx = nod->len = 1;
        nod->mid = L;
        nod->lc = nod->rc = tree; // 防止空指针报错，指向一个不用的节点
        return ;
    }
    nod->mid = L + R >> 1;
    nod->len = R - L + 1;
    nod->lc = ++ tot;
    nod->rc = ++ tot;
    nod->mx = nod->lmx = nod->rmx = nod->len;
    build(nod->lc, L, nod->mid);
    build(nod->rc, nod->mid+1, R);
}

void push_up(Node* nod) {
    nod->lmx = (nod->lc->rmx == nod->lc->len) ? nod->lc->len + nod->rc->lmx : nod->lc->lmx;
    nod->rmx = (nod->rc->lmx == nod->rc->len) ? nod->rc->len + nod->lc->rmx : nod->rc->rmx;
    nod->mx = max(max(nod->lc->mx, nod->rc->mx), nod->lc->rmx + nod->rc->lmx);
}

void push_down(Node* nod) {
    if (!nod->lazy) return ;
    nod->lc->lazy = nod->rc->lazy = nod->lazy;
    if (nod->lazy == 1) {
        nod->rc->mx = nod->rc->lmx = nod->rc->rmx = nod->rc->len;
        nod->lc->mx = nod->lc->lmx = nod->lc->rmx = nod->lc->len;
    } else {
        nod->rc->mx = nod->rc->lmx = nod->rc->rmx = 0;
        nod->lc->mx = nod->lc->lmx = nod->lc->rmx = 0;
    }
    nod->lazy = 0;
}

void modify(Node* nod, int L, int R, int tag) {
    push_down(nod);
    if (L <= nod->l && nod->r <= R) {
        if (tag == 1) {
            nod->mx = nod->lmx = nod->rmx = nod->len;
        } else {
            nod->mx = nod->lmx = nod->rmx = 0;
        }
        nod->lazy = tag;
        return;
    }
    if (L <= nod->mid) {
        modify(nod->lc, L, R, tag);
    }
    if (R > nod->mid) {
        modify(nod->rc, L, R, tag);
    }

    push_up(nod);
}

int query(Node* nod, int len) {
    push_down(nod);
    if (nod->len == 1) {
        return nod->l;
    }

    if (nod->lc->mx >= len) {
        return query(nod->lc, len);
    } else if (nod->lc->rmx + nod->rc->lmx >= len) {
        return nod->mid - nod->lc->rmx + 1;
    } else if (nod->rc->mx >= len) {
        return query(nod->rc, len);
    } else {
        return 0;
    }
}



int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    build(++tot, 1, n);   
    while (m --) {
        cin >> beh >> x;
        if (beh == 1) {
            ltmp = query(tree+1,x);
            cout << ltmp << endl;
            if (ltmp) modify(tree+1, ltmp, ltmp+x-1, 2);
        } else {
            cin >> y;
            modify(tree+1, x, x+y-1, 1);
        }
    }

    return 0;
}