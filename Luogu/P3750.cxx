#include <bitset>
#include <cmath>
#include <iostream>

using std::cin;
using std::cout;

using i64 = long long;

const char endl = '\n';
#define N 100005
const i64 mod = 100003;

i64 n, k;
bool a[N];
unsigned int inv[N];
i64 f[N];
i64 now;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    for (unsigned int i = 1; i <= n; ++i)
        cin >> a[i];
    inv[1] = 1;
    for (unsigned int i = 2; i <= n; ++i)
        inv[i] = ((mod - mod / i) * inv[mod % i]) % mod;

    for (i64 i = n; i; --i) {  // 从最大开始关
        if (!a[i]) continue;
        ++now;
        for (i64 j = 1, lim = sqrt(i); j <= lim; ++j) {  // 枚举因数
            if (i % j) continue;
            a[j] ^= 1;
            if (i / j != j) a[i / j] ^= 1;
        }
    }

    f[n] = 1;
    for (unsigned int i = n - 1; i > k; --i) {
        f[i] = ((((f[i + 1] + 1) % mod) * (n - i) % mod) * inv[i] + 1) % mod;
    }

    i64 ans = 0;
    for (unsigned int i = k + 1; i <= now; ++i) {
        ans = (ans + f[i]) % mod;
    }

    for (unsigned int i = n - 1; i; --i)
        n = n * i % mod;

    cout << (ans + std::min(k, now)) * n % mod << endl;

    return 0;
}