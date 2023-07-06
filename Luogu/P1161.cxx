#include <iostream>

using namespace std;

int t, n, res;
double a;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a >> t;

        for (int j = 1; j <= t; j++) {
            res ^= (int)(j * a);
        }
    }
    cout << res;

    return 0;
}
