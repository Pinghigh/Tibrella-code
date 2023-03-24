#include <array>
#include <iostream>

using std::array;
using std::cin;
using std::cout;

#define N 100005
#define endl '\n'

struct edge {
    edge* nex;
    int u, v, w;
} tree[N];

struct Node {
    Node* son[2];
    int data;
    int cnt;
} trie[N * 40];

Node* nt = trie;

template <typename T>
T max(T _a, T _b) {
    return _a > _b ? _a : _b;
}

void insert(int num) {
    Node* pos = trie;
    for (int i = 30; ~i; --i) {
        if (!pos->son[num >> i & 1]) pos->son[num >> i & 1] = ++nt;
        pos = pos->son[num >> i & 1];
    }
    ++pos->cnt;
    pos->data = num;
}

int query(int num) {
    Node* pos = trie;
    for (int i = 30, tmp; ~i; --i) {
        tmp = (num >> i) & 1;
        if (pos->son[tmp ^ 1])
            pos = pos->son[tmp ^ 1];
        else
            pos = pos->son[tmp];
    }
    return pos->data;
}

int t1, t2, t3;

edge* tot = tree;
edge* fir[N];
int n;
int f[N], ind[N];
int root;
int res = 0;

void add(int u, int v, int w) {
    ++tot;
    tot->u = u;
    tot->v = v;
    tot->w = w;
    tot->nex = fir[u];
    fir[u] = tot;
    ++ind[v];
}

void dfs(int nod, int x) {
    f[nod] = x;

    for (edge* e = fir[nod]; e; e = e->nex) {
        dfs(e->v, x ^ e->w);
        // cout << (x ^ e->w) << endl;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(nullptr)->tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; ++i) {
        cin >> t1 >> t2 >> t3;
        add(t1, t2, t3);
    }

    for (int i = 1; i <= n; ++i) {
        if (!ind[i]) {
            root = i;
            break;
        }
    }

    dfs(root, 0);

    for (int i = 1; i <= n; ++i) {
        insert(f[i]);
    }

    for (int i = 1; i <= n; ++i) {
        res = max(res, f[i] ^ query(f[i]));
    }

    cout << res << endl;

    return 0;
}