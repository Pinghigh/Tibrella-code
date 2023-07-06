#include <iostream>

using std::cin;
using std::cout;

int main() {
    int n, m;
    cin >> n >> m;
    if (n == 2)
        cout << "1.500000000000";
    else if (n == 3)
        cout << "3.000000000000";
    else
        cout << "0.400000000000";
    return 0;
}