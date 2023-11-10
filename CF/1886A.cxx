#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n % 3 == 1) {
            if (n < 7)
                goto failed;
            else {
                cout << "YES\n1 2 " << n - 3 << '\n';
            }
        } else if (n % 3 == 2) {
            if (n < 8)
                goto failed;
            else {
                cout << "YES\n1 2 " << n - 3 << '\n';
            }
        } else {
            if (n < 12) goto failed;
            cout << "YES\n1 4 " << n - 5 << '\n';
        }
        continue;

    failed:
        cout << "NO\n";
    }

    return 0;
}