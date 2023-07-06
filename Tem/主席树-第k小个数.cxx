#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::sort;
using std::vector;
#define endl '\n'
#define N 100514
#define M 10514

using lint = long long;

lint n, m;
lint ori[N];
vector<int> nums;

struct Node {
    lint l, r, mid;
    Node *lc, *rc;
    lint cnt;
    void init(lint _x, lint _y) {
        l = _x;
        r = _y;
        mid = l + r >> 1;
    }
} tree[N * 4 + M * 17];  // 4*n + nlogn
Node* root[M];
Node* idx = tree;
Node none;

lint find(lint x) {
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

void push_up(Node* nod) {
    nod->cnt = nod->lc->cnt + nod->rc->cnt;
}

Node* build(lint l, lint r) {  // 显然可持久化线段树建树之后需要返回一个根节点，所以写一个比较方便的返回结点指针的 build
    Node* nod = ++idx;
    nod->init(l, r);
    if (l == r) {
        nod->lc = nod->rc = &none;
        return nod;
    }
    nod->lc = build(nod->l, nod->mid);
    nod->rc = build(nod->mid + 1, nod->r);

    return nod;
}

Node* insert(Node* pre, lint l, lint r, lint x) {
    Node* nod = ++idx;
    *nod = *pre;
    nod->init(l, r);
    if (l == r) {
        ++nod->cnt;
        return nod;
    }
    if (x <= nod->mid) {
        nod->lc = insert(pre->lc, pre->lc->l, pre->lc->r, x);
    } else {
        nod->rc = insert(pre->rc, pre->rc->l, pre->rc->r, x);
    }
    push_up(nod);
    return nod;
}

lint query(Node* now, Node* prev, lint l, lint r, lint k) {
    if (l == r) return r;
    lint cnt = now->lc->cnt - prev->lc->cnt;

    if (k <= cnt) {
        return query(now->lc, prev->lc, prev->lc->l, prev->lc->r, k);
    } else {
        return query(now->rc, prev->rc, prev->rc->l, prev->rc->r, k - cnt);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    none.lc = none.rc = &none;

    cin >> n >> m;
    for (lint i = 1; i <= n; ++i) {
        cin >> ori[i];
        nums.push_back(ori[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    root[0] = build(0, nums.size() - 1);

    for (lint i = 1; i <= n; ++i) {
        root[i] = insert(root[i - 1], 0, nums.size() - 1, find(ori[i]));
    }

    while (m--) {
        lint l, r, k;
        cin >> l >> r >> k;
        cout << nums[query(root[r], root[l - 1], 0, nums.size() - 1, k)] << endl;
    }

    return 0;
}