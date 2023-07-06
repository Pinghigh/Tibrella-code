#include <iostream>
#include <random>
#include <utility>

std::random_device seed;
std::mt19937 rd(seed());

using std::cin;
using std::cout;
using std::swap;
#define endl '\n'
#define N 100005

template <class T>
class fhq_treap {
private:
    struct Node {
        Node *lc, *rc;
        T key;
        int ext, siz;
        bool mark;
    } space[N];
    Node* tail = space;
    Node* null = tail;
    Node* root = null;  // 此处 root 初始应为空节点
    void push_up(Node* nod) {
        if (nod != null) nod->siz = nod->lc->siz + nod->rc->siz + 1;
    }
    void push_down(Node* nod) {
        if (nod->mark) {
            nod->mark = 0;
            swap(nod->lc, nod->rc);
            if (nod->lc != null) nod->lc->mark ^= 1;
            if (nod->rc != null) nod->rc->mark ^= 1;
        }
    }
    void split(Node* nod, T k, Node*& l, Node*& r) {
        if (nod == null) {
            l = r = null;
            return;
        } else {
            push_down(nod);
            if (nod->lc->siz + 1 <= k) {
                l = nod;  // 键值比参照小，左子树和根都扔到 l 树，右子树不确定，继续分裂右子树
                split(nod->rc, k - nod->lc->siz - 1, nod->rc, r);
            } else {
                r = nod;
                split(nod->lc, k, l, nod->lc);
            }
            push_up(nod);
        }
    }
    Node* merge(Node* l, Node* r) {
        if (l == null) return r;
        if (r == null) return l;
        push_down(l);
        push_down(r);
        if (l->ext < r->ext) {
            l->rc = merge(l->rc, r);  // l 附加权值小则在上面，依据分裂出来的 l r 树的性质，r 一定比 l 大（根）
            push_up(l);
            return l;
        } else {
            r->lc = merge(l, r->lc);
            push_up(r);
            return r;
        }
    }
    Node* new_node(T v) {
        ++tail;
        tail->lc = tail->rc = null;
        tail->siz = 1;
        tail->key = v;
        tail->ext = rd();
        return tail;
    }
    void dfs(Node* nod) {
        if (nod == null) return;
        push_down(nod);
        dfs(nod->lc);
        cout << nod->key << ' ';
        dfs(nod->rc);
    }

public:
    fhq_treap() {
        null->lc = null->rc = null;
        null->siz = 0;
    }
    void ins(T v) {
        root = merge(root, new_node(v));
    }
    void reverse(int l, int r) {
        Node *a, *b, *c, *d;
        a = b = c = d = null;
        split(root, l - 1, a, b);
        split(b, r - l + 1, c, d);
        c->mark ^= 1;
        root = merge(a, merge(c, d));
    }
    void output_res() {
        dfs(root);
    }
};
int n;
int m;
fhq_treap<int> tree;
int l, r;
int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(nullptr)->tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        tree.ins(i);
    }
    while (m--) {
        cin >> l >> r;
        tree.reverse(l, r);
    }
    tree.output_res();
    return 0;
}