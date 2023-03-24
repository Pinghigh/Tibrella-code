#include <cstdio>
#include <iostream>
#define getchar _getchar_nolock
#define putchar _putchar_nolock

using namespace std;

int read() {
    int x = 0,f=1;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') f = -1;
    } while (ch > '9' || ch < '0');
    do {
        x = x*10 + ch -'0';
        ch = getchar();
    } while (ch <= '9' && ch >= '0');
    return f*x;
}

int x,n,k,p;
long long tmp,res;

void pow(int a) {
    // cout << a << endl;
    if (a == 0) {
        return ;
    }
    tmp *= x;
    tmp %= p; 
    pow(a-1);
}

int main() {
    freopen("calculate.in","r",stdin);
    freopen("calculate.out","w",stdout);

    x=read(); n=read(); k=read(); p=read();

    for (int i = 0; i <= n; i ++) {
        tmp = 1;
        pow(i*k);
        res += tmp;
    }
    printf("%lld", res);
    return 0;
}