#include <iostream>
#define MAXN 1010

using namespace std;

int n,m;
int v[MAXN],w[MAXN];
int f[MAXN];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        cin >> v[i] >> w[i];
    }

    for (int i = 1; i <= n; i ++) { // 按照物品从头到尾枚举
        for (int j = m; j >= v[i]; j --) { // 按照体积从最大体积到当前（第 i 个）物品枚举
            f[j] = max(
                f[j], // 此时未更新的 f[j] 是上一次（i-1）枚举的数据，即 f[j] 是不选第 i 个物品的 f[j]
                f[j - v[i]] + w[i] 
                );
        }
    }

    cout << f[m] << endl;

    return 0;
}