#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

using i32 = int;
using i64 = long long;

#define N 20000007

i32 z[N], p[N];
string a, b;

i64 ans;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> a >> b;

    for (i32 i = 1, l = 0, r = 0; i < b.size(); ++i) {
        if (i <= r && z[i - l] < r - i + 1)
            z[i] = z[i - l];
        else {
            z[i] = std::max(r - i + 1, 0);
            while (i + z[i] < b.size() && b[i + z[i]] == b[z[i]])
                ++z[i];
        }

        // 更新 l,r
        if (r < z[i] + i - 1) r = z[i] + i - 1, l = i;
    }

    z[0] = b.size();
    for (i32 i = 0; i < b.size(); ++i)
        ans ^= (i + 1ll) * (z[i] + 1);
    cout << ans << '\n';

    for (i32 i = 0, l = -1, r = -1; i < a.size(); ++i) {
        if (i <= r && z[i - l] < r - i + 1)
            p[i] = z[i - l];
        else {
            p[i] = std::max(r - i + 1, 0);
            while (i + p[i] < a.size() && p[i] <= b.size() && a[i + p[i]] == b[p[i]])
                ++p[i];
        }

        // 更新 l,r
        if (r < p[i] + i - 1) r = p[i] + i - 1, l = i;
    }

    ans = 0;
    for (i32 i = 0; i < a.size(); ++i)
        ans ^= (i + 1ll) * (p[i] + 1);
    cout << ans;

    return 0;
}