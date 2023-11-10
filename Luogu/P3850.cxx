#include <iostream>
#include <random>
#include <string>
#include <chrono>

using std::cin;
using std::cout;
using std::string;

using u32 = int;
using i32 = int;
using i64 = long long;

std::mt19937 rd(std::chrono::steady_clock::now().time_since_epoch().count() ^ 485691787711274ull);

#define N 300

struct Node {
    Node *lc, *rc;
    u32 val;
    u32 siz;
    u32 ext;

    void push_up() {
        siz = lc->siz + rc->siz + 1;
    }
} space[N];
Node* tot = space, *root, *null = space;
string s[N];
i32 stot;

Node* new_node() {
    Node* res = ++tot;
    res->ext = rd();
    res->lc = res->rc = null;
    res->siz = 1;
    return res;
}

void split(Node* cur, i32 rk, Node*& l, Node*& r) {
    if (cur == null) l = null, r = null;
    else {
        if (cur->lc->siz >= rk) {
            r = cur;
            split(cur->lc, rk, l, cur->lc);
        } else {
            l = cur;
            split(cur->rc, rk - cur->lc->siz - 1, cur->rc, r);
        }
        cur->push_up();
    }
}

Node* merge(Node* l, Node* r) {
    if (l == null) return r;
    else if (r == null) return l;
    else {
        if (l->ext < r->ext) {
            l->rc = merge(l->rc, r);
            l->push_up();
            return l;
        } else {
            r->lc = merge(l, r->lc);
            r->push_up();
            return r;
        }
    }
}
Node* query(Node* cur, u32 rk) {
    // cout << cur->lc->siz << ' ' << rk << '\n';
    for (;;) {
        if (cur == null) return null;

        if (cur->lc->siz >= rk) cur = cur->lc;
        else if (cur->lc->siz == rk - 1) return cur;
        else rk = rk - cur->lc->siz - 1, cur = cur->rc;
    }
	// Node *a = null, *b = null, *c = null, *d = null;
	// split(cur, rk, a, b); split(a, rk-1, c, d);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    null->lc = null->rc = null;

    i32 n;
    cin >> n;
    for (i32 i = 1; i <= n; ++ i) {
        Node* nod = new_node();
        cin >> s[++stot];
        nod->val = stot;
        if (!root) root = nod;
        else root = merge(root, nod);
    }
    i32 m;
    cin >> m;
    for (i32 i = 1; i <= m; ++ i) {
        i32 id;
        Node* nod = new_node();
        cin >> s[++stot] >> id;
        nod->val = stot;
        Node *a = null, *b = null;
        split(root, id, a, b);   
        root = merge(merge(a, nod), b);  
    }
    i32 q;
    cin >> q;
    while (q--) {
        i32 rk;
        cin >> rk;
        cout << s[query(root, rk+1)->val] << '\n';
		
		// Node *a = null, *b = null, *c = null, *d = null;
		// split(root, rk+2, a, b); split(a, rk+1, c, d);
		// cout << s[c->val] << '\n';
		// root = merge(merge(c, d), b);
    }

    return 0;
}