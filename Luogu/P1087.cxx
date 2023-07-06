#include <string>
#include <iostream>

using namespace std;

constexpr int N = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;

struct Node {
    short int type; // 2:F 0:B 1:I
    string data;
    Node* lc=NULL;
    Node* rc=NULL;
} tree[4*N];

Node* idx=tree;
int n;
char ring[3] = {'B','I','F'};

void build(Node& node) {
    if (node.data.size()==1) {
        if (node.data == "1") {
            node.type=1;
        } else {
            node.type=0;
        }
        return ;
    }

    node.lc = ++ idx;
    node.rc = ++ idx;
    (*node.lc).data = node.data.substr(0,node.data.size() >> 1); 
    (*node.rc).data = node.data.substr(node.data.size() >> 1,node.data.size());
    
    build(*node.lc); build(*node.rc); 
    
    if (node.lc->type == 0 && node.rc->type == 0) {
        node.type = 0;
    } else if (node.lc->type == 1 && node.rc->type == 1) {
        node.type = 1;
    } else {
        node.type = 2;
    }
}

void ans(Node& now) {
    if (now.lc != NULL) {
        ans(*now.lc);
        ans(*now.rc);
    }
    cout << ring[now.type];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> tree[0].data;    

    build(tree[0]);
    ans(tree[0]);

    return 0;
}
