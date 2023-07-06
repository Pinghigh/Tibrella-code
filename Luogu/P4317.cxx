#include <iostream>

using llint = long long int;
using std::cin;
using std::cout;

#define endl '\n'
#define N 49

const llint mod = 10000007;
llint cnt; 
llint n;
llint f[N+5];
llint ans;

llint binpow(llint x, llint y) {
    static llint res;
    res = 1;
    while (y) {
        if (y&1) res *= x;
        res %= mod;
        x *= x;
        x %= mod;
        y >>= 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    for (int i = N; ~i; -- i) {
        for (int j = N; j; -- j) {
            f[j] += f[j-1];
        }
        if (n >> i & 1) ++f[cnt++];
    }
    ++f[cnt];
    ans = 1;
    for (int i = 1; i <= N; ++ i) ans = (ans * binpow(i,f[i])) % mod;
    cout << ans << endl;

    return 0;
}