#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::max;

const char endl = '\n';

#define N 200005

int a[N], f[N], m[N];
int n;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(f, 128, sizeof f);
    memset(m, 128, sizeof m);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        f[i] = max(f[i - 1], 0) + a[i];
        m[i] = max(f[i], m[i - 1]);
    }

    cout << m[n];

    return 0;
}