#include <algorithm>
#include <iostream>
#include <string>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long int;

#define N 1000006

const i64 mod = 1e9 + 7;
i32 nxt[N], ans[N];
i32 t;
std::string s;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> s;
        std::fill(nxt, nxt + s.size(), 0);
        std::fill(ans, ans + s.size(), 0);

        ans[1] = 1;
        for (i32 i = 1, j = 0; i < s.size(); ++i) {
            while (j && s[j] != s[i])
                j = nxt[j];
            if (s[j] == s[i]) ++j;
            nxt[i + 1] = j;
            ans[i + 1] = (ans[j] + 1) % mod;
        }

        i64 res = 1;

        for (i32 i = 1, j = 0; i < s.size(); ++i) {
            while (j && s[j] != s[i])
                j = nxt[j];
            if (s[j] == s[i]) ++j;
            while ((j << 1) > (i + 1))
                j = nxt[j];
            res = res * (ans[j] + 1) % mod;
        }

        cout << res << '\n';
    }

    return 0;
}