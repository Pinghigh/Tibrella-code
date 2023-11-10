#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;
using u16 = unsigned short;
using u32 = unsigned;
using u64 = unsigned long long;

namespace pcg {
    std::random_device sd;
    u32 seed = sd() ^ std::chrono::steady_clock().now().time_since_epoch().count();
    u16 salt = std::chrono::steady_clock().now().time_since_epoch().count() ^ 20070408;
    u32 rand() {
        u64 ov = seed;
        seed = seed * 998244353 + salt;
        ov = ((ov >> ((ov >> 28u) + 4u)) ^ ov) * 99249192751u;
        return (ov >> 22u) ^ ov;
    }
}   

#define N 100005

struct Node {
    Node *lc, *rc;
    i64 sum, tag;
    i32 val;
    i32 siz;
    u32 ext;

    void push_up() {
        siz = lc->siz + rc->siz + 1; sum = lc->sum + rc->sum + val;
    }
    void push_down() {
        if (!tag) return;
        lc->tag += tag; rc->tag += tag; lc->val += tag; rc->val += tag;
        lc->sum += tag * lc->siz, rc->sum += tag * rc->siz;
        tag = 0;
    }
} space[N];
Node *tot = space, *null = space, *root = space + 1;
i32 a[N];

Node* newnode(i32 val) {
    Node* nod = ++tot;
    nod->val = nod->sum = val;
    nod->ext = pcg::rand();
    nod->siz = 1;
    nod->lc = nod->rc = null;
    return nod;
}

Node* build(i32 l, i32 r) {
    if (l > r) return null;
    else if (l == r) return newnode(a[l]);
    i32 mid = (l + r) >> 1;
    Node* nod = newnode(a[mid]);
    nod->lc = build(l, mid-1);
    nod->rc = build(mid+1, r);
    nod->push_up();
    return nod;
}

void split(Node* cur, i32 rk, Node*& l, Node*& r) {
    if (cur == null) l = null, r = null;
    else {
        cur->push_down();
        if (cur->lc->siz >= rk) {
            r = cur;
            split(cur->lc, rk, l, cur->lc);
        } else {
            l = cur;
            split(cur->rc, rk - cur->lc->siz - 1, cur->rc, r);
        }
        cur->push_up();
    }
}

Node* merge(Node* l, Node* r) {
    if (l == null) return r;
    else if (r == null) return l;
    else {
        l->push_down(), r->push_down();
        if (l->ext < r->ext) {
            l->rc = merge(l->rc, r);
            l->push_up();
            return l;
        } else {
            r->lc = merge(l, r->lc);
            r->push_up();
            return r;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    null->lc = null->rc = null;

    i32 n, m;
    cin >> n >> m;
    for (i32 i = 1; i <= n; ++ i) cin >> a[i];

    root = build(1, n);

    while (m--) {
        i32 op;
        cin >> op;
        if (op == 1) {
            i32 x, y, k;
            cin >> x >> y >> k;
            Node *a, *b, *c, *d;
            split(root, x-1, a, b);
            split(b, y-x+1, c, d);
            c->tag += k;
            c->sum += k * d->siz;
            c->val += k;
            root = merge(a, merge(c,d));
        } else {
            i32 x, y;
            cin >> x >> y;
            Node *a, *b, *c, *d;
            split(root, x-1, a, b);
            split(b, y-x+1, c, d);
            cout << c->sum << '\n';  
            root = merge(a, merge(c,d));
        }
        // cout << root->siz << ' ' << root->val << ' ' << root->sum << '\n';
        // cout << root->sum << '\n';
    }

    return 0;
}