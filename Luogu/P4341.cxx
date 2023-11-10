#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 3001

struct Node {
    i32 son[2];
    i32 cnt;
} trie[N * N];
i32 tot = 0;

void insert(char* s, i32 len) {
    i32 cur = 0;
    for (i32 i = 0; i < len; ++i) {
        cur = trie[cur].son[s[i]] ? trie[cur].son[s[i]] : (trie[cur].son[s[i]] = ++tot);
        ++trie[cur].cnt;
    }
}

void dfs(i32 nod) {
    Node& u = trie[nod];
    if (u.son[0] && trie[u.son[0]].cnt > 1) {
        cout << trie[u.son[0]].cnt << '\n';
        dfs(u.son[0]);
    }
    if (u.son[1] && trie[u.son[1]].cnt > 1) {
        cout << trie[u.son[1]].cnt << '\n';
        dfs(u.son[1]);
    }
}

char s[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    i32 n;
    cin >> n >> s;
    for (i32 i = 0; i < n; ++i)
        s[i] -= '0';
    for (int i = 1; i <= n; ++i)
        insert(s + i - 1, n - i + 1);

    dfs(0);

    return 0;
}