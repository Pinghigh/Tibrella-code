#include <iostream>
#include <map>
#include <string>

using std::cin;
using std::cout;
using std::map;
using std::string;

using i32 = int;

#define N 15

i32 n;
map<string, i32> mp;
string s, str[N];
i32 cnt, ori;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i)
        cin >> str[i];
    for (i32 i = 1; i <= n; ++i) {
        cin >> s;
        cin >> ori >> cnt;
        if (!cnt) continue;
        if (ori % cnt) mp[s] += ori % cnt;
        mp[s] -= ori;
        for (i32 j = 1; j <= cnt; ++j) {
            cin >> s;
            mp[s] += ori / cnt;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << str[i] << ' ' << mp[str[i]] << '\n';
    }

    return 0;
}