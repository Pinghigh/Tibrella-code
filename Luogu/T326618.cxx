#include <algorithm>
#include <iostream>

using namespace std;

using i64 = long long;

i64 x, y, z;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> x >> z;
    if (z < 1e11) {
        x += 1e11;
        cout << x - z;
    } else {
        cout << min(((x - z % 1000000) % 1000000 + 1000000) % 1000000, ((z % 1000000 - x) % 1000000 + 1000000) % 1000000);
    }

    return 0;
}