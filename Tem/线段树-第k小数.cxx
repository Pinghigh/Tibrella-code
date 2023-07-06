#include <algorithm>
#include <cstdio>
#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a)

template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    bool f = 0;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') {
            f = 1;
        }
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
    x *= (f ? -1 : 1);
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
#define N 5005140

struct Node {
    int data;
    Node* lc;
    Node* rc;
    int l, r, mid;

    void init(int L, int R) {
        l = L, r = R, mid = l + r >> 1;
    }
} tree[N * 4];

int n, k;
int lst[N];
Node* tot = tree;
int t1;
Node null;

void push_up(Node* nod) {
    nod->data = nod->lc->data + nod->rc->data;
}

int query(Node* nod, int kth) {
    if (nod->l == nod->r) {
        return nod->r;
    } else if (nod->lc->data < kth) {
        return query(nod->rc, kth - nod->lc->data);
        // cout << 1 << endl;
    } else {
        return query(nod->lc, kth);
    }
}

void build(Node* nod, int L, int R) {
    nod->init(L, R);
    if (L == R) {
        nod->lc = nod->rc = &null;
        nod->data = lst[L];
        return;
    }
    nod->lc = ++tot;
    nod->rc = ++tot;
    build(nod->lc, L, nod->mid);
    build(nod->rc, nod->mid + 1, R);
    push_up(nod);
}

int main() {
    null.init(0, 0);
    null.lc = null.rc = &null;

    read(n, k);
    for (int i = 1; i <= n; ++i) {
        read(t1);
        ++lst[t1];
    }
    build(++tot, 1, n);
    write(query(tree + 1, k + 1), '\n');
    return 0;
}