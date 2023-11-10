#include <fstream>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;
using u32 = int;
using u64 = long long;

#define N 3000001

u32 n, t;
i32 a[N];

u32 qmx[N], qmn[N];
u32 xl, xr, nl, nr;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t >> n;
    for (u32 i = 1; i <= n; ++i)
        cin >> a[i];

    u32 ans = 1;

    xl = xr = nl = nr = 1;
    qmx[1] = qmn[1] = 1;
    u32 pre = 1;

    for (u32 i = 2; i <= n; ++i) {
        while (xl <= xr && a[qmx[xr]] < a[i])
            --xr;
        while (nl <= nr && a[qmn[nr]] > a[i])
            --nr;
        qmx[++xr] = qmn[++nr] = i;
        while (a[qmx[xl]] - a[qmn[nl]] > t) {
            if (qmx[xl] < qmn[nl])
                pre = qmx[xl++] + 1;
            else
                pre = qmn[nl++] + 1;
        }
        ans = std::max(ans, i - pre + 1);
    }

    cout << ans;

    return 0;
}