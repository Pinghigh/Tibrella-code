#include <iostream>
#include <string>

int fu,zh,n,tmp;
int t;

using namespace std;
string x="-1 ", y="1 ";
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n;
    while (n --) {
        cin >> tmp;
        if (tmp < 0) {
            fu += 1;
        } else {
            zh += 1;
        }
    }
    string big="";
    if (fu >= zh) {
        
        cout << y;
        zh --;
        
        t = fu/zh;
        for (int i = 0; i < t; i ++) {
            big += x;
        }
        big += y;
        int mo = fu%zh;

        while(zh --) {
            fu -= t;
            if (mo > 0) {
                mo --;
                cout << x;
            }
            cout << big;
        }
        

    } else {
        t = fu/zh;
        int var = t+1;
        for (int i = 0; i < t; i ++) {
            big += y;
        }
        big += x;
        int yu = zh%fu;
        while(yu --) {
            cout << "-1 " << big;
            zh -= var; fu --;
        }
        while(fu --) {
            cout << big;
            zh -= t; fu --;
        }
    }
    
    
    return 0;
}
