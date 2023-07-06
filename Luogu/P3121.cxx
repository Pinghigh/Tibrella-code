#include <iostream>
#include <queue>
#include <string>

using std::cin;
using std::cout;
using std::string;

using i32 = int;
using i8 = char;

#define N 100005

struct Node {
    i32 son[26], fail;
    bool end;
    i32 length;
} trie[N * 26];
i32 tot;

void insert(string& s) {
    i32 i = 0;
    Node* nod;
    nod = trie + i;
    for (auto c : s) {
        c -= 'a';
        if (!nod->son[c]) nod->son[c] = ++tot;
        i = nod->son[c];
        nod = trie + i;
    }
    nod->end = true;
    nod->length = s.length();
}

void build() {
    std::queue<i32> q;
    Node* nod = trie;
    for (i8 i = 0; i < 26; ++i) {
        if (nod->son[i]) q.push(nod->son[i]);
    }
    while (q.size()) {
        i32 idx = q.front();
        q.pop();
        nod = trie + idx;
        for (i8 i = 0; i < 26; ++i) {
            if (nod->son[i]) {
                trie[nod->son[i]].fail = trie[nod->fail].son[i];
                q.push(nod->son[i]);
            } else
                nod->son[i] = trie[nod->fail].son[i];
        }
    }
}

string t, s;
i32 n;

i32 zifu[N];
i32 ptr[N];
i32 top;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        insert(s);
    }

    build();

    i32 idx = 0;
    Node* nod;
    i32 i = 0, len = t.size();
    while (i < len) {
        ++top;
        char c = t[i] - 'a';
        nod = trie + idx;
        idx = nod->son[c];
        nod = trie + idx;
        zifu[top] = i;
        ptr[top] = idx;
        if (nod->end) {
            top -= nod->length;
            idx = (!top) ? 0 : ptr[top];
            nod = trie + idx;
        }
        ++i;
    }

    // cout << zifu + 1 << '\n';
    // t.resize(N);
    for (int i = 1; i <= top; ++i)
        cout << t[zifu[i]];

    return 0;
}