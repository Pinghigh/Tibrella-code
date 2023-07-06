#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

int n;
string s;
int cnta, cntt;
int mx;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> s;

    for (auto& c : s) {
        switch (c) {
            case ('T'): ++cntt; break;
            default: ++cnta; break;
        }
    }
    if (cnta < cntt) {
        cout << "T\n";
    } else if (cnta > cntt) {
        cout << "A\n";
    } else {
        mx = cnta;
        cnta = cntt = 0;
        for (auto& c : s) {
            switch (c) {
                case ('T'): ++cntt; break;
                default: ++cnta; break;
            }
            if (cntt == mx) {
                cout << "T\n";
                break;
            } else if (cnta == mx) {
                cout << "A\n";
                break;
            }
        }
    }

    return 0;
}