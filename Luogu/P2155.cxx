#include <algorithm>
#include <cmath>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

const i64 mod = 1e9 + 7;
const i64 inv25 = 280000002;
const i64 yin = 26;

i32 t, n;
i64 qp[100005][2];
const i64 b_siz = sqrt(1000000000ll >> 1);
void init() {
    qp[0][0] = qp[0][1] = 1;
    for (int i = 1; i <= b_siz; i++)
        qp[i][0] = qp[i - 1][0] * yin % mod;
    for (int i = 1; i <= b_siz; i++)
        qp[i][1] = qp[i - 1][1] * qp[b_siz][0] % mod;
}

i64 pow(const i64& p) {
    i64 res = qp[p / b_siz][1];
    if (p % b_siz)
        return res * qp[p % b_siz][0] % mod;
    else
        return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    init();
    while (t--) {
        cin >> n;
        i32 k = (n + 1) >> 1;
        cout << ((((k << 1) - 1) * pow(k) % mod - 1 - ((pow(k) % mod - 26) << 1) % mod * inv25 % mod) % mod * 26 % mod * inv25 % mod + mod) % mod << '\n';
    }

    return 0;
}