#include <iostream>
#include <bitset>
#include <string>

using namespace std;

#define N 1000010

string zo;
int n,m;
int a[N];
char ch;
int res;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    if (n == m) {
        for (int i = 0; i < m; ++ i) {
            cin >> ch;
            if (ch == '1') {
                cout << m-i;
                return 0;
            }
        }
    } else {
        cin >> zo;
        bitset<N> st (zo);
        for (int i = 0; i < n; ++ i) {
            cin >> a[i];
            if (st[a[i]]) {
                ++ res;
                st << 1;
            }
        }
    }
    cout << res;

    return 0;
}