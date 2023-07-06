#include <algorithm>
#include <iostream>
#include <random>

std::random_device seed;
std::mt19937 rd(seed());

using std::cin;
using std::cout;
using std::max;

template <int N>
class fhq_treap {
private:
    struct Node {
        Node *lc, *rc;
        unsigned int val, pos;
        unsigned int siz;
        unsigned int heap_val;
    } tree[N];
    unsigned int f[N];

    using nodePointer = Node*;

    nodePointer tot = tree;

    void push_up(nodePointer nod) {
        nod->val = max(f[nod->pos], max(nod->lc->val, nod->rc->val));
        nod->siz = nod->lc->siz + nod->rc->siz + 1;
    }

    nodePointer new_node(int val, int pos) {
        nodePointer res = ++tot;
        res->lc = res->rc = null;
        res->siz = 1;
        res->val = val;
        f[res->pos = pos] = res->val = val;
        res->heap_val = rd();
        return res;
    }

    nodePointer null = tree;
    nodePointer root = null;

    void split(nodePointer nod, unsigned int val, nodePointer& l, nodePointer& r) {
        if (nod == null)
            l = r = null;
        else {
            if (nod->lc->siz + 1 <= val) {
                l = nod;
                split(nod->rc, val - nod->lc->siz - 1, nod->rc, r);
            } else {
                r = nod;
                split(nod->lc, val, l, nod->lc);
            }
            push_up(nod);
        }
    }

    nodePointer merge(nodePointer l, nodePointer r) {
        if (l == null) return r;
        if (r == null) return l;
        if (l->heap_val < r->heap_val) {
            l->rc = merge(l->rc, r);
            push_up(l);
            return l;
        } else {
            r->lc = merge(l, r->lc);
            push_up(r);
            return r;
        }
    }

public:
    fhq_treap() {
        null->lc = null->rc = null;
    }

    unsigned int ins(unsigned int val, unsigned int rk) {
        nodePointer x, y;
        // int tmp = (fpos[rk]) ? fpos[rk]->val : 0;
        split(root, rk, x, y);
        root = merge(x, merge(new_node(x->val + 1, val), y));
        return root->val;
    }
};

fhq_treap<100005> tree;
unsigned int n, t1;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (unsigned int i = 1; i <= n; ++i) {
        cin >> t1;
        // ++t1;
        cout << tree.ins(i, t1) << '\n';
    }

    return 0;
}