#pragma GCC target("avx2,sse4a,lzcnt,popcnt,fma")

#include <algorithm>
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
using i32 = int;
Reader<i32> read;

#define N 10000001

i32 n;

struct Node {
    Node *lc, *rc;
    i64 p;   // 堆
    i64 id;  // 二叉搜索树
} space[N];

using nodePointer = Node*;
nodePointer rline[N];
i64 top;

nodePointer tot = space, null = space, root;

static inline __attribute__((always_inline)) nodePointer new_node() {
    ++tot;
    tot->lc = tot->rc = null;
    tot->p = tot->id = 0;
    return tot;
}

static inline __attribute__((always_inline)) void insert(i64 id, i64 p) {
    nodePointer idx = new_node();
    idx->lc = idx->rc = null;
    idx->id = id;
    idx->p = p;
    nodePointer las = null;
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

using pii = std::pair<int, int>;

i64 t1;

void ans(nodePointer nod) {
    if (nod == null) return;
    printf("%lld ", nod->id);
    ans(nod->lc);
    ans(nod->rc);
}
void debug(nodePointer nod) {
    if (nod == null) return;
    ans(nod->lc);
    printf("%lld ", nod->id);
    ans(nod->rc);
}

pii p[N];

int main() {
    n = read();
    for (int i = 1; i <= n; ++i)
        p[i] = { read(), i };

    std::sort(p + 1, p + n + 1);

    for (int i = 1; i <= n; ++i)
        insert(p[i].first, p[i].second);

    ans(root);
    // puts("");
    // debug(root);
    return 0;
}