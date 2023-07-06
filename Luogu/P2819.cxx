#include <bitset>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>


#define getchar() getchar_unlocked()
#define putchar() putchar_unlocked()
#define int short int

int read() {
    int x = 0;;
    char ch;
    do {
        ch = getchar();
    } while (!isdigit(ch));
    do {
        x = x*10 + ch - '0';
        ch = getchar();
    } while (isdigit(ch));
    // printf("[input] %d\n",x);
    return x;
    
}

using namespace std;

#define N 10010

bitset<N> gra[N];
int path[N];
int u, v;
int n, k, m;
int res;

bool check(int nod) {
    for (int i = 1; i < nod; ++i) {
        if (path[i] == path[nod] && gra[nod][i]) return false;
    }
    return true;
}

void dfs(int nod) {
    if (nod > n) {
        ++ res;
        return;
    }
    for (int i = 1; i <= m; ++i) {
        path[nod] = i;
        if (check(nod)) {
            dfs(nod + 1);
        }
    }
}

signed main() {
    n = read(); k = read(); m = read();
    while (k--) {
        u = read(), v = read();
        gra[u][v] = gra[v][u] = 1;
    }

    dfs(1);

    printf("%d",res);

    return 0;
}