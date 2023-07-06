#include <cmath>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using llint = long long int;

llint a, b, _x, _y;

int ex_gcd(llint u, llint v, llint& x, llint& y) {
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

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> a >> b;
    ex_gcd(a, b, _x, _y);
    cout << (_x % b + b) % b << endl;

    return 0;
}