#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,sse4.2,bmi,bmi2,lzcnt,popcnt,mmx,abm,sse4a")

#include <cstdio>

#ifdef __LINUX__
#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a)
#endif

#ifdef __WINDOWS__
#define getchar() _getchar_nolock()
#define putchar(a) _putchar_nolock()
#endif

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
void write(__outputType __x, char __ch, __outputArgs... __args) {
    write(__x, __ch);
    write(__args...);
}

#define endl '\n'

int max(int a, int b) {
    return a > b ? a : b;
}

#define N 300005

struct edge{
    edge *nex;
    int to;
} graph[N];
edge *fir[N], *tot = graph;
void add(int a, int b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot ++;
}

int core[N], siz[N], fa[N];

void dfs(int nod) {
    siz[nod] = 1;
    int mxson = 0; // 当前节点的最大子树
    core[nod] = nod; // 先默认重心为自己
    for (edge* e = fir[nod]; e; e = e->nex) {
        dfs(e->to);
        siz[nod] += siz[e->to];
        mxson = (siz[mxson] < siz[e->to]) ? e->to : mxson;
    }

    if ((siz[mxson] << 1) > siz[nod]) { // 最大子树大小的两倍大于本树大小，说明根节点不是重心，且重心一定在最大子树中
        core[nod] = core[mxson]; // 从根节点往上跳
        while (((siz[nod] - siz[core[nod]]) << 1) > siz[nod]) core[nod] = fa[core[nod]]; // 目前最大子树一定是 core[nod] 父节点所在的那棵子树
    }
}

int n, q;

int main() {
    read(n, q);
    for (int i = 2; i <= n; ++ i) {
        read(fa[i]);
        add(fa[i], i);
    }

    dfs(1);

    while (q --) {
        read(n); // 变量的重复利用
        write(core[n], '\n');
    }

    return 0;
}