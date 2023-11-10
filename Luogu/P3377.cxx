#pragma GCC target("avx2,ssse3,sse4a,lzcnt,popcnt,bmi,bmi2,fma")

#include <cstdint>
#include <cstdio>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

struct istream {
    static constexpr u32 SIZE = 1 << 18;
    char buf[SIZE], *cur, *end;
    FILE* dist;
    bool eof;

    istream(FILE* __dist) {
        dist = __dist;
        eof = false;
        cur = end = nullptr;
    }

    istream(const char*& __dist) {
        dist = fopen(__dist, "r");
        eof = false;
        cur = end = nullptr;
    }

    char get() {
        if (cur == end) {
            cur = buf, end = buf + fread(buf, 1, SIZE, dist);
            if (cur == end) return EOF;
        }
        return *(cur++);
    }

    template <typename T>
    istream& operator>>(T& x) {
        char c;
        x = 0;
        do {
            c = get();
        } while (c < 48 || c > 57);
        do {
            x = x * 10 + (c ^ 48);
            c = get();
        } while (c > 47 && c < 58);
        return *this;
    }
} cin(stdin);

struct ostream {
    static constexpr u32 SIZE = 1 << 19;
    char buf[SIZE];
    char* cur = buf;
    FILE* dist;

    ostream(FILE* __dist) {
        dist = __dist;
    }

    ostream(const char*& __dist) {
        dist = fopen(__dist, "r");
    }

    void put(const char& c) {
        if (cur - buf == SIZE) {
            fwrite(buf, 1, SIZE, dist);
            cur = buf;
        }
        *(cur++) = c;
    }
    void flush() {
        fwrite(buf, 1, cur - buf, dist);
        cur = buf;
    }
    ostream& operator<<(const char* s) {
        for (u64 i = 0; s[i]; ++i)
            put(s[i]);
        return *this;
    }

    ostream& operator<<(const char& c) {
        put(c);
        return *this;
    }
    template <typename T>
    ostream& operator<<(T x) {
        static char stk[20];
        char top = 0;
        do {
            stk[++top] = x % 10 ^ 48;
            x /= 10;
        } while (x);
        do
            put(stk[top]);
        while (--top);
        return *this;
    }

    ~ostream() {
        flush();
    }
} cout(stdout);

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
    static Node* new_node() {
        Node* nod;
        if (bintop)
            nod = rubbish_bin[bintop--];
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

    Node* del(Node* x) {
        Node* t = merges(x->child);
        remove(x);
        return t;
    }

public:
    Node* root;
    pairing_heap() {
        root = null;
    }
    inline void push(num x) {
        Node* y = new_node();
        y->val = x;
        if (root == null)
            root = y;
        else
            root = meld(root, y);
    }
    inline num top() {
        return root->val;
    }
    inline void pop() {
        root = del(root);
    }

    inline void join(pairing_heap& x) {
        root = meld(root, x.root);
    }
} q[__SIZ];

#include <bitset>

std::bitset<__SIZ> st;

int main() {
    null->child = null->nex = null;

    int n;
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        fa[i] = tmp.id = i;
        cin >> tmp.data;
        q[i].push(tmp);
    }
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int t1, t2;
            cin >> t1 >> t2;
            if (st[t1] || st[t2]) continue;
            t1 = find(t1);
            t2 = find(t2);
            if (t1 == t2) continue;
            q[t1].join(q[t2]);
            uni(t1, t2);
        } else {
            int t1;
            cin >> t1;
            if (st[t1]) {
                cout << "-1\n";
            } else {
                t1 = find(t1);
                st[q[t1].top().id] = 1;
                cout << q[t1].top().data << '\n';
                q[t1].pop();
            }
        }
    }

    return 0;
}