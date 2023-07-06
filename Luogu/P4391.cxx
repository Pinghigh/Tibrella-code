#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

#define endl '\n'
#define L 1000514

string s;
int l;
int nxt[L];

void get_next() {
    for (int i = 2, j = 0; i <= l; ++ i) {
        while (j && s[i] != s[j+1]) {
            j = nxt[j];
        }
        if (s[i] == s[j+1]) {
            ++ j;
        }
        nxt[i] = j;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> l >> s;
    s = '0' + s;
    get_next();
    cout << l - nxt[l] << endl;

    return 0;
}