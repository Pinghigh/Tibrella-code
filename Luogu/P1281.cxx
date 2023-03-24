#include <cstdio>
#include <cctype>
#include <cstring>

// #define getchar() getchar_unlocked()
// #define putchar() putchar_unlocked()
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define N 600
#define int long long 

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

void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + '0');
}

int m,n;
int f[N][N];
int p[N];
int res[N];

void ans(int idx, int last) {
    if (idx == 1) {
        write(1);
        putchar(' ');
        write(last);
        putchar('\n');
        return ;
    }

    int sum = 0,t = 0;
    for (int i = last; i > 0; -- i) {
        sum += p[i];
        if (sum > f[n][m]) {
            t = i + 1;
            break;
        }
        
    }
    ans(--idx,t-1);
    write(t); putchar(' '); write(last); putchar('\n');
}

signed main() {
    memset(f,127,sizeof f);
    m = read(); n = read();
    f[1][0] = 0;
    for (int i = 1; i <= m; i ++) {
        p[i] = read();
        f[1][i] = f[1][i-1] + p[i];
    }
    
    for (int i = 2; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            for (int k = 1; k < j; ++ k) {
                f[i][j] = min(f[i][j],max(f[i-1][k],f[1][j] - f[1][k]));
            }
        }
    } 
    // printf("%d",f[n][m]);
    ans(n,m);

    return 0;
}