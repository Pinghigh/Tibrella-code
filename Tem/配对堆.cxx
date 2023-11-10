using i32 = int;



template<typename T>
class pairing_heap {
    #define __SIZ 1000006
    struct Node {
        T val;
        Node *child, *nex;
    } tree[__SIZ], *rubbish_bin[__SIZ];  // 提早分配内存，new 太慢了
    Node *null = tree, *tot = tree;
    unsigned bintop;
    Node* root;

    Node* new_node() {
        Node* nod;
        if (bintop)
            nod = rubbish_bin[bintop--];  // 垃圾回收
        else
            nod = ++tot;
        nod->child = null;
        nod->nex = null;
        return nod;
    }

    void remove(Node* x) {
        rubbish_bin[++bintop] = x;
    }

    Node* meld(Node* x, Node* y) {  // 合并两个堆
        if (x == null)
            return y;
        else if (y == null)
            return x;
        if (x->val < y->val) {
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

    unsigned siz;

public:
    pairing_heap() {
        root = null;
        null->child = null->nex = null;
    }
    void push(const T& x) {
        Node* y = new_node();
        y->val = x;
        if (root == null)
            root = y;
        else
            root = meld(root, y);
        ++siz;
    }
    T top() {
        return root->val;
    }
    void pop() {
        Node* t = merges(root->child);
        remove(root);
        root = t;
        --siz;
    }
    unsigned size() {
        return siz;
    }
    
};

pairing_heap<i32> q;

#include <iostream>

using std::cin;
using std::cout;

i32 n;
i32 num;
i32 op;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> op;
        switch (op) {
            case (1):
                cin >> num;
                q.push(num);
                break;
            case (2): cout << q.top() << '\n'; break;
            case (3): q.pop();
        }
    }

    return 0;
}