#include <iostream>

using std::cin;
using std::cout;

int nums[25];
int n,x;

int main() {
    cin >> n;
    for (int i = 0; i < n; i ++) {
        cin >> x;
        nums[x] += 1;
    }

    for (int i = 0; i < 21; i ++) {
        while (nums[i] --) {
            cout << i << ' ';
        }
    }

    return 0;
}
