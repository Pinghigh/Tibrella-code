#include <iostream>

using std::cin;
using std::cout;

#define N 105

using i32 = int;
using i64 = long long;

constexpr i64 mod = 1e9 + 7;

i64 f[N][5][5][5];
i32 n;

bool valid(i32 a, i32 b, i32 c, i32 d) {
    return !(((a == 1 && c == 3 && d == 2) || (a == 1 && b == 3 && d == 2) || (b == 1 && ((c == 3 && d == 2) || (c == 2 && d == 3))) || (b == 3 && c == 1 && d == 2)));
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i < 5; ++i)
        for (i32 j = 1; j < 5; ++j)
            for (i32 k = 1; k < 5; ++k)
                if (!((i == 1 && ((j == 2 && k == 3) || (j == 3 && k == 2))) || (i == 3 && j == 1 && k == 2))) f[3][i][j][k] = 1;

    for (i32 i = 3; i < n; ++i) {
        for (i32 j = 1; j < 5; ++j) {
            for (i32 k = 1; k < 5; ++k) {
                for (i32 l = 1; l < 5; ++l) {
                    for (i32 c = 1; c < 5; ++c)
                        if (valid(j, k, l, c)) f[i + 1][k][l][c] = (f[i + 1][k][l][c] + f[i][j][k][l]) % mod;
                }
            }
        }
    }

    i64 ans = 0;

    for (i32 j = 1; j < 5; ++j) {
        for (i32 k = 1; k < 5; ++k) {
            for (i32 l = 1; l < 5; ++l)
                ans = (ans + f[n][j][k][l]) % mod;
        }
    }

    cout << ans;
    return 0;
}