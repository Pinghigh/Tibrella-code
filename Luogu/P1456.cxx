#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::max;
using std::min;

#define N 100005

using i32 = int;
using u32 = unsigned int;

struct dsu_node {
    dsu_node* fa;
    i32 rk;

    dsu_node() {
        fa = this;
        rk = 0;
    }

    void init() {
        fa = this;
        rk = 0;
    }

    using dsu_node_pointer = dsu_node*;

    dsu_node_pointer& find() {
        if (fa != this) fa = fa->find();
        return fa;
    }

    bool merge(dsu_node& a) {
        dsu_node_pointer& x = find();
        dsu_node_pointer& y = a.find();
        if (x == y) return false;
        y->fa = x;
        return true;
    }
} dsu[N];

struct pnode {
    pnode *child, *nex;
    i32 val;
} heap_space[N];
using node_pointer = pnode*;
node_pointer tail = heap_space;
node_pointer rubbish_bin[N];
u32 bintop;

class pairing_heap {
private:
    pnode* root;

    node_pointer meld(node_pointer x, node_pointer y) {
        if (x == nullptr)
            return y;
        else if (y == nullptr)
            return x;
        if (x->val > y->val) {
            y->nex = x->child;
            x->child = y;
            return x;
        } else {
            x->nex = y->child;
            y->child = x;
            return y;
        }
    }

    node_pointer pairing(node_pointer x) {
        if (x == nullptr || x->nex == nullptr) return x;
        node_pointer y = x->nex, sub_tree = x->nex->nex;
        y->nex = x->nex = nullptr;
        return meld(pairing(sub_tree), meld(x, y));
    }

    void del(node_pointer x) {
        rubbish_bin[++bintop] = x;
    }

    node_pointer getnew() {
        if (bintop) {
            rubbish_bin[bintop]->nex = rubbish_bin[bintop]->child = nullptr;
            return rubbish_bin[bintop--];
        } else {
            return ++tail;
        }
    }

public:
    pairing_heap() {
        root = nullptr;
    }

    void push(i32 v) {
        node_pointer tmp = getnew();
        tmp->val = v;
        if (!root) return root = tmp, void();
        root = meld(root, tmp);
    }

    i32 top() {
        return root == nullptr ? 0 : root->val;
    }

    void pop() {
        del(root);
        root = pairing(root->child);
    }

    void join(pairing_heap& x) {
        root = meld(root, x.root);
    }
} q[N];

i32 n, m;
i32 s;
i32 ix, iy;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (cin >> n) {
        for (u32 i = 1; i <= n; ++i) {
            dsu[i].init();
            q[i] = pairing_heap();
            cin >> s;
            q[i].push(s);
        }
        cin >> m;
        while (m--) {
            cin >> ix >> iy;
            i32 xfa = dsu[ix].find() - dsu, yfa = dsu[iy].find() - dsu;
            if (xfa == yfa) {
                cout << "-1\n";
            } else {
                dsu[xfa].merge(dsu[yfa]);
                q[xfa].push(q[xfa].top() >> 1);
                q[xfa].pop();
                q[yfa].push(q[yfa].top() >> 1);
                q[yfa].pop();
                q[xfa].join(q[yfa]);
                cout << q[xfa].top() << '\n';
            }
        }
    }

    return 0;
}