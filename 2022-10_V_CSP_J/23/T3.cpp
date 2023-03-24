// TODO: 降低时间复杂度，另：T6/7和T8/9好像WA了 

#include <iostream>
#define N 520514 // koishi

using namespace std;

long long int n,nums[N];
long long int sum;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("T3.in","r",stdin);
    freopen("T3.out","w",stdout);   

    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> nums[i];
    }
    bool fuEr,er,flag;
    for (int i = 1; i <= n; i ++) {
        flag = 0;
        fuEr = 0;er = 0;
        if (nums[i] == -2) fuEr=1;
        else if (nums[i] == 2) er=1;

        for (int j = i; j <= n; j ++) {
            if (nums[i] != nums[j]) flag = 1;
            if (nums[j] == -2) fuEr=1;
            else if (nums[j] == 2) er=1;
            if (fuEr && er) {
                sum += (n - j + 1);
                // cout << i << ' ' << j << endl;
                break;
            } else if (!fuEr && !er) {
                sum ++;
                // cout << i << ' ' << j << endl;
            } else if (flag == 0) {
                sum ++;
                // cout << i << ' ' << j << endl;
            }
        }
    }
    cout << sum << endl;

    return 0;
}