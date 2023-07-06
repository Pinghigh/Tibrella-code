#include <iostream>
#include <queue>
#include <string>

using std::cin;
using std::cout;
using std::string;
using i32 = int;

#define N 1000006

string s, t;
i32 n;

struct Node {
    i32 son[26], fail;
    i32 cnt;
} trie[N];
i32 tot;

void insert(string& str) {
    i32 idx = 0;
    for (auto& c : str) {
        if (!trie[idx].son[c - 'a']) {
            trie[idx].son[c - 'a'] = ++tot;
        }
        idx = trie[idx].son[c - 'a'];
    }
    ++trie[idx].cnt;
}

void build() {
    std::queue<i32> q;
    for (i32 i = 0; i < 26; ++i)
        if (trie[0].son[i]) q.push(trie[0].son[i]);
    while (!q.empty()) {
        i32 nod = q.front(), lfail = trie[q.front()].fail;
        q.pop();
        for (i32 i = 0; i < 26; ++i) {
            i32& to = trie[nod].son[i];
            if (to) {
                trie[to].fail = trie[lfail].son[i];
                q.push(to);
            } else
                to = trie[lfail].son[i];
        }
    }
}

i32 match(string& str) {
    i32 nod = 0, ans = 0;
    for (auto c : str) {
        c -= 'a';
        nod = trie[nod].son[c];
        for (i32 nxt = nod; nxt && ~trie[nxt].cnt; nxt = trie[nxt].fail) {
            ans += trie[nxt].cnt;
            trie[nxt].cnt = -1;
        }
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        insert(s);
    }

    build();

    cin >> t;

    cout << match(t);

    return 0;
}