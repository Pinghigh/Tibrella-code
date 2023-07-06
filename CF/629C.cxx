#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,fma,sse4a,bmi,bmi2,lzcnt,popcnt,abm,arch=cannonlake,tune=cannonlake")

#include <iostream>
#include <string>

using std::cin;
using std::cout;

#define N 2005
#define endl '\n'

using llint = long long int;

constexpr int mod = 1e9 + 7;

auto max = [](auto a, auto b) { return a > b ? a : b; };

std::basic_string<char> str;
int n, m;
llint ans;

llint p[N][N], q[N][N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> str;

    p[0][0] = 1;
    for (int i = 1; i <= 2000; ++i) {
        p[i][0] = p[i - 1][1];
        for (int j = 1; j <= 2000; ++j) {
            p[i][j] = (p[i - 1][j - 1] + p[i - 1][j + 1]) % mod;
        }
    }

    llint lef = 0, rig = 0, mx = 0, fin;
    for (auto& c : str) {
        if (c == '(')
            ++lef;
        else
            ++rig;
        mx = max(rig - lef, mx);
    }
    fin = lef - rig;
    // cout << fin << ' ' << mx << endl;

    llint len = str.size();
    for (int i = 0; i <= n - len; ++i) {
        for (int j = mx; j <= i && j + fin <= n - len; ++j) {
            ans += p[i][j] * p[n - len - i][j + fin] % mod;
            ans %= mod;
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         cout << p[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    cout << ans << endl;

    return 0;
}