#include <cstdio>
#include <algorithm>

#define GCC optimize(10)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define N 114514191

using namespace std;

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

struct player{
    int now=0;
    int l_hp=0;
    int last=0;
    // int all=0;
    int per_hp=0;
    // bool flag=0;
};

int n,m,a,b;
int q;
int sh[N],me[N];

int main() {
	// freopen("tank.in","r",stdin);
    // freopen("tank.out","w",stdout);
	
    player tian;
    player me;

    q = read();

    while (q --) {
        tian.last = read(); me.last = read(); me.l_hp = me.per_hp = read(); tian.l_hp = tian.per_hp = read();

        while (me.last > 0 && tian.last > 0) {
            // if (tian.last >= me.l_hp) {
            //     me.flag=1;
            // }
            me.l_hp= me.l_hp - tian.last;

            // if (me.last >= tian.l_hp) {
            //     tian.flag=1;
            // }
            tian.l_hp= tian.l_hp - me.last;

            while (me.l_hp <= 0) {
                me.last --;
                me.l_hp += me.per_hp;
            }
            while (tian.l_hp <= 0) {
                tian.last --;
                tian.l_hp += tian.per_hp;
            }
            // printf("tlast:%d thp:%d mlast:%d mhp:%d \n",tian.last,tian.l_hp,me.last,me.l_hp);
        }
        
        if (me.last <= 0) {
            printf("%d",tian.last); putchar('\n'); continue;
        }
        putchar('0');
        putchar('\n');
    }

    return 0;
}