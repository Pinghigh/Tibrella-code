#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

const i64 mod = 1e9 + 7;

#define N 1000005

i32 n, a[N];
std::vector<i32> b(1);

i64 cf[N];   // 差分数组
i64 icf[N];  // i*cf[i]
i64 pre[N], prepos[N];

inline i32 lowbit(i32 x) {
    return x & -x;
}

void m(i32 pos, i64 val) {
    for (i32 i = pos; i <= n; i += lowbit(i)) {
        icf[i] += val * pos % mod;
        cf[i] += val % mod;
        icf[i] %= mod;
        cf[i] %= mod;
    }
}

i64 q(i32 pos) {
    i64 res = 0;
    for (i32 i = pos; i; i -= lowbit(i)) {
        res += (pos + 1) % mod * cf[i] % mod - icf[i];
        res %= mod;
    }
    return res;
}

void modify(i32 l, i32 r, i64 val) {
    m(l, val), m(r + 1, -val);
}

i64 query(i32 l, i32 r) {
    return (q(r) - q(l - 1)) % mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> a[i];
        b.emplace_back(a[i]);
    }

    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());

    for (i32 i = 1; i <= n; ++i)
        a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();

    for (i32 i = 1; i <= n; ++i) {
        if (prepos[a[i]]) pre[i] = prepos[a[i]];
        prepos[a[i]] = i;  // a[i] 上一个出现的位置
    }

    i64 res = 0, tmp = 0;
    for (i32 i = 1; i <= n; ++i) {
        tmp += i - pre[i] + 2 * (q(i) - q(pre[i]));
        tmp %= mod;
        res += tmp;
        m(pre[i] + 1, 1);
        m(i + 1, -1);
    }

    cout << (res % mod + mod) % mod;

    return 0;
}