#include <iostream>
#include <string>

using std::cin;
using std::cout;

using u32 = unsigned int;

int n, m;
int all1 = -1, all0;
int ans;
std::string op;
int t1;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    while (n--) {
        cin >> op >> t1;
        switch (op[0]) {
            case ('A'): all1 &= t1, all0 &= t1; break;
            case ('O'): all1 |= t1, all0 |= t1; break;
            default: all1 ^= t1, all0 ^= t1; break;
        }
    }

    for (int i = 29; ~i; --i) {
        if (all0 & (1 << i))
            ans += (1 << i);
        else if ((all1 & (1 << i)) && (m >= (1 << i)))
            m -= (1 << i), ans += (1 << i);
    }

    cout << ans << '\n';

    return 0;
}