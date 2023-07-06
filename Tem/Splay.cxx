#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

#define N 100005

using i32 = int;
using i64 = long long;

struct Node {
    using nodeptr = Node*;
    nodeptr son[2];
    nodeptr fa;
    i32 val, siz, cnt;

    Node() {
        fa = son[0] = son[1] = nullptr;
    }

    void update() {
        // siz = son[1]->siz + son[0]->siz + 1;
        siz = cnt;
        if (son[0]) siz += son[0]->siz;
        if (son[1]) siz += son[1]->siz;
    }
} space[N];
using nodeptr = Node*;
nodeptr root, rubbish_bin[N], tot = space;
i32 bintop;

void rotate(nodeptr nod) {
    if (!nod->fa) return;
    Node *fa = nod->fa, *gfa = nod->fa->fa;
    bool oripos = fa->son[1] == nod;  // nod 原来是 fa 的哪一个儿子
    if (gfa) gfa->son[fa == gfa->son[1]] = nod;
    nod->fa = gfa;
    fa->son[oripos] = nod->son[oripos ^ 1];  // 解释不了，自己想一下吧
    if (nod->son[oripos ^ 1]) nod->son[oripos ^ 1]->fa = fa;
    nod->son[oripos ^ 1] = fa;
    fa->fa = nod;

    fa->update();
    nod->update();
}

void splay(nodeptr nod, nodeptr pos) {
    if (!nod) return;
    while (nod->fa != pos) {
        Node *fa = nod->fa, *gfa = nod->fa->fa;
        if (gfa != pos) ((gfa->son[0] == fa) ^ (fa->son[0] == nod)) ? rotate(nod) : rotate(fa);
        rotate(nod);
    }
    if (!pos) return root = nod, void();
}

nodeptr newNode(i32 val) {
    nodeptr idx = (bintop) ? (rubbish_bin[bintop--]) : (++tot);
    idx->val = val, idx->cnt = idx->siz = 1;
    idx->son[0] = idx->son[1] = idx->fa = nullptr;
    return idx;
}

void insert(i32 val) {
    nodeptr nod = root, fa = nullptr;
    while (nod && nod->val != val) {
        fa = nod;
        nod = nod->son[nod->val < val];
    }
    if (nod)
        ++nod->cnt;
    else {
        nod = newNode(val);
        nod->fa = fa;
        if (fa) fa->son[fa->val < val] = nod;
    }
    splay(nod, nullptr);
}

// splay nod->val == val，如果不存在，则 splay val 的前驱或者后继
void find(i32 val) {  // 这玩意蛮常用的，毕竟其他操作都要先把节点旋转到根
    nodeptr nod = root;
    if (!nod) return;  // 空
    while (nod->son[nod->val < val] && nod->val != val) {
        nod = nod->son[nod->val < val];
    }
    splay(nod, nullptr);
}

nodeptr getPrev(i32 val) {
    find(val);
    nodeptr nod = root;
    if (nod->val < val) return nod;
    nod = nod->son[0];
    if (!nod) return nullptr;
    while (nod->son[1])
        nod = nod->son[1];
    return nod;
}

nodeptr getNext(i32 val) {
    find(val);
    nodeptr nod = root;
    if (nod->val > val) return nod;
    nod = nod->son[1];
    if (!nod) return nullptr;
    while (nod->son[0])
        nod = nod->son[0];
    return nod;
}

void delNode(nodeptr& nod) {
    rubbish_bin[++bintop] = nod;  // 垃圾回收
    nod = nullptr;
}

void remove(i32 val) {
    nodeptr pre = getPrev(val), nex = getNext(val);
    splay(pre, nullptr);
    splay(nex, pre);  // 前驱旋转到根，后继旋转到前驱的儿子，显然后继是前驱的右儿子，而目标节点是后继的左儿子且为叶子节点
    nodeptr& nod = nex ? nex->son[0] : (pre ? pre->son[1] : root);
    if (--nod->cnt)
        splay(nod, nullptr);
    else {
        if (nod->fa) nod->fa->update();
        delNode(nod);
    }
}

i32 getKth(i32 k) {
    nodeptr nod = root;
    for (;;) {
        i32 lcsiz = nod->son[0] ? nod->son[0]->siz : 0;
        if (lcsiz + nod->cnt < k) {
            k -= lcsiz + nod->cnt;
            nod = nod->son[1];
        } else if (lcsiz >= k)
            nod = nod->son[0];
        else
            return nod->val;
    }
}

i32 getRank(i32 val) {
    find(val);
    return root->son[0] ? root->son[0]->siz + 1 : 1;
}

void dfs(Node* nod) {  // debug
    if (nod->son[0]) {
        cout << nod->val << ' ' << nod->son[0]->val << '\n';
        dfs(nod->son[0]);
    }
    if (nod->son[1]) {
        cout << nod->val << ' ' << nod->son[1]->val << '\n';
        dfs(nod->son[1]);
    }
}

i32 n;
i32 t1, t2;

int main() {
    // freopen("redirection/input", "r", stdin);
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> t1 >> t2;
        // cout << i << ' ';
        // if (t2 == 1105) {
        //     1 + 1;
        // }
        // if (root) cout << root->siz << ' ';
        switch (t1) {
            case (1): insert(t2); break;
            case (2): remove(t2); break;
            case (3): cout << getRank(t2) << std::endl; break;
            case (4): cout << getKth(t2) << std::endl; break;
            case (5): cout << getPrev(t2)->val << std::endl; break;
            case (6): cout << getNext(t2)->val << std::endl; break;
        }
        // dfs(root);
        // cout << '\n';
    }

    return 0;
}