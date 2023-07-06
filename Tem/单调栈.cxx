#include <cstdio>
#define MAXN 3000010

using namespace std;

long long stac[MAXN],nums[MAXN],res[MAXN];
long long top, now, r;

long long read() {
    long long x = 0,f=1;
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
} // 快速读取

int main() {
    int n;
    n = read();
    for (int i = 1; i <= n; i ++) {
        scanf("%ld",&nums[i]);
    }

    now = n;
    while (now > 0) {
        while (top != 0 && nums[stac[top]] <= nums[now]) {
            top --;
        }
        r ++; 
        res[r] = stac[top];
        top ++;
        stac[top] = now;
        now --;
    }

    while (r > 0) {
        printf("%lld ",res[r]);
        r --;
    }

    return 0;
}