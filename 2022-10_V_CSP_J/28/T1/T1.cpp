#include <iostream>
#include <string>

#define N 30

using namespace std;

string a, b;
int t;
int i, j, n;
bool flag;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;

    while (t--) {
        cin >> a >> b;

        if (a.size() % b.size() != 0) {
            cout << "NO" << endl;
            return 0;
        }

        n = a.size() / b.size();

        i = 0;
        j = 0;
        flag = 0;
        while (n--) {
            while (j < b.size()) {
                cout << a[i];
                if (a[i] == b[j]) {
                    i++;
                    j++;
                } else {
                    flag = 1;
                    cout << "NO" << endl;
                    break;
                }
            }
            if (flag) break;
            j = 0;
        }
        if (flag) continue;

        cout << "YES" << endl;
    }

    return 0;
}