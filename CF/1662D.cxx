#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string compress(const string& a) {
    string res;
    for (const char& c : a) {
        if (c != 'B') {
            if (!res.empty() && c == res.back())
                res.pop_back();
            else
                res.push_back(c);
        }
    }
    // cout << res << '\n';
    return res;
}

void solve() {
    string a, b;
    cin >> a >> b;
    int odda = 0, oddb = 0;
    for (const char& c : a)
        if (c == 'B') odda ^= 1;
    for (const char& c : b)
        if (c == 'B') oddb ^= 1;
    if (odda != oddb)
        cout << "NO\n";
    else
        cout << (compress(a) == compress(b) ? "YES\n" : "NO\n");
}

int main() {
    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
