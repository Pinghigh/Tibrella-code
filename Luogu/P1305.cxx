#include <iostream>

using namespace std;

#define N 30

struct Node {
    char data;
    Node* lc = NULL;
    Node* rc = NULL;
} tree[N];

int n;
char no, l, r;
bool flag;
Node* root;

void ans(Node* idx) {
    cout << idx->data;
    if (idx->lc != NULL) ans(idx->lc);
    if (idx->rc != NULL) ans(idx->rc);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> no >> l >> r;
        tree[no - 'a'].data = no;
        if (!flag) {
            root = &tree[no - 'a'];
            flag = 1;
        }
        if (l != '*') {
            tree[no - 'a'].lc = &tree[l - 'a'];
        }
        if (r != '*') {
            tree[no - 'a'].rc = &tree[r - 'a'];
        }
    }

    ans(root);

    return 0;
}
