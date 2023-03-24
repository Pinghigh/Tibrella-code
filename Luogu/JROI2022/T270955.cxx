#include <iostream>

using namespace std;

long long int x,k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> x >> k;
    long long int m = x%3;
    while (k > m) {
        if (x == 1) {
            cout << x + k%2;
            return 0;
        }
        m = x%3;
        k -= (3-m);
        x/=3; x++;
    }
    while (k--) {
        x ++;
        if (x % 3 == 0) {
            x /= 3;
        }
    }

    cout << x;

    return 0;
}