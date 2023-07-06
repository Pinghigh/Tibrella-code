#include <cstring>
#include <iostream>


using std::cin;
using std::cout;
using std::min;

using u16 = unsigned short int;
using u64 = unsigned long long int;

#define N 100015
#define M 30
#define ST (1 << 20)

u64 n, m;
u64 s[M][N];  // sum[i][j] 前 j 个人里面有多少个乐队 i 的人
u64 sum[N];   // 懒得用 s[n][j] 了，再开一个
u64 t1;
u64 f[ST + 10];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(f, 0x3f, sizeof f);

    cin >> n >> m;
    for (u64 i = 1; i <= n; ++i) {
        cin >> t1;
        for (u64 j = 1; j <= m; ++j)
            s[j][i] = s[j][i - 1] + (j == t1);  // 统计前缀和
        ++sum[t1];                              // 统计总数
    }

    u64 max_st = (1 << m) - 1;

    f[0] = 0;
    for (u64 st = 0; st <= max_st; ++st) {
        u64 len = 0;
        for (u64 i = 1; i <= m; ++i) {
            if ((1 << (i - 1)) & st) len += sum[i];
        }

        for (u64 i = 1; i <= m; ++i) {
            if ((1 << (i - 1)) & st) f[st] = min(f[st], f[st ^ (1 << (i - 1))] + sum[i] - (s[i][len] - s[i][len - sum[i]]));
        }
    }

    cout << f[max_st] << std::endl;

    return 0;
}