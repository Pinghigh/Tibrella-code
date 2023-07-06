#include <iostream>
#include <numeric>

using std::cin;
using std::cout;
using std::iota;

using i32 = int;

i32 n, m;

#define N 100001
#define M 200001

struct parray {
    i32 a[N];

    struct Node {
        Node *lc, *rc;
        i32 val;
        i32 l, r, mid;

        void init(i32 L, i32 R) {
            l = L, r = R;
            mid = (l + r) >> 1;
        }
    } stree[N * 20], *root[M];
    Node* tot;
    i32 ver, mx;

    parray() {
        tot = stree - 1;
        ver = 0;
    }

    Node* build(i32 l, i32 r) {
        Node* nod = ++tot;
        nod->init(l, r);
        if (l == r)
            nod->val = a[l];
        else {
            nod->lc = build(l, nod->mid);
            nod->rc = build(nod->mid + 1, r);
        }
        return nod;
    }

    Node* modify(Node* pre, i32 l, i32 r, i32 pos, i32 val) {
        Node* nod = ++tot;
        nod->init(l, r);
        if (l == r)
            nod->val = val;
        else {
            if (nod->mid >= pos)
                nod->lc = modify(pre->lc, l, nod->mid, pos, val), nod->rc = pre->rc;
            else
                nod->rc = modify(pre->rc, nod->mid + 1, r, pos, val), nod->lc = pre->lc;
        }
        return nod;
    }

    i32 query(Node* nod, i32 pos) {
        if (nod->l == nod->r)
            return nod->val;
        else {
            if (nod->mid >= pos)
                return query(nod->lc, pos);
            else
                return query(nod->rc, pos);
        }
    }

    void init(i32 n) {
        mx = n;
        root[ver] = build(1, mx);
    }

    void mod(i32 pre_ver, i32 pos, i32 val) {
        // std::cerr << ver << ' ' << ++ver << std::endl;
        root[++ver] = modify(root[pre_ver], 1, mx, pos, val);
    }

    i32 get(i32 version, i32 pos) {
        return query(root[version], pos);
    }

    void cpyver(i32 pre_ver) {
        // std::cerr << ver << ' ' << ++ver << std::endl;
        root[++ver] = root[pre_ver];
        // std::cerr << ver << std::endl;
    }
} fa, rk;

i32 ver;  // 当前操作前的版本号

i32 find(i32 nod) {
    i32 f = fa.get(ver, nod);
    i32 tmp = fa.get(ver, f);
    // std::cerr << f << ' ' << tmp << std::endl;
    while (f != tmp) {
        f = tmp;
        tmp = fa.get(ver, f);
    }
    return f;
}

void merge(i32 a, i32 b) {
    // if (a == 20) {
    //     1 + 1;
    // }
    i32 af = find(a), bf = find(b);
    // std::cerr << af << ' ' << bf << std::endl;
    if (af == bf) return rk.cpyver(ver), fa.cpyver(ver), void();
    i32 ar = rk.get(ver, af), br = rk.get(ver, bf);
    if (ar > br) {
        fa.mod(ver, bf, af);
        rk.mod(ver, af, std::max(ar, br + 1));
    } else {
        fa.mod(ver, af, bf);
        rk.mod(ver, bf, std::max(br, ar + 1));
    }
}

i32 op, a, b;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    iota(fa.a + 1, fa.a + n + 1, 1);  // 每一个点的初始父亲是自己
    fa.init(n);
    rk.init(n);

    while (m--) {
        cin >> op >> a;
        if (op == 1) {
            cin >> b;
            merge(a, b);
        } else if (op == 2) {
            fa.cpyver(a), rk.cpyver(a);
        } else {
            fa.cpyver(ver), rk.cpyver(ver);
            cin >> b;
            cout << (find(a) == find(b)) << '\n';
        }
        ++ver;
        // std::cerr << fa.ver << std::endl;
    }

    return 0;
}