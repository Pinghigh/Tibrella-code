#include <iostream>

using namespace std;

#define MAXN 1010
#define MAXX 1000010

struct enemy {
    int l,w,u;
} es[MAXN];

int n, x;
long long int f[MAXX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> x;
    for (int i = 1; i <= n; i ++) {
        cin >> es[i].l >> es[i].w >> es[i].u;
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = x; j >= es[i].u; j --) {
            //f[j] += es[i].l;
            f[j] = max(f[j]+es[i].l ,f[j-es[i].u] + es[i].w);
        } // 01背包里面没有“不选的价值”所以不用考虑小于“当前物品所占空间”的部分，但是本题有，所以剩下的部分需要再处理一遍。
        for (int j = 0; j < es[i].u; j ++) {
            f[j] += es[i].l;
        }
    }

    cout << 5*f[x] << endl;

    //for (int i = 0; i <= x; i ++) cout << f[i] << ' ';

    return 0;
}
