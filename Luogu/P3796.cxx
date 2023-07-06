#include <iostream>
#include <queue>
#include <string>

using std::cin;
using std::cout;
using std::string;
using i32 = int;

#define N 1550

string s[N], t;
i32 n;

struct Node {
    i32 son[26], fail;
    i32 cnt;
    i32 id;
} trie[N * 27];
i32 tot;

i32 end[N];

void insert(string& str, i32 id) {
    i32 idx = 0;
    for (auto& c : str) {
        if (!trie[idx].son[c - 'a']) {
            trie[idx].son[c - 'a'] = ++tot;
        }
        idx = trie[idx].son[c - 'a'];
    }
    end[id] = idx;
    trie[idx].id = id;
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

void match(string& str) {
    i32 nod = 0;
    for (auto c : str) {
        c -= 'a';
        nod = trie[nod].son[c];
        for (i32 nxt = nod; nxt; nxt = trie[nxt].fail) {
            ++trie[nxt].cnt;
        }
    }
}

#include <cstring>

void clean() {
    memset(trie, 0, sizeof trie);
    memset(end, 0, sizeof end);
    tot = 0;
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        insert(s[i], i);
    }
    build();
    cin >> t;

    match(t);
    // cout << "SUCCESS\n";
    // calc(root);
    i32 c = 0;
    for (int i = 1; i <= n; ++i) {
        c = std::max(c, trie[end[i]].cnt);
    }
    cout << c << '\n';
    for (int i = 1; i <= n; ++i) {
        if (trie[end[i]].cnt == c) cout << s[i] << '\n';
    }
    clean();
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while ((cin >> n), n) {
        solve();
    }

    return 0;
}