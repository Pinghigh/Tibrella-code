#include <iostream>
#include <algorithm>
#include <map>
#include <cstdint>
#include <chrono>
#include <unordered_map>

using std::cin;
using std::cout;

using i32 = int;
#define N 40004

i32 a[N], b[N], c[N], ans[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        a[i] = c[i] = i;
        cin >> b[i];
    }
    std::sort(a+1,a+n+1,[](const i32&i, const i32&j)->bool{return b[i]>b[j];});
    for (int i = 1; i <= n; ++ i) 
        ans[a[i]] = c[i];

    for (int i = 1; i <= n; ++ i) 
        cout << ans[i] << ' ';
    
    cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 t;
    cin >> t;
    while (t--) solve();

    return 0;
}