#pragma GCC target("avx2,sse4a,lzcnt,popcnt,fma")
const char endl = '\n';

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
}  // namespace Fastio
using namespace Fastio;

#include <climits>
#include <cmath>

// #include <iostream>

// using std::cin;
// using std::cout;

#define N 300005

using i64 = __int128;
using f128 = __int128;

struct sakuya {
    f128 s;
    i64 id;
    i64 start;

    bool operator<(const sakuya& a) {
        return s < a.s;
    }
    bool operator>(const sakuya& a) {
        return s > a.s;
    }
};

f128 abs(f128 x) {
    return x < 0 ? -x : x;
}

struct Node {
    Node *child, *nex;
    sakuya val;
    f128 plus, mul;  // 加后乘
    bool null;

    Node() {
        mul = 1;
    }

    void push_down() {
        if (null) {
            mul = 1;
            plus = 0;
            return;
        }
        Node* c = child;
        val.s *= mul;
        val.s += plus;
        if (abs(c->mul) > (LLONG_MAX / 2) || abs(c->plus) > 1e18) c->push_down();
        while (!c->null) {
            if (mul != 1) {
                c->mul *= mul;
                c->plus *= mul;
            }
            if (plus) {
                c->plus += plus;
            }
            if (abs(c->mul) > (LLONG_MAX / 2) || abs(c->plus) > 1e18) c->push_down();
            c = c->nex;
        }
        mul = 1, plus = 0;
    }
} space[N];

Node *tot = space + 1, *null = space;

Node* meld(Node* x, Node* y) {
    if (x == null)
        return y;
    else if (y == null)
        return x;
    x->push_down();
    y->push_down();
    if (x->val > y->val) {
        x->nex = y->child;
        y->child = x;
        return y;
    } else {
        y->nex = x->child;
        x->child = y;
        return x;
    }
}

Node* merge(Node* nod) {
    if (nod == null || nod->nex == null) return nod;
    Node *x = nod->nex, *y = nod->nex->nex;
    x->nex = nod->nex = null;
    x->push_down();
    y->push_down();
    nod->push_down();
    return meld(merge(y), meld(nod, x));
}

void push(Node*& root, sakuya val) {
    Node* y = ++tot;
    y->val = val;
    y->child = y->nex = null;
    if (root == null) {
        root = y;
        return;
    }
    root->push_down();
    root = meld(root, y);
}

void pop(Node*& root) {
    Node* t = merge(root->child);
    root->child = root->nex = null;
    root->mul = 1;
    root->plus = 0;
    root->val = { 0, 0, 0 };
    root = t;
}

i64 son[N], nex[N];  // 左儿子右兄弟
i64 op[N], val[N];
i64 hp[N];
Node* heap[N];
i64 kill[N], guard[N];
i64 dep[N];

i64 n, m;
f128 t1, t2, t3;
i64 t4, t5, t6;

void dfs(int nod) {
    // if (heap[nod] == null) return;
    for (int to = son[nod]; to; to = nex[to]) {
        dep[to] = dep[nod] + 1;
        dfs(to);
        if (heap[to] != null) {
            heap[to]->child = merge(heap[to]->child);  // 多配对几次防止 push_down 复杂度爆炸
            heap[to]->push_down();                     // 标记下传
            heap[nod] = meld(heap[nod], heap[to]);     // 合并
            heap[nod]->child = merge(heap[nod]->child);
        }
    }
    heap[nod]->push_down();
    while (heap[nod] != null && heap[nod]->val.s < hp[nod]) {
        ++guard[nod];                                                    // 当前城池杀人 + 1
        kill[heap[nod]->val.id] = dep[heap[nod]->val.start] - dep[nod];  // 起点深度 - 终点深度
        pop(heap[nod]);
        heap[nod]->push_down();
    }
    // 添加标记
    if (abs(heap[nod]->mul) > 1e18 || abs(heap[nod]->plus) > 1e18) heap[nod]->push_down();
    if (op[nod]) {
        heap[nod]->mul *= val[nod];
        heap[nod]->plus *= val[nod];
        heap[nod]->push_down();
    } else {
        heap[nod]->plus += val[nod];
        heap[nod]->push_down();
    }
}

void last(Node* nod) {  // 统计最后一个堆的节点
    if (nod == null) return;
    kill[nod->val.id] = dep[nod->val.start];  // 起点深度 - 终点深度
    last(nod->nex);
    last(nod->child);
}

int main() {
    // std::ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);
    dep[1] = 1;
    null->child = null->nex = null;
    null->null = 1;

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> hp[i];
        heap[i] = null;
    }
    for (int i = 2; i <= n; ++i) {
        cin >> t5 >> op[i] >> val[i];
        nex[i] = son[t5];
        son[t5] = i;
    }
    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t5;  // 初始攻击力，初始位置
        push(heap[t5], (sakuya){ t1, i, t5 });
    }

    dfs(1);
    last(heap[1]);

    for (int i = 1; i <= n; ++i) {
        cout << guard[i] << endl;
    }
    for (int i = 1; i <= m; ++i) {
        cout << kill[i] << endl;
    }

    return 0;
}