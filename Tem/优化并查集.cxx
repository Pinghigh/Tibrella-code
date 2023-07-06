// P3367 
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define N 11514

int fa[N];
int rk[N];
int m,n;
int z,x,y;
int tmp1, tmp2;

int max(int a, int b) {
    return (a>b?a:b);
}

int find(int a) {
    if (fa[a] != a) fa[a] = find(fa[a]);
    return fa[a];
}

void uni(int a, int b) {
    tmp1 = find(a);
    tmp2 = find(b);

    if (rk[tmp1] >= rk[tmp2]) {
        fa[tmp2] = tmp1;
        rk[tmp1] = max(rk[tmp1], rk[tmp2] + 1);
    } else {
        fa[tmp1] = tmp2;
        rk[tmp2] = max(rk[tmp2],rk[tmp1]+1);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; ++ i) {
        fa[i] = i;
        rk[i] = 1;
    }

    while (m --) {
        cin >> z >> x >> y;

        if (z == 1) {
            uni(x,y);
        } else {
            cout << ((find(x) == find(y))?'Y':'N') << endl;
        }
    }

    return 0;
}