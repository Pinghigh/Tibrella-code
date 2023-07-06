#include <iostream>

using std::cin;
using std::cout;
using pii = std::pair<int, int>;

#define endl '\n'
#define N 5000005

struct edge {
    edge* nex;
    int to, val;
} graph[N << 2], *fir[N << 1];
edge* tot = graph;

void add(int a, int b, int v) {
    tot->to = b;
    tot->val = v;
    tot->nex = fir[a];
    fir[a] = tot++;
}

struct Node {
    Node *lc, *rc;
    int id;
    int l, r, mid;

    void init(int L, int R) {
        l = L, r = R, mid = (L + R) >> 1;
    }
} nodes[N << 2];

Node *tail, *iroot, *oroot, *null;
int idx;
int iid[N], oid[N];

void build(Node* inod, Node* onod, int l, int r) {
    inod->init(l, r);
    inod->id = ++idx;
    onod->init(l, r);
    onod->id = ++idx;
    add(inod->id, onod->id, 0);
    if (l == r) {
        // (is_in ? iid[l] : oid[l]) = idx;
        iid[l] = inod->id;
        oid[l] = onod->id;
        inod->lc = inod->rc = onod->lc = onod->rc = null;
    } else {
        inod->lc = ++tail;
        inod->rc = ++tail;
        onod->lc = ++tail;
        onod->rc = ++tail;
        build(inod->lc, onod->lc, inod->l, inod->mid);
        build(inod->rc, onod->rc, inod->mid + 1, inod->r);

        add(inod->id, inod->lc->id, 0);
        add(inod->id, inod->rc->id, 0);
        add(onod->lc->id, onod->id, 0);
        add(onod->rc->id, onod->id, 0);
    }
}

void modify(Node* nod, int vnod, int l, int r, bool is_in) {
    if (nod->l == l && nod->r == r) {
        if (is_in)
            add(vnod, nod->id, 1);
        else
            add(nod->id, vnod, 0);
    } else {
        if (nod->lc->r >= r) {
            modify(nod->lc, vnod, l, r, is_in);
        } else if (nod->rc->l <= l) {
            modify(nod->rc, vnod, l, r, is_in);
        } else {
            modify(nod->lc, vnod, l, nod->lc->r, is_in);
            modify(nod->rc, vnod, nod->rc->l, r, is_in);
        }
    }
}

int n, m, p;
int a, b, c, d;

#include <bitset>
#include <cstring>
#include <list>

std::list<pii> q;
std::bitset<(N << 1)> vis;
int dis[N << 1];
void bfs() {
    memset(dis, 0x3f, sizeof(dis));
    q.emplace_back((pii){ iid[p], 0 });
    dis[iid[p]] = 0;
    while (q.size()) {
        int nod = q.front().first;
        q.pop_front();
        vis[nod] = true;
        for (edge* e = fir[nod]; e; e = e->nex) {
            if (vis[e->to]) continue;
            if (e->val + dis[nod] < dis[e->to]) {
                dis[e->to] = dis[nod] + e->val;
                if (e->val)
                    q.emplace_back((pii){ e->to, dis[e->to] });
                else
                    q.emplace_front((pii){ e->to, dis[e->to] });
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    tail = nodes;
    null = tail;

    idx = 0;

    cin >> n >> m >> p;

    iroot = ++tail;
    oroot = ++tail;
    build(iroot, oroot, 1, n);

    // for (Node* nd = iroot; nd != oroot; ++nd)
    //     add(nd->id, nd->id + pian, 0);

    while (m--) {
        cin >> a >> b >> c >> d;
        ++idx;
        modify(iroot, idx, a, b, true);
        modify(oroot, idx, c, d, false);
        ++idx;
        modify(iroot, idx, c, d, true);
        modify(oroot, idx, a, b, false);
    }

    bfs();

    for (int i = 1; i <= n; ++ i) cout << dis[iid[i]] << '\n';

    // for (int i = 1; i <= n; ++i) {
    //     cout << iid[i] << ' ';
    // }
    // cout.put('\n');
    // for (int i = 1; i <= idx; ++i)
    //     cout << dis[i] << ' ';

    return 0;
}