#include <algorithm>
#include <iostream>

using namespace std;

#define N 2000006

struct comp {
    int p, c;
} all[N];

int n, m;
long long ans;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> all[i].p >> all[i].c;
    }
    sort(all + 1, all + 1 + m, [](const comp& a, const comp& b) { return a.p < b.p; });
    for (int i = 1; i <= m; ++i) {
        if (n <= all[i].c) {
            ans += all[i].p * n;
            break;
        }
        ans += all[i].p * all[i].c;
        n -= all[i].c;
    }
    cout << ans << endl;
    return 0;
}