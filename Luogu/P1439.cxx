#include <iostream>
#include <algorithm>

using namespace std;

#define N 100010

int n,num;
int a[N],b[N];
int dp[N], tail;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> num;
        a[num] = i; // 记录每个数出现的位置
                    // 因为输入的是 1~n 的全排列，所以没必要用 map 存
    }
    for (int i = 1; i <= n; i ++) {
        cin >> num;
        b[i]=a[num]; // 实际上是跳步骤
                     // 目的是把 b_i 修改为 a 中 b_i 出现的位置
    }
    
    // LIS
    tail=0;
    dp[++tail]=b[1];
    for (int i = 2; i <= n; i ++) {
        if (dp[tail] < b[i]) {
            dp[++tail] = b[i];
        } else {
            *lower_bound(dp+1,dp+1+tail,b[i]) = b[i];
        }
    }
    cout << tail;

    return 0;
}
