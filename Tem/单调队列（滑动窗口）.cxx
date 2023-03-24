#include <cstdio>
#define MAXN 3000010

using namespace std;

int que[MAXN], nums[MAXN], mi[MAXN], ma[MAXN];
int head,tail=-1,tma,tmi;

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
    int n,k;
    n = read(); k = read();
    for (int i = 0; i < n; i ++) {
        nums[i] = read();
    }

    for (int i = 0; i < n; i ++) {
        if (head <= tail && que[head] < i - k + 1) head ++;
        while (head <= tail && nums[que[tail]] >= nums[i]) {
            tail --;
        }
        que[++ tail] = i;
        if (i+1>=k) {
            printf("%d ",nums[que[head]]);
        }
    }





    // 下面是重复
    putchar('\n');

    head = 0; tail = -1;
    for (int i = 0; i < n; i ++) {
        if (head <= tail && que[head] < i - k + 1) head ++;
        while (head <= tail && nums[que[tail]] <= nums[i]) {
            tail --;
        }
        que[++ tail] = i;
        if (i+1>=k) {
            printf("%d ",nums[que[head]]);
        }
    }


    return 0;
}