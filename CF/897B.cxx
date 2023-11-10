#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 100005
bool ans[N];
void solve() {
    std::string s;
    int n;
    cin >> n >> s;
    int same = 0, diff = 0;
    std::memset(ans, 0, sizeof(bool) * (n+3));
    if (s.size() & 1) {
        auto l = s.begin(), r = --s.end();
        while (l<r) {
            if (*l == *r) ++same;
            else ++diff;
            ++l,--r;
        }
        for (int i = diff; i <= diff + same*2+1; ++ i) ans[i]=true;
    } else {
        auto l = s.begin(), r = --s.end();
        while (l<r) {
            if (*l == *r) ++same;
            else ++diff;
            ++l,--r;
        }
        for (int i = diff; i <= diff + same*2; ++i, ++i) ans[i]=true;
    }
    for (int i = 0; i <= n; ++ i) cout << ans[i];
    cout << '\n';
}

int main() {
    i32 t;
    cin >> t;
    while (t--) solve();

    return 0;
}

