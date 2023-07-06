#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

const char endl = '\n';

int t;
string s;
bool flag;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;
    while (t--) {
        flag = 0;
        cin >> s;
        char tmp = s[0];
        for (int i = 1; i < s.size(); ++i) {
            if (tmp != s[i]) {
                cout << s.size() - 1 << endl;
                flag = true;
                break;
            }
        }
        if (!flag) cout << "-1\n";
    }

    return 0;
}