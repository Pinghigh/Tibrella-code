#include <iostream>
#include <algorithm>

#define N 1145

using namespace std;

int nums[N][N],n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= i; j ++) {
            cin >> nums[i][j];
        }
    }

    for (int i = n-1; i >= 1; i --) {
        for (int j = 1; j <= i; j ++) {
            nums[i][j] += max(nums[i+1][j],nums[i+1][j+1]);
        }
    }

    cout << nums[1][1];

    return 0;
}