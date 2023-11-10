#include <iostream>
#include <string>

using i32 = int;
using i64 = long long;

constexpr i64 mod = 998244353;

i64 inv(i64 x) {
    i32 p = mod - 2;
    i64 res = 1;
    while (p) {
        if (p & 1) res = res * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return res;
}

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    i64 tmp = 1, *ans = nullptr;
    i64 zero = 0;
    for (i32 i = 2; i <= n - 1; ++i)
        if (s[i - 1] == '?') tmp = tmp * (i - 1) % mod;
    ans = s[0] == '?' ? &zero : &tmp;
    cout << *ans << '\n';
    while (m--) {
        i32 x;
        char c;
        cin >> x >> c;
        if (c == '?' ^ s[x - 1] == '?') {
            s[x - 1] = c;
            if (c == '?') {
                if (x - 1 == 0)
                    ans = &zero;
                else
                    tmp = tmp * (x - 1) % mod;
            } else {
                if (x - 1 == 0)
                    ans = &tmp;
                else
                    tmp = tmp * inv(x - 1) % mod;
            }
        }
        cout << *ans << '\n';
    }

    return 0;
}
