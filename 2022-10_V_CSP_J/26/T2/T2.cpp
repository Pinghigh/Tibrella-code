#include <cstdio>
#include <cmath>
#include <algorithm>
#define int long long
#define N 100010
#define INF 1145141919

int n;
int q[N],p[N],yet;
int res=INF;
char tmp;

signed main() {
    freopen("T2.in","r",stdin);
    freopen("T2.out","w",stdout);
    scanf("%lld",&n);
    getchar();
    for (int i = 1; i <= n; i ++) {
        tmp = getchar();
        q[i] = q[i-1] + (tmp == '0')*i;
        p[i] = p[i-1] + (tmp == '1')*i;
        // printf("%d\n",tmp-'0');
    }

    for (int i = 1; i <= n; i ++) {
        res = std::min(res,(int)abs(q[i-1]-p[n]+p[i-1]));
        // if (abs(q[i]-p[n]+p[i]) == 1) printf("i:%d q[i]:%d p[i]:%d\n",i,q[i],p[i]);
    }

    printf("%lld",res);

    return 0;
}