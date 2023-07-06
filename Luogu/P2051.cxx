#include <cstdio>
#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a)

template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    char ch;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename __inputType, typename... __inputArgs>
void read(__inputType& x, __inputArgs&... __args) {
    read(x);
    read(__args...);
}

template <typename __outputType>
void write(__outputType __x, char __ch = ' ') {
    static short int __output_stack[32], __pos;
    __pos = 0;
    do {
        __output_stack[__pos++] = __x % 10;
        __x /= 10;
    } while (__x);
    while (__pos--) {
        putchar(__output_stack[__pos] ^ 48);
    }
    putchar(__ch);
}

template <typename __outputType, typename... __outputArgs>
void write(__outputType __x, char __ch = ' ', __outputArgs... __args) {
    write(__x, __ch);
    write(__args...);
}

const int mod = 9999973;
const int N = 105;

using llint = long long int;

int n, m;
llint f[N][N][N];  // f[i][j][k] 前 i 行，j 列单棋子，k 列双棋子

signed main() {
    read(n, m);
    // std::cin >> n >> m;

    f[0][0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; j + k <= m; ++k) {
                // 不放棋子的方案
                f[i][j][k] += f[i - 1][j][k] % mod;

                // 只放一个棋子的方案
                if (j > 0) {  // 放在没棋子的列
                    f[i][j][k] += f[i - 1][j - 1][k] * (m - (j - 1ll) - k) % mod;
                    f[i][j][k] %= mod;
                }
                if (k > 0) {  // 放在一个棋子的列
                    f[i][j][k] += f[i - 1][j + 1][k - 1]  * (j + 1ll) % mod;
                    f[i][j][k] %= mod;
                }

                // 放两个棋子的方案
                if (k > 0) {  // 一个放在一个棋子的列，一个放在空列
                    f[i][j][k] += f[i - 1][j][k - 1] * (j * (m - j - (k - 1ll)) % mod) % mod;
                    f[i][j][k] %= mod;
                }
                if (k > 1) {  // 都放在一个棋子的列
                    f[i][j][k] += f[i - 1][j + 2][k - 2] * (((j + 1) * (j + 2ll) / 2) % mod) % mod;
                    f[i][j][k] %= mod;
                }
                if (j > 1) {  // 都放在空列
                    f[i][j][k] += f[i - 1][j - 2][k] * (((m - (j - 2ll) - k) * (m - (j - 2ll) - k - 1) / 2) % mod) % mod;
                    f[i][j][k] %= mod;
                }
                f[i][j][k] %= mod;
            }
        }
    }

    llint ans = 0;
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j + i <= m; ++j) {
            ans += f[n][i][j] % mod;
            ans %= mod;
        }
    }

    // std::cout << ans;
    write(ans, '\n');

    return 0;
}