#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

using f64 = double;
using pos = pair<f64, f64>;

double dis(pos& a, pos& b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

#define x(p) p.first
#define y(p) p.second

pos o = {0,0};

void solve() {
    pos p, a, b;
    cin >> x(p) >> y(p) >> x(a) >> y(a) >> x(b) >> y(b);

    f64 ans = min(max(dis(a,p),dis(a,o)), max(dis(b,p), dis(b,o)));
    f64 rdis = dis(a,b)/2;
    ans = min(
        ans,
        min(
            max(max(dis(a,o),dis(b,p)),rdis),
            max(max(dis(a,p),dis(b,o)),rdis)
        )
    );

    cout << fixed << setprecision(7) << ans << '\n';
    
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}