#include <iostream>

using std::cin;
using std::cout;

#define N 400005

using i32 = int;

#define get_pointer(u) Node *nod = stree + u, *lc = stree + lc(u), *rc = stree + rc(u)
#define lc(u) ((u) << 1)
#define rc(u) ((u) << 1 | 1)

i32 tmp;
void swap(i32& a, i32& b) {
    tmp = a;
    a = b;
    b = tmp;
}
bool chkmin(i32& a, i32 b) {
    return (b < a ? (a = b, true) : false);
}
bool chkmax(i32& a, i32 b) {
    return (b > a ? (a = b, true) : false);
}

i32 n, a[N];

struct Node {
    i32 l, r, mid;
    i32 sum;
    i32 lmx, rmx, mx;
    i32 lmxpos, rmxpos, mxposl, mxposr;
    i32 lmn, rmn, mn;
    i32 lmnpos, rmnpos, mnposl, mnposr;
    bool tag;

    void init(i32 L, i32 R) {
        l = L, r = R;
        mid = (l + r) >> 1;
        tag = 0;
    }

    void assign(i32 val) {
        sum = lmx = rmx = mx = lmn = rmn = mn = val;
        lmxpos = rmxpos = mxposl = mxposr = lmnpos = rmnpos = mnposl = mnposr = l;
        tag = 0;
    }

    void upd() {
        tag ^= 1;
        swap(lmn, lmx);
        swap(rmn, rmx);
        swap(mn, mx);
        swap(lmnpos, lmxpos);
        swap(rmnpos, rmxpos);
        swap(mnposl, mxposl);
        swap(mnposr, mxposr);
        sum = -sum;
        lmn = -lmn, rmn = -rmn, mn = -mn;
        lmx = -lmx, rmx = -rmx, mx = -mx;
    }

} stree[N << 2];

Node operator+(Node a, Node b) {
    Node res;
    Node *nod = &res, *lc = &a, *rc = &b;

    if (!a.mxposl) cout << a.l << ' ' << a.r << ' ' << a.lmx << '\n';

    nod->init(lc->l, rc->r);
    nod->sum = lc->sum + rc->sum;
    nod->lmx = lc->lmx, nod->lmxpos = lc->lmxpos;
    nod->rmx = rc->rmx, nod->rmxpos = rc->rmxpos;
    nod->lmn = lc->lmn, nod->lmnpos = lc->lmnpos;
    nod->rmn = rc->rmn, nod->rmnpos = rc->rmnpos;

    if (chkmax(nod->lmx, lc->sum + rc->lmx)) nod->lmxpos = rc->lmxpos;
    if (chkmin(nod->lmn, lc->sum + rc->lmn)) nod->lmnpos = rc->lmnpos;

    if (chkmax(nod->rmx, lc->rmx + rc->sum)) nod->rmxpos = lc->rmxpos;
    if (chkmin(nod->rmn, lc->rmn + rc->sum)) nod->rmnpos = lc->rmnpos;

    nod->mx = lc->mx, nod->mxposl = lc->mxposl, nod->mxposr = lc->mxposr;
    if (chkmax(nod->mx, rc->mx)) nod->mxposl = rc->mxposl, nod->mxposr = rc->mxposr;
    if (chkmax(nod->mx, lc->rmx + rc->lmx)) nod->mxposl = lc->rmxpos, nod->mxposr = rc->lmxpos;

    nod->mn = lc->mn, nod->mnposl = lc->mnposl, nod->mnposr = lc->mnposr;
    if (chkmin(nod->mn, rc->mn)) nod->mnposl = rc->mnposl, nod->mnposr = rc->mnposr;
    if (chkmin(nod->mn, lc->rmn + rc->lmn)) nod->mnposl = lc->rmnpos, nod->mnposr = rc->lmnpos;

    // cout << res.mx << '\n';

    return res;
}

void push_up(i32 u) {
    // stree[u] = stree[lc(u)] + stree[rc(u)];

    get_pointer(u);  // 指针辅助修改，用途是得到当前节点、左右儿子的一共三个指针，这样码量小

    nod->sum = lc->sum + rc->sum;
    nod->lmx = lc->lmx, nod->lmxpos = lc->lmxpos;  // 初始值为左儿子 lmx
    nod->rmx = rc->rmx, nod->rmxpos = rc->rmxpos;
    nod->lmn = lc->lmn, nod->lmnpos = lc->lmnpos;
    nod->rmn = rc->rmn, nod->rmnpos = rc->rmnpos;

    if (chkmax(nod->lmx, lc->sum + rc->lmx)) nod->lmxpos = rc->lmxpos;
    if (chkmin(nod->lmn, lc->sum + rc->lmn)) nod->lmnpos = rc->lmnpos;

    if (chkmax(nod->rmx, lc->rmx + rc->sum)) nod->rmxpos = lc->rmxpos;
    if (chkmin(nod->rmn, lc->rmn + rc->sum)) nod->rmnpos = lc->rmnpos;

    nod->mx = lc->mx, nod->mxposl = lc->mxposl, nod->mxposr = lc->mxposr;
    if (chkmax(nod->mx, rc->mx)) nod->mxposl = rc->mxposl, nod->mxposr = rc->mxposr;
    if (chkmax(nod->mx, lc->rmx + rc->lmx)) nod->mxposl = lc->rmxpos, nod->mxposr = rc->lmxpos;

    nod->mn = lc->mn, nod->mnposl = lc->mnposl, nod->mnposr = lc->mnposr;
    if (chkmin(nod->mn, rc->mn)) nod->mnposl = rc->mnposl, nod->mnposr = rc->mnposr;
    if (chkmin(nod->mn, lc->rmn + rc->lmn)) nod->mnposl = lc->rmnpos, nod->mnposr = rc->lmnpos;

    // cout << nod->mx << '\n';
}

inline void push_down(i32 u) {
    if ((stree + u)->tag) {
        (stree + lc(u))->upd(), (stree + rc(u))->upd();
        (stree + u)->tag = 0;
    }
}

void build(i32 u, i32 l, i32 r) {
    Node* nod = stree + u;
    nod->init(l, r);
    if (l == r)
        nod->assign(a[l]);
    else {
        build(lc(u), l, nod->mid);
        build(rc(u), nod->mid + 1, r);
        push_up(u);
    }
}

void modify(i32 u, i32 pos, i32 val) {
    Node* nod = stree + u;
    push_down(u);
    if (nod->l == nod->r && nod->l == pos)
        nod->assign(val);
    else {
        modify(nod->mid < pos ? rc(u) : lc(u), pos, val);
        push_up(u);
    }
}

void reverse(i32 u, i32 l, i32 r) {
    Node* nod = stree + u;
    push_down(u);
    // cout << u << std::endl;
    if (nod->l == l && nod->r == r) {
        nod->upd();
    } else {
        if (nod->mid >= r)
            reverse(lc(u), l, r);
        else if (nod->mid < l)
            reverse(rc(u), l, r);
        else
            reverse(lc(u), l, nod->mid), reverse(rc(u), nod->mid + 1, r);
        push_up(u);
    }
}

Node query(i32 u, i32 l, i32 r) {
    Node* nod = stree + u;
    if (nod->l == l && nod->r == r) {
        return *nod;
    } else {
        push_down(u);
        if (nod->mid >= r)
            return query(lc(u), l, r);
        else if (nod->mid < l)
            return query(rc(u), l, r);
        else
            return query(lc(u), l, nod->mid) + query(rc(u), nod->mid + 1, r);
    }
}

i32 lstk[25], rstk[25], top;
i32 m, t1, t2, t3;
char op;
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, 1, n);

    cin >> m;

    while (m--) {
        cin >> op >> t1 >> t2;
        op -= '0';
        if (op) {
            cin >> t3;
            i32 res = 0;
            while (t3--) {
                Node nod = query(1, t1, t2);
                if (nod.mx <= 0 || !nod.mxposl || !nod.mxposr) break;
                reverse(1, nod.mxposl, nod.mxposr);
                res += nod.mx;
                ++top;
                lstk[top] = nod.mxposl, rstk[top] = nod.mxposr;
            }
            cout << res << std::endl;
            while (top) {
                reverse(1, lstk[top], rstk[top]);
                --top;
            }
        } else {
            modify(1, t1, t2);
        }
    }

    return 0;
}
