#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using llint = long long int;

#define endl '\n'
#define N 100005

llint b[N], p[N];
llint res;
int n;

llint ex_gcd(llint u, llint v, llint& x, llint& y) {
    if (!v) {
        x = 1, y = 0;
        return u;
    }

    llint g = ex_gcd(v, u % v, x, y);
    llint temp = x;
    x = y;
    y = temp - u / v * y;
    return g;
}

llint crt() {
    llint tmp = 1, ans = 0;
    for (int i = 1; i <= n; ++i)
        tmp *= b[i];
    for (int i = 1; i <= n; ++i) {
        llint m = tmp / b[i], x, y;
        ex_gcd(m, b[i], x, y);
        ans = (ans + p[i] * m * x % tmp) % tmp;
    }
    return (ans % tmp + tmp) % tmp;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> b[i] >> p[i];
    }

    cout << crt();

    return 0;
}