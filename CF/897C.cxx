#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int y;

        int n;
        cin >> n;
        int x, lasx = -1, mex = -1;
        for (int i = 1; i <= n; ++i) {
            cin >> x;
            if (x - lasx > 1 && mex == -1) mex = lasx + 1;
            lasx = x;
        }
        if (mex == -1) mex = x + 1;
        cout << mex << endl;
        cin >> y;
        while (y >= 0) {
            cout << y << endl;
            cin >> y;
        }
        if (y == -2) break;
    }

    return 0;
}