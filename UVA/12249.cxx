#include <iostream>
#include <algorithm>

using i32 = int;
using i64 = long long;

using std::cin;
using std::cout;

#define N 100001

i32 b[N], a[N];

int main() {
    i32 n, m;
    cin >> n >> m;
    for (i32 i = 1; i <= n; ++ i) cin >> a[i];
    for (i32 i = 1; i <= m; ++ i) cin >> b[i];
        
    std::sort(a+1,a+n+1,std::greater<i32>()), std::sort(b+1,b+m+1,std::greater<i32>());
    i64 ans = 0;
    i32 i;
    for (i = 1; i <= n && a[i] >= 0; ++ i) ans += a[i] * 1ll * b[i];
    for (i32 j = n, p = m; j >= i; --j, --p) ans += a[j] * 1ll * b[p]; 
    cout << ans;
    
    return 0;
}