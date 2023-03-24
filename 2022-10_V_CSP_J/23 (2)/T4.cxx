#include <cstdio>

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

// k n m AKA d n l
int find[10][10][10] {
    {{},{0,1}},
    {{},{},{0,0,1},{0,0,0,1}},
    {{},{},{},{},{0,1},{0,0,1},{0,0,0,2},{0,0,0,0,1}}
};
int n,m,t,sum;

int main() {
    n=read(), m=read(), t=read();

    for (int i = 0; i <= t; i ++) {
        for (int j = 0; j <= m; j ++) {
            for (int p = 0; p <= n; p ++) {
                sum += find[i][j][p];
				// printf("%d,",find[i][j][p]);
            }
			// putchar(' ');
        }
		// putchar('\n');
    }
	printf("%d",sum);
    return 0;
}