#include <iostream>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >>t;
    while (t--) {
        int n;
        cin >> n;
        for (long long i = 1; i <= n; ++ i) cout << (i<<1)-1 << ' ';
        cout << '\n';
    }

    return 0;
}