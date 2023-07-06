#include <iostream>

using namespace std;

#define N 1000010 

struct Node {
    Node *lc=NULL,*rc=NULL;
    int data;
} tree[N];

int n;
Node *idx = tree;
int l,r;
int res;

int query(Node& now) {
    if ()
}

int main() {
    ios::sync_with_stdio();
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++ i) {
        cin >> tree[i].data;
    }
    for (int i = 0; i < n; ++ i) {
        cin >> l >> r;
        if (l != -1) {
            tree[i].lc=&tree[l-1];
        }
        if (r != -1) {
            tree[i].rc=&tree[r-1];
        }
    }

    query(tree[0]);

    return 0;
}