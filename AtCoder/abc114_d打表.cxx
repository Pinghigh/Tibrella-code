#include <iostream>

using std::cin;
using std::cout;

#define N 105

using i32 = int;

i32 n, cnt[N];

void resolute(i32 x) {
    for (int i = 2; x > 1; ++i) {
        while (!(x % i)) {
            ++cnt[i];
            x /= i;
        }
    }
}

i32 count(i32 x) {
    i32 res = 0;
    for (int i = 1; i <= 97; ++i)
        res += (cnt[i] >= x);
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 1; i <= 100; ++i) {
        resolute(i);
        cout << '\"' <<  (count(74) + count(24) * (count(2) - 1) + count(14) * (count(4) - 1) + ((count(4) * (count(4) - 1) * (count(2) - 2)) >> 1)) << "\", ";
    }

    return 0;
}