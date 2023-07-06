#include <cstdio>
#include <cctype>
#define getchar getchar_unlocked
#define putchar putchar_unlocked

inline int read() {
    int x = 0,f=1;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') f = -1;
    } while (!isdigit(ch));
    do {
        x = x*10 + ch -'0';
        ch = getchar();
    } while (isdigit(ch));
    return f*x;
}

inline void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + '0');
}

#define N 100010

int n,q;
int it,h,t;
int be[N],val[N];
int num,pos,tmpVal;

void ask(int x) {
    for (int i = 1; i <= n; i ++) {
        switch (be[i]) {
            case (1): x += val[i]; break;
            case (2): x = (x>val[i])?val[i]:x; break;
            case (3): x = (x>val[i])?x:val[i]; break;
        }
    }
    write(x);
}

int main() {
    n = read();
    for (int i = 1, t = n+1; i < t; i ++) {
        be[i]=read();
        val[i]=read();
    }
    q = read();
    while (q--) {
        num=read();
        switch (num) {
            case (4):
                ask(read()); putchar('\n'); break;
            default:
                pos = read(); tmpVal = read();
                be[pos]=num; val[pos]=tmpVal;
                break;
        }
    }
    return 0;
}
