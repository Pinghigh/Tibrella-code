#include <cmath>
#include <iostream>

#define ll long long
ll l,r;
bool is_pow(ll x) {
    return !(x & (x - 1));
}

ll f(ll x) {
    ll dep = ceil(log2(x)); // 需要向上取整
    ll res = 0;
    while (!is_pow(x) && !is_pow(x - 1)) {
        res += (1ll << dep);  // 此处 1 默认为 int，即使 dep 是 long long，右移依然会炸
        x >>= 1;
        --dep;
    }
    res += (x << 1) - 1;
    return res;
}

ll g(ll x) {
    switch (x) {
        case (0): return 0ll;
        case (1): return 1ll;
        case (2): return 2ll;
        case (3): return 3ll;
        default:
            ll res = 7ll;
            for (ll i = 4; i <= x; i <<= 1) {
                res^=f(i)^f(1+i);
            }
            if (!(x&1) && !is_pow(x) && !is_pow(x-1)) { // 如果 x 没有被消掉
                res ^= f(x);
            }
            if (is_pow(x)) {
                res ^= f(x+1);
            }
            return res;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);
    std::cin >> l >> r;
    std::cout << (g(l-1)^g(r)) << '\n';
    return 0;
}