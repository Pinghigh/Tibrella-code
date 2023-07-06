#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::sort;
using std::unique;
using std::vector;

#define endl '\n'

const long long N = 100005;

long long n;
struct Segment {
    long long x, top, bottom;

    long long k;
    bool operator<(const Segment& _exa) const {
        return x < _exa.x;
    }
} seg[2 * N];

struct Node {
    long long l, r, mid;
    long long cnt;
    long long len;
    Node *lc, *rc;

    void init(long long L, long long R) {
        l = L;
        r = R;
        mid = l + r >> 1;
    }
} tree[8 * N];
Node* idx = tree;
Node* null = idx;
vector<int> ycoor(N);

long long find(long long y) {
    return lower_bound(ycoor.begin(), ycoor.end(), y) - ycoor.begin();
}

void push_up(Node* nod) {
    if (nod->cnt)
        nod->len = ycoor[nod->r + 1] - ycoor[nod->l];
    else if (nod->l != nod->r) {
        nod->len = nod->lc->len + nod->rc->len;
    } else {
        nod->len = 0;
    }
}

void build(Node* nod, long long L, long long R) {
    nod->init(L, R);
    if (L == R) {
        nod->lc = nod->rc = null;
    } else {
        nod->lc = ++idx;
        nod->rc = ++idx;
        build(nod->lc, nod->l, nod->mid);
        build(nod->rc, nod->mid + 1, nod->r);
    }
}

void modify(Node* nod, long long L, long long R, long long x) {
    if (nod->l >= L && nod->r <= R) {
        nod->cnt += x;
        push_up(nod);
    } else {
        if (L <= nod->mid) modify(nod->lc, L, R, x);
        if (R > nod->mid) modify(nod->rc, L, R, x);
        push_up(nod);
    }
}

long long res;

int main() {
    null->lc = null->rc = null;
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (long long i = 0, j = 0; i < n; ++i) {
        long long t1, t2, t3, t4;  // x1,y1,x2,y2
        cin >> t1 >> t2 >> t3 >> t4;
        seg[j++] = { t1, t2, t4, 1 };
        seg[j++] = { t3, t2, t4, -1 };
        ycoor.push_back(t2);
        ycoor.push_back(t4);
    }

    sort(ycoor.begin(), ycoor.end());
    ycoor.erase(unique(ycoor.begin(), ycoor.end()), ycoor.end());

    build(++idx, 0, ycoor.size() - 2);  // 区间个数 = 点数 - 1

    sort(seg, seg + n * 2);

    res = 0;
    for (long long i = 0; i < n * 2; ++i) {
        if (i > 0) res += tree[1].len * (seg[i].x - seg[i - 1].x);
        modify(tree + 1, find(seg[i].top), find(seg[i].bottom) - 1, seg[i].k);  // 存的是区间而不是点，左闭右开，因此 - 1
    }
    cout << res << endl;

    return 0;
}
