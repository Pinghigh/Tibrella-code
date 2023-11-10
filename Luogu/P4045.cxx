#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

using std::cin;
using std::cout;

using u8 = unsigned char;
using u16 = unsigned short;
using i32 = int;
using i64 = long;
using u32 = unsigned;
using u64 = unsigned long;

#define N 11
#define L 11

struct Node {
    u32 son[26], fail;
    u16 end;
} trie[N * L];
i32 tot;
void insert(std::string& str, const u8 id) {
    i32 cur = 0;
    for (auto& c : str) {
        c -= 'a';
        cur = trie[cur].son[c] ? trie[cur].son[c] : (trie[cur].son[c] = ++tot);
    }
    trie[cur].end |= 1 << id;
}

void build() {
    std::queue<i32> q;
    for (u8 c = 0; c < 26; ++c)
        if (trie[0].son[c]) q.emplace(trie[0].son[c]);
    while (!q.empty()) {
        Node& nod = trie[q.front()];
        Node& lfail = trie[nod.fail];
        q.pop();
        for (u8 c = 0; c < 26; ++c) {
            if (nod.son[c]) {
                trie[nod.son[c]].fail = lfail.son[c];
                q.emplace(nod.son[c]);
            } else
                nod.son[c] = lfail.son[c];
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    return 0;
}