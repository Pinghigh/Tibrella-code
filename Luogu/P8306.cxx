#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#define MAX 3000005

struct Node {
    std::array<Node*, '{' - '0' + 1> son;
    char data;
    int cnt;
    int siz;
} trie[MAX];

using std::string;

Node* idx = trie;

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
    nod->siz = nod->cnt;
    for (auto i : nod->son) {
        if (!i) continue;
        dfs(i);
        nod->siz += i->siz;
    }
    std::cout << nod->data << std::endl;
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

int n, q;
string str;
int t;

// #define cin fin
// #define cout fout

int main() {
    // std::ifstream fin("1.in", std::ios::in);
    // std::ofstream fout("1.out", std::ios::out);

    std::ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;

    cin >> n >> q;

    while (n--) {
        cin >> str;
        insert(str);
    }
    dfs(trie);
    // for (Node* nod = trie; nod != idx + 1; ++nod) {
    //     nod->siz += nod->cnt;
    // }

    // while (q--) {
    //     cin >> str;
    //     cout << query(str) << endl;
    // }

    return 0;
}