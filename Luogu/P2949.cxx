#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i64 = long long;

#define __SIZ N
#define N 100005

struct Node {
    i64 val;
    Node *child, *nex;
} tree[__SIZ], *rubbish_bin[__SIZ];
Node *null = tree, *tot = tree;
int bintop;
class pairing_heap {
    inline __attribute__((always_inline)) Node* new_node() {
        Node* nod;
        if (bintop)
            nod = rubbish_bin[bintop--];
        else
            nod = ++tot;
        nod->child = null;
        nod->nex = null;
        return nod;
    }

    inline __attribute__((always_inline)) void remove(Node* x) {
        rubbish_bin[++bintop] = x;
    }

    inline __attribute__((always_inline)) Node* meld(Node* x, Node* y) {  // 合并两个堆
        if (x == null)
            return y;
        else if (y == null)
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

    Node* merges(Node* x) {
        if (x == null || x->nex == null) return x;  // x 为空或者 x 没有下一个兄弟节点
        Node* y = x->nex;                           // y 是 x 的下一个兄弟
        Node* c = y->nex;                           // c 是下一个兄弟
        x->nex = y->nex = null;                     // 拆散
        return meld(merges(c), meld(x, y));         // x 与 y 配对在一起，剩下的继续配对
    }

    inline __attribute__((always_inline)) Node* del(Node* x) {
        Node* t = merges(x->child);
        remove(x);
        return t;
    }

public:
    Node* root;
    pairing_heap() {
        root = null;
    }
    inline __attribute__((always_inline)) void push(i64 x) {
        Node* y = new_node();
        y->val = x;
        if (root == null)
            root = y;
        else
            root = meld(root, y);
    }
    inline __attribute__((always_inline)) i64 top() {
        return root->val;
    }
    inline __attribute__((always_inline)) void pop() {
        if (root == null) return;
        root = del(root);
    }

    inline __attribute__((always_inline)) void join(pairing_heap& x) {
        root = meld(root, x.root);
    }

    bool empty() {
        return (root == null);
    }
} q;

i64 n;
struct e {
    i64 v, d;
} task[N];

i64 tim = 0x3f3f3f3f;
i64 ans;
e* now;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> task[i].d >> task[i].v;
    }
    std::sort(task + 1, task + n + 1, [](e& a, e& b) { return a.d > b.d; });
    now = task + 1;
    for (int i = 1; i <= n;) {
        // for (;;) {
        q.push(now->v);
        ++i, ++now;
        //     if (now->p != (now-1)->p) break;
        // }
        while ((now - 1)->d == now->d) {
            q.push(now->v);
            ++i, ++now;
        }
        if (q.empty() && tim >=z now->d) {
            tim = now->d;
        }
        while (!q.empty() && tim > (now + 1)->d) {
            ans += q.top();
            q.pop();
            --tim;
        }
    }

    cout << ans;

    return 0;
}