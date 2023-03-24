#include <iostream>

#define N 200010
#define endl '\n'

using std::cin;
using std::cout;


int n,l,r,f[N];
int q[N], head, tail;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> l >> r;

    for (int i = 0; i <= n+1; i ++) {
        cin >> f[i];
    }

    head = 0; tail = -1;
    q[++tail] = n;
    for (int i = n-l; i >= 0; i ++) {
        while (head <= tail && f[q[head]] > i+r) {
            ++ head;
        }

        f[i] += f[q[head]];

        while (head <= tail && f[q[tail]] <= f[i]) {
            -- tail;
        }

        f[++tail] = i;
    }
    cout << f[0] << endl;

    return 0;
}