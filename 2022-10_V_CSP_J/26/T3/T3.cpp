#include <iostream>
#include <string>

using namespace std;

int T,n;
string str,cow;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("T3.in","r",stdin);
    freopen("T3.out","w",stdout);

    cin >> T ;
    while (T--) {
        cin >> n >> str >> cow;
        if (n == 1) {
            for (int i = 0, fin=cow.size()-str.size(); i <= fin;) {
                if (cow.substr(i,str.size()) == str) {
                    cow[i] = '*';
                    i += str.size();
                } else {
                    i ++;
                }
            }
            cout << cow << endl;
        } else {
            for (int i = 0; i < cow.size(); i ++) {
                cout << '*';
            }
            cout << endl;;
        }
    }

    return 0;
}