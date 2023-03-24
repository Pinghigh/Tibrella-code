#include <algorithm>
#include <climits>
#include <cmath>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

std::random_device seed;
std::mt19937 rd(seed());

using std::cin;
using std::cout;
using std::swap;
using llint = long long int;
using ldouble = long double;

const ldouble DOWN = 0.997;
const int N = 40;
const char endl = '\n';
llint t;
llint n;
std::vector<llint> a, b;
llint ans;
llint t1;
llint sa, sb;

// llint energy() {
//     llint ares = 0, bres = 0;
//     for (auto& i : b)
//         bres += i;
//     for (auto& i : a)
//         ares += i;

//     return abs(ares - bres);
// }

void SA() {
    ldouble temp = 3000;
    llint x, y, e_now;
    llint cha;

    while (temp > 1e-30) {
        x = rd() % a.size();
        y = rd() % b.size();
        sa = sa - a[x] + b[y];
        sb = sb - b[y] + a[x];
        swap(a[x], b[y]);
        e_now = abs(sa - sb);
        if (e_now < ans) {
            ans = e_now;
        } else if (exp((ldouble)(ans - e_now) / temp) * (long long)INT_MAX <= rd()) {
            sa = sa - a[x] + b[y];
            sb = sb - b[y] + a[x];
            swap(a[x], b[y]);
        }
        temp *= DOWN;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> t;

    while (t--) {
        cin >> n;
        if (n == 1) {
            cin >> ans;
            cout << ans << endl;
            continue;
        }
        ans = sa = sb = 0;
        a.resize(0);
        b.resize(0);
        for (int i = 1; i <= n; ++i) {
            if (i % 2) {
                cin >> t1;
                sa += t1;
                a.push_back(t1);
            } else {
                cin >> t1;
                sb += t1;
                b.push_back(t1);
            }
        }

        ans = LLONG_MAX;
        for (int i = 0; i < 15; ++i)
            SA();
        cout << ans << endl;
    }

    return 0;
}