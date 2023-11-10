#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i64 = long long;

#define N 200006

i64 f[N], ans;

i64 n;

int main() {
    cin >> n;

    for (i64 i = n; i; --i) {
        f[i] = n/i;
        f[i] *= f[i];
        for (i64 j = i << 1; j <= n; j += i) f[i] -= f[j];
        ans += f[i]*i;
    }
    ans -= n*(n+1)>>1;
    ans >>=1;
    cout << ans;

    return 0;
}