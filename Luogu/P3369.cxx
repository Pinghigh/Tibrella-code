#pragma GCC target("avx2,sse4a,lzcnt,popcnt,bmi,bmi2,fma")

#include <cstdio>
#include <string>

namespace Fastio {
    namespace Fread {
        const int SIZE = (1 << 20);
        char buf[SIZE], *S, *T;
        inline char getchar() {
            if (S == T) {
                T = (S = buf) + fread(buf, 1, SIZE, stdin);
                if (S == T) return '\n';
            }
            return *S++;
        }
    }  // namespace Fread
    namespace Fwrite {
        const int SIZE = (1 << 20);
        char buf[SIZE], *S = buf, *T = buf + SIZE;
        inline void flush() {
            fwrite(buf, 1, S - buf, stdout);
            S = buf;
        }
        inline void putchar(char c) {
            *S++ = c;
            if (S == T) flush();
        }
        struct NTR {
            ~NTR() {
                flush();
            }
        } ztr;
    }  // namespace Fwrite
#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif
    struct Reader {
        char c;
        template <typename T>
        Reader& operator>>(T& x) {
            T dp = 1;
            do {
                c = getchar();
                if (c == '-') dp = -1;
            } while (c < '0' || c > '9');
            x = 0;
            do {
                x = x * 10 + (c ^ '0'), c = getchar();
            } while (c > 47 && c < 58);
            x *= dp;
            return *this;
        }
        Reader& operator>>(char& ch) {
            ch = getchar();
            while (ch == ' ' || ch == '\n')
                ch = getchar();
            return *this;
        }
        Reader& operator>>(char* str) {
            int len = 0;
            c = getchar();
            while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
                c = getchar();
            while (c != ' ' && c != '\n' && c != '\r' && c != '\t')
                str[len++] = c, c = getchar();
            str[len] = '\0';
            return *this;
        }
        Reader& operator>>(std::string& str) {
            str.resize(0);
            do {
                c = getchar();
            } while (c == ' ' || c == '\n');
            do {
                str += c, c = getchar();
            } while (c != ' ' && c != '\n' && c != '\r');
            // str += '\0';
            return *this;
        }
        inline Reader() {}
    } cin;
    const char endl = '\n';
    static char __output_sta[40];
    int __output_top;

#define sta __output_sta
#define top __output_top

    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (x < 0) putchar('-'), x = -x;
            top = 0;
            do {
                sta[++top] = x % 10 ^ 48, x /= 10;
            } while (x);
            do {
                putchar(sta[top--]);
            } while (top);
            return *this;
        }
        Writer& operator<<(char c) {
            putchar(c);
            return *this;
        }
        Writer& operator<<(char* str) {
            int cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        Writer& operator<<(const char* str) {
            int cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        Writer& operator<<(const std::string& str) {
            for (auto& c : str)
                putchar(c);
            return *this;
        }
        inline Writer() {}
#undef sta
#undef top
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
}  // namespace Fastio
using namespace Fastio;

#include <random>

std::random_device seed;
std::mt19937_64 rd(seed());

#define N 100005

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
    fhq_tree() {fhq->lc = fhq->rc = root->lc = root->rc = fhq;null->siz=0;}

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
        root = merge(merge(l,new_son),r);
    }

    __sizeType get_rank(__keyType v) {
        Node *l, *r;
        l = r = null;
        split(root, v - 1, l, r);
        __sizeType res = l->siz + 1;
        root = merge(l, r);
        return res;
    }

    __keyType get_kth(__sizeType v) {
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
    Node *null = new_node(0);
    void split(Node* nod, __keyType k, Node *&l, Node *&r) {  // 此处 l 指的是 l 树的右子树，r 指的是 r 树的左子树
        if (nod == null) {                     // 此行实际上用来初始化
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
    Node* kth(Node* nod, __sizeType k) {  // 查找第 k 小的数字，分三种情况，即 k + 1 < nod->lc->size，k + 1 == nod->lc->size 和 k + 1 > nod->lc->size
        while (nod->lc->siz != k - 1) {
            while (!nod->lc) nod = nod->rc;
            if (nod->lc->siz > k - 1) {
                nod = nod->lc;
            } else {
                k -= nod->lc->siz+1;
                nod = nod->rc;
            }
        }
        return nod;
    }
};

fhq_tree<long long, unsigned long long> tree;
int n;
int opt, x;

int main() {
    cin >> n;
    while (n--) {
        cin >> opt >> x;
        if (opt == 1) {
            tree.ins(x);
        } else if (opt == 2) {
            tree.del(x);
        } else if (opt == 3) {
            cout << tree.get_rank(x) << endl;
        } else if (opt == 4) {
            cout << tree.get_kth(x) << endl;
        } else if (opt == 5) {
            cout << tree.get_front(x) << endl;
        } else if (opt == 6) {
            cout << tree.get_next(x) << endl;
        }
    }

    return 0;
}
