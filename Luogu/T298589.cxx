#include <iostream>
#include <cmath>
#include <climit>

using namespace std;

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)>(b)?(b):(a))
#define N 114514

int m,n;
int mx=INT_MAX,mn=1;
int a;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
        cin >> a;
        mx = min(ceil((1.0*m)/(a*1.0-1)/i),mx);
        mn = max(ceil((1.0*m)/(a*1.0+1)/i),mn);
    }

    if (mx > 1e9) {
        cout << "xiaogougege";
    } else {
        cout << max(0,mx-mn);
    }

    return 0;
}