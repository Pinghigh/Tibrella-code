#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

using std::cin;
using std::cout;

#define N 61
#define LENGTH 101
#define M 101

using i32 = int;
using i64 = long long;

struct Node {
    i32 son[26], fail;
    i32 cnt;
    bool illegal;
} trie[N * 26 * LENGTH];
i32 tot;
i32 end[N];

void insert(const std::string& s) {
    i32 cur = 0;
    for (auto c : s) {
        c -= 'A';
        cur = (trie[cur].son[c]) ? trie[cur].son[c] : trie[cur].son[c] = ++tot;
    }
    trie[cur].illegal = true;
}

void build() {
    std::queue<i32> q;
    for (i32 i = 0; i < 26; ++i)
        if (trie[0].son[i]) q.emplace(trie[0].son[i]);
    while (!q.empty()) {
        Node& nod = trie[q.front()];
        q.pop();
        i32 last_fail = nod.fail;
        for (i32 i = 0; i < 26; ++i) {
            i32& to = nod.son[i];
            if (to)
                q.emplace(to), trie[to].fail = trie[last_fail].son[i], trie[to].illegal |= trie[trie[last_fail].son[i]].illegal;
            else
                to = trie[last_fail].son[i];
        }
    }
}

i32 f[M][N * M];

constexpr i32 mod = 1e4 + 7;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    i32 n, m;
    cin >> n >> m;
    for (i32 i = 1; i <= n; ++i) {
        std::string t;
        cin >> t;
        insert(t);
    }

    build();

    f[0][0] = 1;
    for (i32 i = 0; i < m; ++i)
        for (i32 j = 0; j <= tot; ++j)
            for (char c = 0; c < 26; ++c)
                if (!trie[trie[j].son[c]].illegal) f[i + 1][trie[j].son[c]] = (f[i + 1][trie[j].son[c]] + f[i][j]) % mod;

    i32 ans = 1;
    for (i32 i = 1; i <= m; ++i)
        (ans *= 26) %= mod;

    for (i32 i = 0; i <= tot; ++i)
        ans = (ans - f[m][i]) % mod;
    cout << (ans + mod) % mod;

    return 0;
}