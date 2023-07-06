#include <iostream>

using std::cin; 
using std::cout;

using i32 = int;
using i64 = long long;

#define N 10005

i64 a, ans;
i32 n;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        cin >> a;
        while (!(a & 1)) ++ans, a>>=1;
    }

    cout << ans;


    return 0;
}