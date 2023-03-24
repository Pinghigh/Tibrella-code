#include <iostream>
#include <algorithm>
#define MAXN 110

using std::cin;
using std::cout;
using std::max;

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int snow[MAXN][MAXN],s[MAXN][MAXN];
int m,n,res;

int dfs(int x, int y) {
    if (s[x][y]) return s[x][y];
    s[x][y] = 1;
    for (int i = 0; i < 4; i ++) {
        int fx=x+dx[i], fy=y+dy[i];
        if (snow[fx][fy] > snow[x][y] && fy > 0 && fx > 0 && fx <= m && fy <= n) {
            dfs(fx,fy);
            s[x][y] = max(s[x][y],s[fx][fy]+1);
        }
    }
    return s[x][y];
    
}

int main() {
    cin >> m >> n;
    for (int i = 1; i <= m; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> snow[i][j];
        }
    }
    
    for (int i = 1; i <= m; i ++) {
        for (int j = 1; j <= n; j ++) {
            res = max(dfs(i,j),res);
        }
    }

    cout << res;

    return 0;
}
