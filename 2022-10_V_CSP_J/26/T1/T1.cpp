#include <cstdio>
#include <cctype>
#include <iostream>
// #include <queue>
// #define getchar _getchar_nolock
// #define putchar _putchar_nolock
#include <string>

using namespace std;

#define N 200010

int numTmp,n,t;
char chTmp;
string res,strTmp;

int main() {
    freopen("T1.in","r",stdin);
    freopen("T1.out","w",stdout);

    scanf("%d",&t);

    while (t--) {
        scanf("%d",&n);

        while (n --) {
            chTmp=getchar();
            if (chTmp == ' ') {n ++; continue;}
            // cout << chTmp << " n:" << numTmp  << ' ' << res << endl;
            if (isdigit(chTmp)) numTmp = numTmp * 10 + (chTmp-'0');
            else {
                if (numTmp) {
                    numTmp --;
                    strTmp = res;
                    while (numTmp --) res += strTmp;
                    numTmp = 0;
                }
                res += chTmp;
            }
        }
        numTmp --;
        strTmp = res;
        while (numTmp --) res += strTmp;
        numTmp = 0;
        cout << res << endl;
        res = "";
    }

    return 0;
}