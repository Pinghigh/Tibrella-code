#include <iostream>

using std::cin;
using std::cout;

#define N 3000006

int inv[N];

int main() {
    inv[1] = 1;
    int n, p;
    cin >> n >> p;
    for (int i = 2; i <= n; ++ i) inv[i] = inv[p%i] * 1ll * (p-p/i) % p;
    for (int i = 1; i <= n; ++ i) cout << inv[i] << '\n';
    return 0;   
}