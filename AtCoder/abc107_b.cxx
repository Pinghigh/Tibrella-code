#include <iostream>
#include <list>

using std::cin;
using std::cout;

using i32 = int;

#define N 106

i32 h, w;
i32 cnt1[N], cnt2[N];
char mp[N][N];
std::list<i32> l, r;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> h >> w;
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            cin >> mp[i][j];
            if (mp[i][j] == '#') ++cnt1[i], ++cnt2[j];
        }
    }

    for (int i = 1; i <= h; ++i)
        if (cnt1[i]) l.emplace_back(i);

    for (int j = 1; j <= w; ++j)
        if (cnt2[j]) r.emplace_back(j);

    for (auto i : l) {
        for (auto j : r)
            cout << mp[i][j];
        cout << '\n';
    }

    return 0;
}