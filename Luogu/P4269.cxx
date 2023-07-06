#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

using i32 = int;

#define N 100005

struct Node {
    Node *lc, *rc;
    i32 mxl, mxr, mx;
    bool val;
    i32 l, r, mid;

    void init(i32 L, i32 R) {
        l = L, r = R, mid = (L + R) >> 1;
    }
} stree[N << 2];
using np = Node*;
np tot = stree;
np null;
np root;

void build(np nod, i32 l, i32 r) {
    nod->init(l, r);
    if (l == r) {
        nod->lc = nod->rc = null;
    } else {
        nod->lc = ++tot;
        build(nod->lc, l, nod->mid);
        nod->rc = ++tot;
        build(nod->rc, nod->mid + 1, r);
    }
}

void modify(np nod, i32 pos) {
    if (nod->l == nod->r && nod->l == pos) {
        nod->mxl = nod->mxr = nod->mx = 1;
        return;
    }

    if (pos > nod->mid)
        modify(nod->rc, pos);
    else
        modify(nod->lc, pos);

    nod->mxl = max((nod->lc->mxl == (nod->lc->r - nod->lc->l + 1) ? nod->lc->mxl + nod->rc->mxl : nod->lc->mxl), nod->mxl);
    nod->mxr = max((nod->rc->mxr == (nod->rc->r - nod->rc->l + 1) ? nod->lc->mxr + nod->rc->mxr : nod->rc->mxr), nod->mxr);
    nod->mx = max(max(nod->mx, max(nod->lc->mx, nod->rc->mx)), max(max(nod->mxl, nod->mxr), nod->lc->mxr + nod->rc->mxl));
}
struct bele {
    i32 id;
    i32 s;
    i32 d;
} boot[N];

struct diz {
    i32 id;
    i32 f;
} place[N], sorted[N];

i32 n, b;
std::bitset<N> ans;

int main() {
    null = tot;
    null->lc = null->rc = null;

    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> b;
    for (int i = 1; i <= n; ++i) {
        cin >> place[i].f;
        place[i].id = i;
        sorted[i] = place[i];
    }
    std::sort(sorted + 1, sorted + n + 1, [](const diz& a, const diz& b) { return a.f > b.f; });
    for (int i = 1; i <= b; ++i) {
        cin >> boot[i].s >> boot[i].d;
        boot[i].id = i;
    }
    std::sort(boot + 1, boot + b + 1, [](const bele& a, const bele& b) { return a.s > b.s; });

    root = ++tot;
    build(root, 0, 1 + n);

    i32 pos = 1;
    for (int i = 1; i <= b; ++i) {
        bele* bt = boot + i;
        while (pos <= n && sorted[pos].f > bt->s) {
            modify(root, sorted[pos++].id);
        }
        ans[bt->id] = ((root->mx) < bt->d);
    }

    // cout << root->mx << ' ' << root->mxl << ' ' << root->mxr;

    for (int i = 1; i <= b; ++i)
        cout << ans[i] << '\n';

    return 0;
}