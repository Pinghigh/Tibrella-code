#include <iostream>
#include <climits>

using namespace std;

#define N 500514

int tree[N];
int t1,t2,t3;
char beh;
int n,m;

int lowbit(int x) {
    return (x&-x);
}

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
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
        cin >> t1;
        modify(i,t1);
        modify(i+1,-t1);
    }

    while (m --) {
        cin >> beh;
        if (beh == '1') {
            cin >> t1 >> t2 >> t3;
            modify(t1,t3);
            modify(t2+1,-t3);
        } else {
            cin >> t1;
            cout << query(t1) << endl;
        }
    }

    return 0;
}