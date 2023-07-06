#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;

i32 n;
constexpr i32 a[] = { 111, 222, 333, 444, 555, 666, 777, 888, 999 };

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    cout << *std::lower_bound(a, a + 9, n);

    return 0;
}