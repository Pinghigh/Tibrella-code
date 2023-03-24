#include <iostream>
#include <stack>

using namespace std;

#define ll long long
#define MAXN 100010

int n,t;
stack<ll> res;
ll pos[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll cow,sp;

    cin >> n >> t;
    for (int i = 1; i <= n; i ++) {
        cin >> cow >> sp;
        pos[i] = cow + sp*t;
    }

    for (int i = 1; i <= n; i ++) {
        while (!res.empty() && res.top() >= pos[i]) {
            res.pop();
        }

        res.push(pos[i]);
    }

    cout << res.size();

    return 0;
}