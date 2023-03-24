#include <iostream>

using namespace std;

#define max(a,b) ((a) > (b) ? (a) : (b))
#define N 11451
int n;
int idx, f[N], tim, dep, res;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    while (n --) {
        cin >> idx;
        cin >> tim;
        cin >> dep;
        while(dep) {
            f[idx] = max(f[idx],f[dep]);
            cin >> dep;
        }
        f[idx] += tim;
        res = max(res,f[idx]);
    }

    cout << res << endl;

    return 0;
}
