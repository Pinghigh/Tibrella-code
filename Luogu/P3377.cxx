#pragma GCC target("avx2,sse4a,lzcnt,popcnt,bmi,bmi2,fma")

#include <cstdio>

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
        template <typename T>
        Reader& operator>>(T& x) {
            char c = getchar();
            T dp = 1;
            while (c < '0' || c > '9') {
                if (c == '-') dp = -1;
                c = getchar();
            }
            x = 0;
            while (c >= '0' && c <= '9')
                x = x * 10 + (c - '0'), c = getchar();
            x *= dp;
            return *this;
        }
        Reader& operator>>(char& c) {
            c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            return *this;
        }
        Reader& operator>>(char* str) {
            int len = 0;
            char c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            while (c != ' ' && c != '\n' && c != '\r')
                str[len++] = c, c = getchar();
            str[len] = '\0';
            return *this;
        }
        inline Reader() {}
    } cin;
    const char endl = '\n';
    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (!x) {
                putchar('0');
                return *this;
            }
            if (x < 0) putchar('-'), x = -x;
            static char sta[40];
            int top = 0;
            while (x)
                sta[++top] = x % 10 ^ 48, x /= 10;
            while (top)
                putchar(sta[top]), --top;
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
        inline Writer() {}
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
}  // namespace Fastio
using namespace Fastio;

#define __SIZ 100005

int fa[__SIZ];
int rk[__SIZ];

struct num {
    int data;
    int id;
    bool operator<(const num& a) const {
        return (data < a.data) || (data == a.data && id < a.id);
    }
    bool operator>(const num& a) const {
        return (data > a.data) || (data == a.data && id > a.id);
    }
};

num tmp;

int max(int a, int b) {
    return (a > b ? a : b);
}

int find(int a) {
    if (fa[a] != a) fa[a] = find(fa[a]);
    return fa[a];
}

void uni(int a, int b) {
    fa[b] = a;
}

struct Node {
    num val;
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
    inline __attribute__((always_inline)) void push(num x) {
        Node* y = new_node();
        y->val = x;
        if (root == null)
            root = y;
        else
            root = meld(root, y);
    }
    inline __attribute__((always_inline)) num top() {
        return root->val;
    }
    inline __attribute__((always_inline)) void pop() {
        root = del(root);
    }

    inline __attribute__((always_inline)) void join(pairing_heap& x) {
        root = meld(root, x.root);
    }
} q[__SIZ];

#include <bitset>

std::bitset<__SIZ> st;
int n;
int op;
int m;
int t1, t2;

int main() {
    null->child = null->nex = null;

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        cin >> t1;
        tmp.id = i;
        tmp.data = t1;
        q[i].push(tmp);
    }
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> t1 >> t2;
            if (st[t1] || st[t2]) continue;
            t1 = find(t1);
            t2 = find(t2);
            if (t1 == t2) continue;
            q[t1].join(q[t2]);
            uni(t1, t2);
        } else {
            cin >> t1;
            if (st[t1]) {
                cout << -1 << endl;
            } else {
                t1 = find(t1);
                st[q[t1].top().id] = 1;
                cout << q[t1].top().data << endl;
                q[t1].pop();
            }
        }
    }

    return 0;
}