#include <cstring>
#include <iostream>


#define N 200010

using namespace std;

int n, l, r, f[N];
int q[N], head, tail;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> l >> r;

    for (int i = 0; i <= n + 1; i++) {
        cin >> f[i];
    }

    head = 0;
    tail = -1;
    q[++tail] = n;
    for (int i = n - l + 1; i >= 0; i--) {
        if (head <= tail && q[head] > i + r) head++;
        while (head <= tail && f[q[tail]] <= f[i + l])
            tail--;
        q[++tail] = i + l;
        f[i] += f[q[head]];
    }
    cout << f[0];

    return 0;
}