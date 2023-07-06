// https://www.acwing.com/problem/content/837/

#include <iostream>
#include <string>

#define N 200005
#define endl '\n'

using std::string;

struct Node {
    Node* son[26];
    int cnt;
    char letter;
} trie[N];
Node* idx = trie;

void insert(string& s) {
    Node* pos = trie;
    for (auto c : s) {
        if (!pos->son[c - 'a']) {
            pos->son[c - 'a'] = ++idx;
        }
        pos = pos->son[c - 'a'];
    }
    ++pos->cnt;
}

int query(string& s) {
    Node* pos = trie;
    for (auto c : s) {
        if (pos->son[c - 'a'])
            pos = pos->son[c - 'a'];
        else
            return 0;
    }
    return pos->cnt;
}

string str;
char beh;
int n;

using std::cin;
using std::cout;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    while (n--) {
        cin >> beh >> str;
        switch (beh) {
            case ('I'): insert(str); break;
            case ('Q'): cout << query(str) << endl; break;
        }
    }

    return 0;
}