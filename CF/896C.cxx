#include <iostream>
#include <set>

using std::cin;
using std::cout;

using std::set;

using i64 = long long;

struct Node {
    mutable i64 v;
    i64 l, r;

    Node(i64 l, i64 r, i64 v) : l(l), r(r), v(v) {}

    bool operator<(const Node& b) {
        return l < b.l;
    }
};

set<Node> s;

using sit = set<Node>::iterator;

sit split(i64 pos) {
    sit it = s.lower_bound(Node(pos));
    if (it != s.end() && it->l == pos) return it;

    --it;
    if (it->r < pos) return s.end();
    i64 l = it->l, r = it->r, v = it->v;
    s.erase(it);
    s.insert(Node(l, pos - 1, v));
    return s.insert(Node(pos, r, v)).first;
}

sit assign(i64 l, i64 r, i64 v) {
    sit itr = split(r + 1), itl = split(l);  // r 在 l 后面，先裂后，后裂前，防止迭代器变化或者左区间被偷家
    s.erase(itl);
    s.erase(itr);
    s.insert(Node(l, r, v));
}

void add(i64 l, i64 r, i64 x) {
    sit itr = split(r + 1), itl = split(l); // 为了方便修改，整个左闭右开
    for (auto it = itl, it != itr, ++it) {

    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    return 0;
}