#include <iostream>

using std::cin;
using std::cout;

int a, b, c, d;
int t;
const char endl = '\n';

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> a >> b >> c >> d;
        if ((d < b) || (d - b) < (c - a)) {
            cout << "-1" << endl;
        } else if (c < a) {
            cout << ((d - b) << 1) + a - c << endl;
        } else {
            cout << ((d - b) << 1) - c + a << endl;
        }
    }

    return 0;
}