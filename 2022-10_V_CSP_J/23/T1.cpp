#include <cstdio>
#include <map>
#include <set>

using namespace std;

map<int,int> dict;
set<int> fi;
int up[114514],n,j=1;

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
} // 快速读取

int main() {
    freopen("T1.in","r",stdin);
    freopen("T1.out","w",stdout);
    n=read();
    for(int i = 0; i < n; i ++) {
        up[i] = read();
        fi.insert(up[i]);
    }

    for(int i = 0; i < n; i ++) {
        if (dict.count(up[i])) {
            printf("%d ",dict[up[i]]);
            continue;            
        }

        while (fi.count(j)) {
            j ++;
        }

        fi.insert(j);
        printf("%d ",j);
        dict[up[i]] = j;
    }

    return 0;
}