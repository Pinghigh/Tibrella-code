#include <algorithm>
#include <iostream>

#define N 100005

using std::cin;
using std::cout;
using std::max;
using i64 = long long int;
using u32 = unsigned int;

struct pnode {
    pnode *child, *nex;
    i64 val;
    i64 siz;
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
            x->siz += y->siz;
            return x;
        } else {
            x->nex = y->child;
            y->child = x;
            y->siz += x->siz;
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

    void push(i64 v) {
        node_pointer tmp = getnew();
        tmp->val = v;
        root = meld(root, tmp);
        ++root->siz;
    }

    i64 top() {
        return root == nullptr ? 0 : root->val;
    }

    void pop() {
        del(root);
        root = pairing(root->child);
    }

    void join(pairing_heap& x) {
        root = meld(root, x.root);
    }

    i64 size() {
        if (!root) return 0;
        return root->siz;
    }
} q[N];

i64 n, m;
i64 b, c[N], l[N];
i64 son[N], nex[N];
i64 ans;

i64 dfs(i64 nod) {
    i64 sum = c[nod];
    for (i64 to = son[nod]; to; to = nex[to]) {
        sum += dfs(to);
        q[nod].join(q[to]);
    }
    while (sum > m) {
        sum -= q[nod].top();
        q[nod].pop();
    }
    ans = max(ans, q[nod].size() * l[nod]);
    return sum;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> b >> c[i] >> l[i];
        nex[i] = son[b];
        son[b] = i;
        q[i].push(c[i]);
    }

    dfs(1);

    cout << ans;

    return 0;
}