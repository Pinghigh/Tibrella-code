#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s = "1";
    int n;

    cin >> n;

    if (n < 5 || (n-5)%4 != 0) {
        cout << -1 << endl; return 0;
    } else {
        while (s.size() != n) {
            s += "0011";
        }
    }
    cout << s << endl;

    return 0;
}