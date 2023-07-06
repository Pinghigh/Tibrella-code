#include <cstdio>
#include <functional>
#include <algorithm>
#include <cctype>


bool readFlag=1;

int read() {
    char ch; int x=0;
    do {
        ch=getchar();
        if (ch == EOF) break;
    } while(!isdigit(ch));
    do {
        x = x * 10 + ch - '0';
        ch=getchar();
    } while(isdigit(ch));
    if (ch == EOF) readFlag=0;
    return x;
}

using namespace std;

#define N 100100

int b[N];
int f1[N],f2[N];
int it;
int t1,t2;

int main() {
    it = 0; // b
    while (readFlag) {
        b[++ it] = read();
    }
    it ++;
    t1 = t2 = 0; // f
    f1[++t1] = f2[++t2] = b[1];
    for (int i = 2; i < it; i ++) {
        //printf("it:%d tail:%d b[i]:%d f[tail]:%d\n",it,tail,b[i],f[tail]);
        if (f1[t1] >= b[i]) {
            f1[++ t1] = b[i];
        } else {
            *upper_bound(f1+1,f1+1+t1,b[i],greater<int>())=b[i];
        }
        
        if (f2[t2] < b[i]) {
            f2[++ t2] = b[i];
        } else {
            *lower_bound(f2+1,f2+1+t2,b[i])=b[i];
        }

    }
    printf("%d\n%d",t1,t2);

    return 0;
}

