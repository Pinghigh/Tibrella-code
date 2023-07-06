#include <cstdio>

namespace Fastio {
    namespace Fread {
        const unsigned int SIZE = (1 << 21);
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
        const unsigned int SIZE = (1 << 21);
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
// #ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
    // #endif
    struct Reader {
        template <typename T>
        Reader& operator>>(T& x) {
            static char c;
            do {
                c = getchar();
            } while (c < '0' || c > '9');
            x = 0;
            do {
                x = x * 10 + (c ^ '0'), c = getchar();
            } while (c > 47 && c < 58);
            return *this;
        }
        inline Reader() {}
    } cin;
    const char endl = '\n';
    static char sta[111];
    char top = 0;
    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            if (!x) {
                putchar('0');
                return *this;
            }
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
        inline Writer() {}
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
}  // namespace Fastio
using namespace Fastio;

#pragma GCC target("avx2,sse4a,lzcnt,popcnt")

using i64 = unsigned int;

#define __SIZ 1000006

struct Node {
    i64 val;
    Node *child, *nex;
} tree[__SIZ], *rubbish_bin[__SIZ];
Node *null = tree, *tot = tree;
i64 bintop;

Node* root;

Node* new_node() {
    Node* nod;
    if (bintop)
        nod = rubbish_bin[bintop--];
    else
        nod = ++tot;
    nod->child = null;
    nod->nex = null;
    return nod;
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

Node* del(Node* x) {}

void push(i64 x) {}

i64 n;
i64 num;
i64 op;

int main() {
    root = null;
    null->child = null->nex = null;

    cin >> n;
    for (i64 i = 1; i <= n; ++i) {
        cin >> op;
        switch (op) {
            case (1):
                cin >> num;
                Node* nod;
                if (bintop)
                    nod = rubbish_bin[bintop--];
                else
                    nod = ++tot;
                nod->child = null;
                nod->nex = null;
                nod->val = num;
                if (root == null)
                    root = nod;
                else
                    root = meld(root, nod);
                break;
            case (2): cout << root->val << endl; break;
            case (3):
                Node* t = merges(root->child);
                rubbish_bin[++bintop] = root;
                root = t;
        }
    }

    return 0;
}