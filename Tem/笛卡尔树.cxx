#include <cstdio>

#ifdef __WINDOWS__
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef __LINUX__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

template <typename T>
struct Reader {
    char ch;
    T x;

    T operator()() {
        x = 0;
        do {
            ch = getchar();
        } while (ch < 48 || ch > 57);
        do {
            x = x * 10 + (ch ^ 48);
            ch = getchar();
        } while (ch > 47 && ch < 58);
        return x;
    }
};

using i64 = long long int;
Reader<i64> read;

#define N 10000007

i64 n;

struct Node {
    Node *lc, *rc;
    i64 p;   // 堆
    i64 id;  // 二叉搜索树
} space[N];

using nodePointer = Node*;
nodePointer rline[N], nodlist[N];
i64 top;

nodePointer tot = space, root;

nodePointer new_node() {
    ++tot;
    tot->lc = tot->rc = nullptr;
    tot->p = tot->id = 0;
    return tot;
}

void insert(i64 id, i64 p) {
    nodePointer idx = new_node();
    idx->lc = idx->rc = nullptr;
    nodlist[id] = idx;
    idx->id = id;
    idx->p = p;
    nodePointer las = nullptr;
    while (top && rline[top]->p > p) {
        las = rline[top--];
    }
    idx->lc = las;
    if (top) {
        rline[top]->rc = idx;
    } else {
        root = idx;
    }

    rline[++top] = idx;
}

i64 ansl, ansr;

void ans() {
    for (i64 i = 1; i <= n; ++i) {
        if (nodlist[i]->lc)
            ansl ^= i * (nodlist[i]->lc->id + 1);
        else
            ansl ^= i * 1;

        if (nodlist[i]->rc)
            ansr ^= i * (nodlist[i]->rc->id + 1);
        else
            ansr ^= i * 1;
    }
    printf("%lld %lld", ansl, ansr);
}

int main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        insert(i, read());
    }
    ans();

    return 0;
}