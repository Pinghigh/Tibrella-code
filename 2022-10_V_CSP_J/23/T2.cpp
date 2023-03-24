#include <iostream>

using namespace std;

long long int n,m,p,q,t,last,sum;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("T2.in","r",stdin);
    freopen("T2.out","w",stdout);

    cin >> n >> m >> p >> q >> t;

    while (m/n < p && n != 0) {
        n --;
    }

    last = m%n;

    if (m/n *t >= q) {
        cout << n*q;
    } else {
        if ((m/n+1) *t >= q) {
            cout << last*q + (n-last)*(m/n)*t;
        } else {
            cout << last*(m/n+1)*t + (n-last)*(m/n)*t;
        }
    }

    return 0;
}