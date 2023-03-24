#include <iostream>
#include <algorithm>

using namespace std;

#define N 31

int t, n;
int list[N] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215, 33554431, 67108863, 134217727, 268435455, 536870911, 1073741823, 2147483647};

int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int a;
    cin >> t;
    for (int i = 0; i < t; i ++) {
        cin >> n;
        if (n % 2){
            a = upper_bound(list,list+N,n) - list;
            cout << a + (list[a-1]!=n) << endl;
            // cout << a << endl;
        } else
            cout << -1 << endl;
    }

    return 0;
}