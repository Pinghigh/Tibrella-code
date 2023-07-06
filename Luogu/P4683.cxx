#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <deque>
#include <string>


#define MAX 30005

struct Node {
    std::array<Node*, 80> son;
    char data;
    int cnt;
    int siz;
} trie[MAX];

using std::string;

Node* idx = trie;

std::deque<char> q;

void insert(string& s) {
    Node* pos = trie;
    for (auto c : s) {
        if (!pos->son[c - '0']) {
            pos->son[c - '0'] = ++idx;
            idx->data = c;
        }
        ++(pos->siz);
        pos = pos->son[c - '0'];
    }
    ++(pos->cnt);
    ++pos->siz;
}

void dfs(Node* nod) {
    if (nod != trie) q.push_back(nod->data);

    for (auto i : nod->son) {
        if (!i) continue;
        dfs(i);
        nod->siz += i->siz;
    }
    if (nod->cnt > 0) q.push_back('P');
    q.push_back('-');

    // std::cout << nod->cnt << ' ' << nod->siz << std::endl;
}

int query(string& s) {
    Node* pos = trie;
    for (auto c : s) {
        if (!pos->son[c - '0']) {
            return 0;
        }
        pos = pos->son[c - '0'];
    }
    return pos->siz;
}

using std::cin;
using std::cout;

#define endl '\n'

int n;
string str;
int t;

int main() {

    std::ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    while (n--) {
        cin >> str;
        insert(str);
    }
    dfs(trie);
    while(q.back() == '-') {
        q.pop_back();
    }
    cout << q.size() << endl;
    for (auto c : q) {
        cout << c << endl;
    }

    return 0;
}