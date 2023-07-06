#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;

using i32 = int;
using i64 = long long;

constexpr int mat[] = { 0, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

i32 n, m;
i32 t1;
std::vector<i32> hav;
string f[10004];

string max(const string& a, const string& b) {
    if (a.size() != b.size()) return (a.size() > b.size()) ? a : b;
    for (i32 i = 0, lim = b.size(); i < lim; ++i) {
        if (a[i] > b[i])
            return a;
        else if (b[i] > a[i])
            return b;
    }
    return a;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> t1;
        hav.emplace_back(t1);
    }
    std::sort(hav.begin(), hav.end(), [](const i32& a, const i32& b) { return a > b; });

    for (i32 it = 0; it < m; ++it) {
        i32 i = hav[it];
        // cout << i << '\n';
        for (i32 j = mat[i]; j <= n; ++j) {
            if (f[j - mat[i]].size() || j - mat[i] == 0) f[j] = max(f[j], f[j - mat[i]] + (char)(i + '0'));
            // cout << j << ' ' << f[j] << ' ' << '\n';
        }
    }

    cout << f[n];

    return 0;
}