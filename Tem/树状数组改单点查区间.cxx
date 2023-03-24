#include <climits>
#include <iostream>

using std::cin;
using std::cout;
#define endl '\n'
#define N 500514

int lowbit(int& x) {
    return x & (-x);
}

int tree[N];
int n, m;
char beh;
int t1, t2;

void modify(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tree[i] += v;
    }
}

int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += tree[i];
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> t1;
        modify(i, t1);
    }

    while (m--) {
        cin >> beh >> t1 >> t2;
        switch (beh) {
            case ('1'): modify(t1, t2); break;
            case ('2'): cout << query(t2) - query(t1 - 1) << endl; break;
        }
    }

    return 0;
}