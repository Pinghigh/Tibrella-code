#include <iostream>

using namespace std;

char a; int count;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> a;
    while (a!='@') {
        switch(a) {
            case('(') :
                count ++;break;
            case(')') :                 
                if (count) {
                    count --;break;
                } else {
                    cout << "NO" ; return 0;
                }
        }
        cin >> a;
    }
    if (count) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}