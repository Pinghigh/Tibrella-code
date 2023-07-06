#include <iostream>

using std::cin;
using std::cout;

using i32 = int;

#define N 100005

i32 jcnt[N], ocnt[N];

i32 n;
i32 a;
i32 jf, js, of, os;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a;
        if (i & 1) {
            ++jcnt[a];
            if (jcnt[a] > jcnt[jf])
                js = jf, jf = a;
            else if (jcnt[a] > jcnt[js] && a != jf)
                js = a;
        } else {
            ++ocnt[a];
            if (ocnt[a] > ocnt[of])
                os = of, of = a;
            else if (ocnt[a] > ocnt[os] && a != of)
                os = a;
        }
    }

    // cout << jf << ' ' << js << ' ' << of << ' ' << os << '\n';

    if (jf != of) {
        cout << n - jcnt[jf] - ocnt[of];
    } else {
        cout << n - std::max(jcnt[jf] + ocnt[os], jcnt[js] + ocnt[of]);
    }

    return 0;
}