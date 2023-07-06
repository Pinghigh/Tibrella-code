#include <cstring>
#include <iostream>
#include <unordered_set>

using i32 = int;
using i64 = long long;
using std::cin;
using std::cout;

#define N 100005

i32 t1, n, t;
i64 a[N];
std::unordered_set<i64> num;

i64 calc(i32 st) {
    i64 res = 0;
    for (i32 i = 1; i <= n; ++i) {
        if (st & (1 << (i - 1))) res += a[i];
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> n;
        for (i32 i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        if (n > 19)
            cout << "Yes\n";
        else {
            for (i32 i = 0; i <= (1 << n) - 1; ++i) {
                i64 tmp = calc(i);
                if (num.find(tmp) != num.end()) {
                    cout << "Yes\n";
                    goto end;
                } else
                    num.emplace(tmp);
            }
            cout << "No\n";
        }
    end:
        num.clear();
    }
    return 0;
}
