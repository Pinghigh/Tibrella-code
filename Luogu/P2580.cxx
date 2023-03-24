#include <array>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

#define SON 30
#define N 500005
#define endl '\n'

struct Node {
    std::array<Node*, SON> son;
    int cnt;
    bool st;
} trie[N];

string s;
int n;
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

using sint = short int;

sint query(string& s) {
    Node* pos = trie;
    for (auto c : s) {
        if (!pos->son[c - 'a']) return -1;
        pos = pos->son[c - 'a'];
    }
    if (pos->st)
        return 1;
    else if (!pos->cnt)
        return -1;
    else {
        pos->st = 1;
        return 0;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(nullptr)->tie(nullptr);

    cin >> n;
    while (n--) {
        cin >> s;
        insert(s);
    }
    cin >> n;
    while (n--) {
        cin >> s;
        sint res = query(s);
        if (res == -1)
            cout << "WRONG" << endl;
        else if (res == 0)
            cout << "OK" << endl;
        else
            cout << "REPEAT" << endl;
    }

    return 0;
}