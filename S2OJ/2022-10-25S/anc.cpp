#include <iostream>
#include <string>
#include <bitset>

#define N 500010
#define HOMO a[0]==a[1]&&a[1]==a[4]&&a[2]==a[5]&&a[1]!=a[2]&&a[2]!=a[3]&&a[3]!=a[4]

using namespace std;

string ori;
// string a;
bitset<N> tag;
bitset<5> homo = 10000;
int sum;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> ori;

    for (int i = 0, fin=ori.size() - 6; i <= fin; i ++) {
        string a = ori.substr(i,6);
        sum += HOMO;
        cout << a << " if:" << (HOMO) << endl;
    }
    
    sum %= 114514;
    cout << sum;

    return 0;
}