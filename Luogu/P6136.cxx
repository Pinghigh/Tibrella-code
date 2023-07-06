#pragma GCC target("avx2,avx512f,sse4a,sse4.2,sse4.1,mmx,popcnt,lzcnt,bmi,bmi2")

#include <random>

std::random_device seed;
std::mt19937 rd(seed());

#include <cstdio>
#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a)

template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    char ch;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename __inputType, typename... __inputArgs>
void read(__inputType& x, __inputArgs&... __args) {
    read(x);
    read(__args...);
}

template <typename __outputType>
void write(__outputType __x, char __ch = ' ') {
    static short int __output_stack[64], __pos;
    __pos = 0;
    do {
        __output_stack[__pos++] = __x % 10;
        __x /= 10;
    } while (__x);
    while (__pos--) {
        putchar(__output_stack[__pos] ^ 48);
    }
    putchar(__ch);
}

template <typename __outputType, typename... __outputArgs>
void write(__outputType __x, char __ch = ' ', __outputArgs... __args) {
    write(__x, __ch);
    write(__args...);
}

#define endl '\n'
#define N 1100005

template <class __keyType, class __sizeType>
class fhq_tree {
public:
    struct Node {
        Node *lc, *rc;
        __keyType key;
        __sizeType ext;
        __sizeType siz;

        void push_up() {
            siz = lc->siz + rc->siz + 1;  // 如果是叶子节点，siz 始终为 1，因此不需要在操作时更新叶子节点
        }
    } fhq[N];

    Node* tail = fhq;
    Node* root = fhq + 1;
    fhq_tree() {
        fhq->lc = fhq->rc = root->lc = root->rc = fhq;
        null->siz = 0;
    }

    void ins(__keyType v) {
        Node *l, *r;
        l = r = null;
        Node* nod = new_node(v);
        split(root, v, l, r);
        root = merge(merge(l, nod), r);
        // std::cerr << root->key << endl;
    }

    void del(__keyType v) {
        Node *l, *r, *del, *new_son;
        l = r = del = new_son = null;
        split(root, v - 1, l, r);
        split(r, v, del, r);
        new_son = merge(del->lc, del->rc);
        root = merge(merge(l, new_son), r);
    }

    __keyType get_rank(__keyType v) {
        Node *l, *r;
        l = r = null;
        split(root, v - 1, l, r);
        __sizeType res = l->siz + 1;
        root = merge(l, r);
        return res;
    }

    __keyType get_kth(__keyType v) {
        return kth(root, v)->key;
    }

    __keyType get_front(__keyType v) {
        Node *l, *r;
        l = r = null;
        split(root, v - 1, l, r);
        __keyType res = kth(l, l->siz)->key;
        merge(l, r);
        return res;
    }

    __keyType get_next(__keyType v) {
        Node *l, *r;
        l = r = null;
        split(root, v, l, r);
        __keyType res = kth(r, 1)->key;
        merge(l, r);
        return res;
    }

private:
    Node* null = new_node(0);
    void split(Node* nod, __keyType k, Node*& l, Node*& r) {  // 此处 l 指的是 l 树的右子树，r 指的是 r 树的左子树
        if (nod == null) {                                    // 此行实际上用来初始化
            l = r = null;
            return;
        }

        if (nod->key <= k) {  // 键值比参照小，因而左子树所有值比参照小，分到 l 树，同时右子树未知，向右继续分裂
            l = nod;
            split(nod->rc, k, nod->rc, r);

        } else {
            r = nod;
            split(nod->lc, k, l, nod->lc);
        }
        nod->push_up();
    }

    Node* merge(Node* l, Node* r) {
        if (l == null) return r;
        if (r == null) return l;
        // std::cerr << ">>>>> fhq: " << fhq << " l: " << l << " r: " << r << endl;
        if (l->ext < r->ext) {  // l 附加权值比 r 小，为了保证堆的性质需要让 r 在 l 底下，又因为 r 的真权值一定比 l 大，因此合并到右子树上
            l->rc = merge(l->rc, r);
            l->push_up();
            return l;
        } else {
            r->lc = merge(l, r->lc);
            r->push_up();
            return r;
        }
    }

    Node* new_node(__keyType v) {
        ++tail;
        tail->lc = tail->rc = null;
        tail->key = v;
        tail->siz = 1;
        tail->ext = rd();
        return tail;
    }
    Node* kth(Node* nod, __keyType k) {  // 查找第 k 小的数字，分三种情况，即 k + 1 < nod->lc->size，k + 1 == nod->lc->size 和 k + 1 > nod->lc->size
        while (nod->lc->siz != k - 1) {
            while (!nod->lc)
                nod = nod->rc;
            if (nod->lc->siz > k - 1) {
                nod = nod->lc;
            } else {
                k -= nod->lc->siz + 1;
                nod = nod->rc;
            }
        }
        return nod;
    }
};

fhq_tree<int, int> tree;
int n, m;
int opt, x;
int ans;
int res;

int main() {
    read(n, m);
    while (n--) {
        read(x);
        tree.ins(x);
    }
    while (m--) {
        read(opt, x);
        x ^= ans;
        if (opt == 1) {
            tree.ins(x);
        } else if (opt == 2) {
            tree.del(x);
        } else if (opt == 3) {
            ans = tree.get_rank(x);
            res ^= ans;
            // write(ans, '\n');
        } else if (opt == 4) {
            ans = tree.get_kth(x);
            res ^= ans;
            // write(ans, '\n');
        } else if (opt == 5) {
            ans = tree.get_front(x);
            res ^= ans;
            // write(ans, '\n');
        } else if (opt == 6) {
            ans = tree.get_next(x);
            res ^= ans;
            // write(ans, '\n');
        }
    }
    write(res, '\n');

    return 0;
}
