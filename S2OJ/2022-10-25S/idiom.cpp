#include <cstdio>
#include <bitset>

#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define N 200010

using namespace std;

struct id {
    int ca; // 分类
    int next; // 指向下一个（类似链表结构
    int step = 0;
}all[N];

bitset<N> stat;
bitset<N> is;
int n,m,q;

inline int read() {
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

inline int search(int a) {
    if (stat[all[a].ca]) return 1;
    stat[all[a].ca] = 1;
    int tmp = search(all[a].next);
    stat[all[a].ca] = 0;
    return tmp + 1;
}

int main() {
    n=read(); m=read();
    for (int i = 1; i <= n; i ++) all[i].ca=read();
    for (int i = 1; i <= n; i ++) all[i].next = read();
    q=read();
    int now;
    while (q --) {
        now = read();
        if (!is[now]) {
            all[now].step = search(now);
        }
        is[now]=1;
        printf("%d\n",all[now].step);
    }

    return 0;
}