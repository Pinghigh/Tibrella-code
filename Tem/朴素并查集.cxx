// P1551
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define N 5140

int fa[N];
int n, m, p;
int u, v;
int f1, f2;
int k,q;

int find(int node) {
    if (fa[node] == node) return node;
    else return find(fa[node]);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> p;

    for (int i = 1; i <= n; ++ i) fa[i] = i;

    while (m--) {
        cin >> u >> v;
        k = find(u);
        q = find(v);
        if (k != q) fa[k] = q;
    }

    while (p --) {
        cin >> f1 >> f2;
        cout << (find(f1) == find(f2)?"Yes":"No") << endl;
    }

    return 0;
}