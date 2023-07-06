#include <iostream>

using std::cin;
using std::cout;

int t, n;

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        cout << (n & 1 ? "Acestar\n" : "Blueqwq\n");
    }
    return 0;
} 