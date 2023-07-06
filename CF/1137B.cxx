#include <iostream>
#include <string>

using std::cin;
using std::cout;

using i32 = int;

#define N 500005

i32 nxt[N];
char ch;
i32 n;
std::string s, t;
i32 z1, z2, o1, o2;
i32 zt, ot;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s >> t;

    for (auto& c : s) {
        if (c == '0')
            ++z1;
        else
            ++o1;
    }

    for (auto& c : t) {
        if (c == '0')
            ++z2;
        else
            ++o2;
    }

    for (i32 i = 1, j = 0; i < t.length(); ++i) {
        while (j && t[i] != t[j])
            j = nxt[j];
        if (t[i] == t[j]) ++j;
        nxt[i + 1] = j;
    }

    for (i32 i = t.length() - nxt[t.length()]; i < t.length(); ++i) {
        if (t[i] == '0')
            ++zt;
        else
            ++ot;
    }
    zt = z2 - zt;
    ot = o2 - ot;

    std::string res, prefix = t.substr(nxt[t.length()], t.length() - nxt[t.length()]);
    if (z2 > z1 || o2 > o1) {
        cout << s;
        return 0;
    }

    z1 -= z2;
    o1 -= o2;
    res = t;
    while (zt <= z1 && ot <= o1) {
        z1 -= zt;
        o1 -= ot;
        res += prefix;
    }
    while (o1--) {
        res += '1';
    }
    while (z1--) {
        res += '0';
    }
    cout << res;

    // cout << zt << ' ' << ot << ' ' << prefix;

    return 0;
}