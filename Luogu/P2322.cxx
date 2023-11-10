#include <iostream>
#include <string>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 13
#define M 51

struct Node {
    i32 son[26];
    i32 fail;
    i32 state;
    char c;
    bool vis[1 << N];
} trie[N * M];
i32 pre[2000006], ans[2000006];

i32 tot;

void insert(const std::string& str, const i32& id) {
    i32 cur = 0;
    for (auto c : str) {
        c -= 'A';
        cur = trie[cur].son[c] ? trie[cur].son[c] : trie[cur].son[c] = ++tot;
        trie[trie[cur].son[c]].c = c;
    }
    trie[cur].state |= 1 << id;
}

#include <algorithm>
#include <queue>

void build() {
    std::queue<i32> q;
    for (i32 c = 0; c < 26; ++c)
        if (trie[0].son[c]) q.emplace(trie[0].son[c]);
    while (!q.empty()) {
        Node& nod = trie[q.front()];
        Node& lfail = trie[nod.fail];
        q.pop();
        // cout << nod.c << '\n';
        for (i32 c = 0; c < 26; ++c) {
            if (nod.son[c]) {
                trie[nod.son[c]].fail = lfail.son[c];
                trie[nod.son[c]].state |= trie[lfail.son[c]].state;
                q.emplace(nod.son[c]);
            } else
                nod.son[c] = lfail.son[c];
        }
    }
}

std::string s[N];
struct pair {
    Node* nod;
    i32 state, id;
    pair() {
        nod = nullptr, state = 0;
    }
    pair(Node* a, i32 b, i32 c) : nod(a), state(b), id(c) {}
};

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    i32 n;
    cin >> n;
    for (i32 i = 0; i < n; ++i) {
        cin >> s[i];
        insert(s[i], i);
    }
    i32 mxst = (1 << n) - 1;

    build();
    // cout << "FICK" << std::endl;
    i32 cnt = 0;
    std::queue<pair> q;
    q.emplace(trie, 0, cnt);
    while (q.size()) {
        pair cur = q.front();
        q.pop();
        Node* nod = cur.nod;
        if (cur.state == mxst) {
            std::string res;
            while (pre[cur.id]) {
                res += ans[pre[cur.id]] + 'A';
                cur.id = pre[cur.id];
            }
            std::reverse(res.begin(), res.end());
            cout << res;
            return 0;
        } else {
            for (i32 c = 0; c < 26; ++c) {
                i32 nxst = cur.state | nod->state;
                if (!trie[nod->son[c]].vis[nxst]) {
                    trie[nod->son[c]].vis[nxst] = true;
                    // trie[nod->son[c]].prev
                    pre[++cnt] = cur.id;
                    ans[cnt] = c;
                    q.emplace(trie + nod->son[c], nxst, cnt);
                }
            }
        }
    }

    return 0;
}