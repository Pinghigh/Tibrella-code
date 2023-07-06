#include <iostream>

using namespace std;

#define N 50010

int l, n, m;
int dis[N];

bool check(int x) {
    int cnt = 0;
    int idx = 0;
    for (int i = 1; i <= n + 1; ++i) {
        // cout << "---cnt:" << cnt << " i:" << i << " idx:" << idx << " dis:" << dis[i] - dis[idx] << endl;

        if (dis[i] - dis[idx] < x) {
            ++cnt;
        } else {
            idx = i;
        }
    }
    return (cnt <= m);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> l >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> dis[i];
    }
    dis[n + 1] = l;

    int lb, rb, mid;
    lb = 1, rb = l;
    while (lb < rb) {
        // cout << "lb:" << lb << " rb:" << rb << endl;
        mid = (lb + rb + 1) >> 1;
        if (check(mid)) {
            lb = mid;
        } else {
            rb = mid - 1;
        }
    }

    cout << rb;

    return 0;
}
