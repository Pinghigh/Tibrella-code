#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 61

template <typename T>
bool chkmax(T& a, const T& b) {
    if (a < b) return a = b, true;
    return false;
}

i64 f[N][N], rt[N][N];
i64 k[N];


i64 dp(const i32& l, const i32& r) {
    if (r < l) return 1;
    else if (l == r) return k[l];
    else if (f[l][r]) return f[l][r];
    else 
        for (i32 rot = l; rot <= r; ++ rot) 
            if (chkmax(f[l][r], dp(l, rot - 1) * 1ll * dp(rot + 1, r) + k[rot])) 
                rt[l][r] = rot;
    return f[l][r];
}

void dfs(const i32& l, const i32& r) {
    if (l > r) return;
    else if (l == r) cout << l << ' ';
    else {
        const i32& rot = rt[l][r];
        cout << rot << ' ';
        dfs(l, rot-1);
        dfs(rot+1, r);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    for (i32 i = 1; i <= n; ++ i) cin >> k[i];
    i64 ans = dp(1, n);
    cout << ans << '\n';
    dfs(1, n);

    return 0;
}