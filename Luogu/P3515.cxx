#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>

using std::cin;
using std::cout;

using i32 = long long;
using i64 = long long;
using u64 = unsigned long long;
using f128 = long double;

#define N 500005

f128 p[N], a[N];
i32 n;

struct d {
    i32 l, r;
    i32 p;
};

template <typename T, u64 lsiz>
class list {
private:
    struct Node {
        T val;
        Node *pre, *nxt;
    } space[lsiz];
    Node *tot, *rubbish_bin[lsiz];
    u64 bintop;

    Node *head, *tail;

    Node* new_node() {
        if (bintop)
            return rubbish_bin[bintop--];
        else
            return ++tot;
    }

    void del_node(Node* nod) {
        rubbish_bin[++bintop] = nod;
    }

    u64 siz;

public:
    list() {
        tot = space;
        bintop = siz = 0;
        head = tail = nullptr;
    }

    bool empty() {
        return !siz;
    }

    template <class... Args>
    void push_front(const Args&... args) {
        Node* nw = new_node();
        *nw = (Node){ args..., nullptr, head };
        if (head) head->pre = nw;
        head = nw;
        if (!tail) tail = head;
    }

    template <class... Args>
    void push_back(Args... args) {
        Node* nw = new_node();
        *nw = (Node){ args..., tail, nullptr };
        if (tail) tail->nxt = nw;
        tail = nw;
        if (!head) head = tail;
        ++siz;
    }

    void pop_front() {
        --siz;
        del_node(head);
        if (head->nxt) head->nxt->pre = nullptr;
        head = head->nxt;
    }

    void pop_back() {
        --siz;
        del_node(tail);
        if (tail->pre) tail->pre->nxt = nullptr;
        tail = tail->pre;
    }

    T& front() {
        return head->val;
    }
    T& back() {
        return tail->val;
    }
    u64 size() {
        return siz;
    }

    void clear() {
        while (siz)
            pop_back();
    }
};

list<d, N> q;

f128 calc(i32 i, i32 j) {
    return a[j] - a[i] + sqrt(std::abs((f128)(i * 1.0 - j)));
}

i32 get_pos(const d& x, const i32& i) {
    i32 l = x.l, r = x.r, j = x.p, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (calc(mid, j) <= calc(mid, i))
            r = mid;
        else
            l = mid + 1;
    }
    return r;
}

void solve() {
    q.push_back((d){ 1, n, 0 });
    for (i32 i = 1; i <= n; ++i) {
        if (q.size()) {
            if (q.front().r == i - 1)
                q.pop_front();
            else
                q.front().l = i;
        }
        p[i] = std::max(p[i], calc(i, q.front().p));

        i32 pos = q.back().l;

        while (q.size() && calc(q.back().l, q.back().p) <= calc(q.back().l, i)) {
            pos = q.back().l;
            q.pop_back();
        }

        if (q.empty())
            q.push_back((d){ i + 1, n, i });
        else {
            if (calc(q.back().r, q.back().p) >= calc(q.back().r, i)) {
                pos = q.back().r + 1;
            } else {
                pos = get_pos(q.back(), i);
            }

            if (pos <= n) {
                q.back().r = pos - 1;
                q.push_back((d){ pos, n, i });
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i)
        cin >> a[i];

    solve();
    q.clear();
    std::reverse(a + 1, a + n + 1);
    std::reverse(p + 1, p + n + 1);
    solve();
    std::reverse(p + 1, p + n + 1);
    for (i32 i = 1; i <= n; ++i)
        cout << (i32)std::ceil(p[i]) << '\n';

    return 0;
}