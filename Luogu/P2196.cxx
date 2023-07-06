#include <cctype>
#include <cstdio>
#include <bitset>
#include <cstring>

using namespace std;

#define MAXN 25
#define INF 1145141919

int read() {
    int f=1,x=0;
    char ch;
    ch = getchar();
    while(!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
        //puts("1!");
    }
    while(isdigit(ch)) {
        x=x*10+ch-'0';
        ch = getchar();
        //puts("5!");
    }
    return x*f;
}

int n, b[MAXN], in[MAXN];
int path[MAXN], res[MAXN], recSum=-INF, len;
bitset <MAXN> p[MAXN], st; 
char c;

bool check(int a) {
    for (int i = a+1; i <= n; i ++) {
        if (p[a][i]&&!st[i]) return 1;
    }
    return 0;
}

void dfs(int idx, int hav, int sum) {
    if (check(idx)) {
        for (int i = idx+1; i <= n; i ++) {
            if (p[idx][i]&&!st[i]) {
                st[i] = 1;
                path[hav+1] = i;
                dfs(i, hav+1, sum+b[i]);
                st[i] = 0;
            }
        } 
    } else { // 边界
        if (recSum < sum) {
            memcpy(res,path,sizeof path);
            recSum = sum;
            len = hav;
        }
    }
}

int main() {
    n=read();
    for (int i = 1; i <= n; i ++) {
        b[i]=read();
        //puts("1!");
    }
    for (int i = 1; i < n; i ++) {
        for (int j = i+1; j <= n; j ++) {
            c = getchar();
            while(!isdigit(c)) c = getchar();
            if (c=='1') {
                p[i][j] = 1;
                in[j] += 1;
            }
        }
    }

    for (int i = 1; i <= n; i ++) {
        st[i]=1;
        path[1]=i;
        dfs(i,1,b[i]);
        st[i]=0;
    }

    for (int i = 1; i <= len; i ++) {
        printf("%d ",res[i]);
    }
    putchar('\n');
    printf("%d", recSum);

    return 0;
}
