#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

using i8 = char;
using u64 = unsigned long long;
using i32 = int;
using i64 = long long;
using f64 = double;

#define N 200005

const i32 modx = 39989;
const u64 mody = 1e9;
const f64 inf = 1e9;

struct line {
    i32 id;
    f64 k, b;
};

f64 calc(line* l, i32 x) {
    if (!l)
        return -inf;
    else
        return l->k * x + l->b;
}

std::deque<line> l;

struct Node {
    line* lx;
    i32 l, r, mid;

    void init(i32 L, i32 R) {
        l = L, r = R;
        mid = (l + r) >> 1;
    }
} stree[N << 2];

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

const f64 eps = 1e-9;

i8 cmp(f64 a, f64 b) {
    if (a - b > eps)
        return 1;
    else if (b - a > eps)
        return -1;
    else
        return 0;
}

void build(i32 u, i32 l, i32 r) {
    Node& nod = stree[u];
    nod.init(l, r);
    if (l != r) return build(lc(u), l, nod.mid), build(rc(u), nod.mid + 1, r);
}

void update(i32 u, line& lx) {
    Node& nod = stree[u];
    line *&b = nod.lx, *a = &lx;
    if (cmp(calc(a, nod.mid), calc(b, nod.mid)) == 1) std::swap(a, b);  // 不优的下传
    i8 cmpl = cmp(calc(a, nod.l), calc(b, nod.l)), cmpr = cmp(calc(a, nod.r), calc(b, nod.r));
    if (cmpl == 1 || (cmpl == 0 && a->id < b->id))
        return update(lc(u), *a);
    else if (cmpr == 1 || (cmpr == 0 && a->id < b->id))
        return update(rc(u), *a);
}

void insert(i32 u, i32 l, i32 r, line& lx) {
    Node& nod = stree[u];
    if (l <= nod.l && r >= nod.r)
        update(u, lx);
    else {
        if (l <= nod.mid) insert(lc(u), l, r, lx);
        if (r > nod.mid) insert(rc(u), l, r, lx);
    }
}

struct pair {
    f64 val;
    line* x;

    bool operator>(const pair& b) const {
        return val > b.val || (val == b.val && x->id > b.x->id);
    }
    bool operator<(const pair& b) const {
        return val < b.val || (val == b.val && x->id < b.x->id);
    }
};

pair pmax(pair x, pair y) {  // pair max函数
    if (cmp(x.val, y.val) == -1)
        return y;
    else if (cmp(x.val, y.val) == 1)
        return x;
    else if (!x.x)
        return y;
    else if (!y.x)
        return x;
    else
        return x.x->id < y.x->id ? x : y;
}

pair query(i32 u, i32 x) {
    Node& nod = stree[u];
    // if (nod.lx) std::cerr << nod.lx->id << ' ';
    if (nod.l > x || nod.r < x)
        return { -inf, nullptr };
    else if (nod.l == nod.r)
        return { calc(nod.lx, x), nod.lx };
    else {
        pair l = query(lc(u), x), r = query(rc(u), x);
        // std::cerr << "DEBUG " << (l.x != nullptr ? l.x->id : 0) << ' ' << (l.x != nullptr ? l.x->id : 0) << ' ' << (l.x != nullptr ? l.x->id : 0) << '\n';
        // std::cerr << l.val << ' ' << r.val << ' ' << calc(nod.lx, x) << '\n';
        return pmax(pmax(l, r), (pair){ calc(nod.lx, x), nod.lx });
    }
}

i32 ax, ay, bx, by;
i32 n;
i32 op;
i32 lastans;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    build(1, 1, modx);

    cin >> n;
    i32 id = 0;
    while (n--) {
        cin >> op;
        if (op) {
            cin >> ax >> ay >> bx >> by;
            ax = (ax + lastans - 1 + modx) % modx + 1;
            bx = (bx + lastans - 1 + modx) % modx + 1;
            ay = (ay + lastans - 1 + mody) % mody + 1;
            by = (by + lastans - 1 + mody) % mody + 1;

            if (ax > bx) std::swap(ax, bx), std::swap(ay, by);

            if (ax == bx)
                l.emplace_back((line){ ++id, 0, std::max(ay, by) * 1.0 });
            else
                l.emplace_back((line){ ++id, 1.0 * (ay - by) / (ax - bx), by - 1.0 * (ay - by) / (ax - bx) * bx });

            std::cerr << std::fixed << ax << ' ' << ay << ' ' << bx << ' ' << by << ' ' << l.back().k << ' ' << l.back().b << '\n';
            insert(1, ax, bx, l.back());
        } else {
            cin >> ax;
            ax = (ax + lastans - 1 + modx) % modx + 1;
            line* lx = query(1, ax).x;
            if (!lx)
                lastans = 0;
            else
                lastans = lx->id;
            cout << lastans << '\n';
        }
    }
    std::cerr << calc(&l.front(), 1);

    return 0;
}