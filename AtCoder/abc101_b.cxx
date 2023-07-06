#include <iostream>

using std::cin;
using std::cout;

using i32 = int;

i32 n, yuanshen, genshin;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    yuanshen = n;
    do {
        genshin += n % 10;
        n /= 10;
    } while (n);
    cout << ((yuanshen % genshin) ? "No" : "Yes");

    return 0;
}