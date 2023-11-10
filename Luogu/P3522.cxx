#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

template <typename T>
static void chkmax(T& a, const T& b) {
    if (a < b) a = b;
}


template <typename T>
static void chkmin(T& a, const T& b) {
    if (a > b) a = b;
}

struct segment {
    i32 tim;
    i32 l, r;

    void read() {
        cin >> l >> r;
    } 
};

#define N 1000001

segment q[N];
i32 hh, tt;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    hh = 1, tt = 0;
    i32 n, ans = 1;
    cin >> n;
    for (i32 i = 1; i <= n; ++ i) {
        segment s;
        s.tim = i;
        s.read();
        while (hh <= tt && s.r < q[hh].l) ++hh;
        if (hh <= tt)
            chkmax(ans, i - q[hh].tim + 1);
        while (hh <= tt && s.l > q[tt].l) s.tim = q[tt].tim, s.r = q[tt].r, --tt;
        q[++tt] = s;
    }
    cout << ans << '\n';

    return 0;
}