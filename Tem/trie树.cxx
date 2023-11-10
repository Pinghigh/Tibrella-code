#include <array> 
#include <iostream>
#include <string>

#define MAX 3000005

struct Node {
    std::array<Node*, '{' - '0' + 1> son;
    // int cnt;
    int siz;
} trie[MAX];

using std::string;

Node* idx = trie;

void insert(string& s) {
    Node* pos = trie;
    for (auto c : s) {
        c -= '0';
        if (!pos->son[c]) pos->son[c] = ++idx;
        pos = pos->son[c];
        ++(pos->siz);
    }
    // ++(pos->cnt);
    // ++pos->siz;
}

// void dfs(Node* nod) {
//     nod->siz = nod->cnt;
//     for (auto i : nod->son) {
//         if (!i) continue;
//         dfs(i);
//         nod->siz += i->siz;
//     }
//     // std::cout << nod->cnt << ' ' << nod->siz << std::endl;
// }

int query(string& s) {
    Node* pos = trie;
    for (auto c : s) {
        c -= '0';
        if (!pos->son[c]) return 0;
        pos = pos->son[c];
    }
    return pos->siz;
}

using std::cin;
using std::cout;

#define endl '\n'

int n, q;
string str;
int t;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;

    while (t--) {
        cin >> n >> q;
        while (n--) {
            cin >> str;
            insert(str);
        }
        while (q--) {
            cin >> str;
            cout << query(str) << endl;
        }
        if (t) {
            ++idx;
            for (; idx != trie; --idx) {
                idx->siz = 0;
                idx->son.fill(0);
            }
            idx = trie;
            idx->siz = 0, idx->son.fill(0);
        }
    }

    return 0;
}