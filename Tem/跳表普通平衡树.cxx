#include <iostream>
#include <random>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

std::random_device seed;
std::minstd_rand rng(seed());

const i32 MAX_LEVEL = 7;

#define N 100005

struct Node {
    i32 level;
    i64 key;

    struct ptr {
        Node* pointer;
        i32 span;

        ptr() {
            pointer = nullptr;
            span = 0;
        }
        ptr(Node* x) {
            pointer = x;
            span = 0;
        }
        operator Node*() const& {
            return pointer;
        }
        Node* operator->() const& {
            return pointer;
        }
    } nxt[MAX_LEVEL];

} space[N], *rubbin[N];
Node* tot = space;
Node* head = space;
i32 bintop;

#define new_node() (bintop ? rubbin[bintop--] : ++tot)
#define del_node(x) (rubbin[++bintop] = (x))

i32 level;  // global max level now
i32 length;

i32 random_level() {
    i32 res = 1;
    while (res < MAX_LEVEL && (rng() & 1) && (rng() & 1))
        ++res;
    return res;
}

Node* create_node(const i32& level, const i64& key) {
    Node* res = new_node();
    res->key = key;
    res->level = level;
    return res;
}

void insert(const i64& key) {
    Node* cur = head;
    Node::ptr update[MAX_LEVEL];
    i32 lst_pos[MAX_LEVEL + 1];
    lst_pos[level] = 0;

    for (i32 l = level - 1; l > -1; --l) {
        lst_pos[l] = lst_pos[l + 1];

        while (cur->nxt[l] && cur->nxt[l]->key < key) {
            lst_pos[l] += cur->nxt[l].span;
            cur = cur->nxt[l];
        }
        update[l] = cur;
    }

    i32 lev = random_level();

    if (lev > level) {
        for (i32 i = level; i < lev; ++i) {
            update[i] = head;
            update[i]->nxt[i].span = length;
            lst_pos[i] = 0;
        }
        level = lev;
    }

    cur = create_node(lev, key);

    for (i32 i = 0; i < lev; ++i) {
        cur->nxt[i] = update[i]->nxt[i];
        cur->nxt[i].span = update[i]->nxt[i].span - (lst_pos[0] - lst_pos[i]);
        update[i]->nxt[i].pointer = cur;
        update[i]->nxt[i].span = lst_pos[0] - lst_pos[i] + 1;
    }

    for (i32 i = lev; i < level; ++i)
        ++update[i]->nxt[i].span;

    ++length;
}

void erase(const i64& key) {
    Node* cur = head;
    Node::ptr update[MAX_LEVEL];
    for (i32 l = level - 1; l > -1; --l) {
        while (cur->nxt[l] && cur->nxt[l]->key < key)
            cur = cur->nxt[l];
        update[l] = cur;
    }

    cur = cur->nxt[0];

    for (i32 i = 0; i < level; ++i)
        if (update[i]->nxt[i] == cur)
            update[i]->nxt[i].span += cur->nxt[i].span - 1, update[i]->nxt[i].pointer = cur->nxt[i].pointer;
        else
            --update[i]->nxt[i].span;

    while (level > 1 && !head->nxt[level - 1])
        --level;

    del_node(cur);
    --length;
}

i32 get_rk(const i64& key) {
    Node* cur = head;
    i32 res = 0;
    for (i32 l = level - 1; l > -1; --l) {
        while (cur->nxt[l] && cur->nxt[l]->key < key) {
            res += cur->nxt[l].span;
            cur = cur->nxt[l];
        }
    }
    return res + 1;
}

i64 find_by_rk(i32 k) {
    Node* cur = head;
    for (i32 l = level - 1; l > -1; --l) {
        while (cur->nxt[l] && k - cur->nxt[l].span > 0) {
            k -= cur->nxt[l].span;
            cur = cur->nxt[l];
        }
    }
    return cur->nxt[0]->key;
}

Node* prev(const i64& key) {
    Node* cur = head;
    for (i32 l = level - 1; l > -1; --l) {
        while (cur->nxt[l] && cur->nxt[l]->key < key)
            cur = cur->nxt[l];
    }
    return cur;
}

Node* next(const i64& key) {
    Node* cur = head;
    for (i32 l = level - 1; l > -1; --l) {
        while (cur->nxt[l] && cur->nxt[l]->key < key)
            cur = cur->nxt[l];
    }
    cur = cur->nxt[0];
    while (cur->key == key)
        cur = cur->nxt[0]; // 可能有重复数字，但是后继要严格大于当前点
    return cur;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    i32 op, x;
    cin >> n;
    while (n--) {
        cin >> op >> x;
        switch (op) {
            case (1): insert(x); break;
            case (2): erase(x); break;
            case (3): cout << get_rk(x) << '\n'; break;
            case (4): cout << find_by_rk(x) << '\n'; break;
            case (5): cout << prev(x)->key << '\n'; break;
            case (6): cout << next(x)->key << '\n'; break;
        }
        // cout.flush();
    }

    return 0;
}