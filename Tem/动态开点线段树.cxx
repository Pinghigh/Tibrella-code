// 我去我动态开点模板怎么没了，重写一份

#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 100001

i64 a[N];

struct Node { 
    Node *lc, *rc;
    i64 sum, ltag, rtag;
    i32 l, r, mid;
    void push_down() {
        if (ltag && lc) lc->sum += (mid - l + 1) * ltag, lc->ltag += ltag, lc->rtag += ltag, ltag = 0;
        if (rtag && rc) rc->sum += (r - mid) * rtag, rc->ltag += rtag, rc->rtag += rtag, rtag = 0;
    }
    void push_up() {
        sum = 0;
        sum += lc?lc->sum:(a[mid]-a[l-1] + ltag * (mid - l + 1));
        sum += rc?rc->sum:(a[r]-a[mid] + rtag * (r - mid));
    }
    void init(const i32& L, const i32& R) {
        l = L; r = R; mid = (L + R) >> 1;
        sum = a[R] - a[L-1];
    }
} space[N << 1];
Node *tot = space, *root;

void modify(Node* nod, const i32& l, const i32& r, const i32& x) {
    if (l > nod->r || r < nod->l) return;
    else if (nod->l >= l && nod->r <= r) 
        nod->rtag += x, nod->ltag += x, nod->sum += (nod->r - nod->l + 1) * x; 
    else { 
        if (nod->mid >= l) {
            if (!nod->lc) (nod->lc = ++tot)->init(nod->l, nod->mid);
            nod->push_down();
            modify(nod->lc, l, r, x);
        }
        if (nod->mid < r) {
            if (!nod->rc) (nod->rc = ++tot)->init(nod->mid+1, nod->r);
            nod->push_down();
            modify(nod->rc, l, r, x);
        }   
        nod->push_up();
    }
}

i64 query(Node* nod, const i32& l, const i32& r) {
    // std::cerr << nod->l << ' ' << nod->mid << ' ' << nod->r << ' ' << l << ' ' << r << '\n';
    if (l > nod->r || r < nod->l) return 0;
    else if (nod->l >= l && nod->r <= r) return nod->sum;
    else { 
        i64 res = 0;
        if (nod->mid >= l) {
            if (!nod->lc) (nod->lc = ++tot)->init(nod->l, nod->mid);
            nod->push_down();
            res += query(nod->lc, l, r);
        }
        if (nod->mid < r) {
            if (!nod->rc) (nod->rc = ++tot)->init(nod->mid+1, nod->r);
            nod->push_down();
            res += query(nod->rc, l, r);
        }
        return res;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    i32 n, m;
    cin >> n >> m;
    for (i32 i = 1; i <= n; ++ i) {cin >> a[i]; a[i] += a[i-1];}
    (root = ++tot)->init(1, n);
    while (m--) {
        i32 op;
        cin >> op;
        if (op == 1) {
            i32 x, y, z;
            cin >> x >> y >> z;
            modify(root, x, y, z);
        } else {
            i32 x, y;
            cin >> x >> y;
            cout << query(root, x, y) << '\n';
        }
        // for (i32 i = 1; i <= n; ++ i) cout << query(root, i, i) << ' ';
        // cout << '\n';
    }

    return 0;
}