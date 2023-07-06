#include <algorithm>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

using i32 = int;

#define N 5000005

string ori, s;
i32 p[N], mid, mr;
i32 n;

void init(string& a, string& res) {
    res += "$#";
    for (auto& c : a) {
        res += c;
        res += '#';
    }
    res += '^';
    n = res.size();
}

i32 ans;

void manacher() {
    // p[0] = 1;
    for (int i = 1; i < n; ++i) {
        if (i < mr)
            p[i] = std::min(p[(mid << 1) - i], mr - i);
        else
            p[i] = 1;

        while (s[i - p[i]] == s[i + p[i]])
            ++p[i];
        if (i + p[i] > mr) {
            for (int j = std::max(i + 4, mr) - i + 1; j <= p[i]; ++j) {
                if (!((j - 1) % 4) && s[i - (j / 2)] == '#' && p[i - (j / 2)] * 2 > j) {
                    ans = std::max(j - 1, ans);
                    // if (j - 1 == 16) {
                    //     for (i32 k = i - j + 1; k <= i + j - 1; ++k) {
                    //         cout << s[k];
                    //     }
                    //     cout << '\n';
                    // }
                }
            }
            mid = i;
            mr = i + p[i];
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> ori;
    init(ori, s);
    manacher();

    cout << ans;

    return 0;
}