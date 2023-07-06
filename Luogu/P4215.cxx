#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>

using std::cin;
using std::cout;
using std::list;

#define N 300005

using i32 = int;
using i64 = long long;

i64 a[N];

struct Node {
    Node *lc, *rc;
    i32 l, r, mid;
    i64 sum;
    list<i32> cover;

    void init(i32 L, i32 R) {
        l = L, r = R, mid = (L + R) >> 1;
    }
} stree[N << 2];

using np = Node*;

np tot = stree, null, root;

void build(np nod, i32 l, i32 r) {
    nod->init(l, r);
    if (l == r) {
        nod->sum = a[l];
        nod->lc = nod->rc = null;
    } else {
        nod->lc = ++tot;
        build(nod->lc, l, nod->mid);
        nod->rc = ++tot;
        build(nod->rc, nod->mid + 1, r);
        nod->sum = nod->lc->sum + nod->rc->sum;
    }
}

i32 cnt[N];

void sign(np nod, i32 l, i32 r, i32 id) {
    if (nod->l == l && nod->r == r) {
        ++cnt[id];
        nod->cover.emplace_back(id);
    } else {
        if (l > nod->mid) {
            sign(nod->rc, l, r, id);
        } else if (r <= nod->mid) {
            sign(nod->lc, l, r, id);
        } else {
            sign(nod->lc, l, nod->mid, id);
            sign(nod->rc, nod->mid + 1, r, id);
        }
    }
}

i32 las, ans;

void modify(np nod, i32 pos) {
    --nod->sum;
    if (!nod->sum && nod->cover.size()) {
        for (auto& i : nod->cover)
            if (!--cnt[i]) ++ans;
        nod->cover.clear();
    }
    if (nod->l != nod->r) {  // 非叶子
        if (pos > nod->mid)
            modify(nod->rc, pos);
        else
            modify(nod->lc, pos);
    }
}

i32 n, m;
i32 l, r;
i32 x, q;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    null = tot;
    null->lc = null->rc = null;
    root = ++tot;

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(root, 1, n);
    for (int i = 1; i <= m; ++i) {
        cin >> l >> r;
        sign(root, l, r, i);
    }

    cin >> q;
    while (q--) {
        cin >> x;
        x = (las + x - 1) % n + 1;
        modify(root, x);
        cout << ans << '\n';
        las = ans;
    }

    return 0;
}