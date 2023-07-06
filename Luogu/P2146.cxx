#include <iostream>
#include <bitset>

using std::cin;
using std::cout;


#define N 100005

using i32 = int;

struct edge {
    edge * nex;
    i32 to;
} graph[N],*fir[N];
edge* tot = graph;
void add(i32 a, i32 b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a]=tot++;
}

i32 fa[N];
i32 n;

i32 siz[N], wson[N], dep[N];

void get_wson(i32 nod) {
    siz[nod]=1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        dep[to]=dep[nod]+1;
        get_wson(to);
        if (siz[wson[nod]]<siz[to]) wson[nod]=to;
    }
}

i32 dfn[N], qdfn[N], tim;
void get_dfn(i32 nod) {
    dfn[nod]=++tim;
    qdfn[tim]=nod;
    if (wson[nod]) get_dfn(nod);
    for (edge* e= fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to != wson[nod]) get_dfn(wson[nod]);
    }
}

struct Node {
    Node* lc, *rc;
    i32 tag;
    i32 sum;
    i32 l, r, mid;

    void init(i32 L, i32 R) {
        l = L, r = R;
        mid = (l+r)>>1;
    }
} stree[N];
Node* tail = stree, *root, *null=stree;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        cin >> fa[i];
        ++fa[i];
        add(fa[i], i);
    }

    get_wson(1);
    get_dfn(1);

    root = ++tail;
    build(root, 1, n);

    return 0;
}