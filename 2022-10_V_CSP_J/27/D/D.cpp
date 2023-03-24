#include <cstdio>
#include <queue>
#include <cctype>

#define int unsigned
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#define N 500000

using namespace std;

int rd() {
    int k = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();

    while (isdigit(c)) {
        k = (k << 1) + (k << 3) + (c ^ 48);
        c = getchar();
    }
    return k;
}
void wr(int x) {
    if (x > 9)wr(x / 10);
    putchar(x % 10 + '0');
}

unsigned n,m,l,r,p,q,tmp;
unsigned nums[N];
queue<unsigned> xb;

signed main() {
    freopen("D.in","r",stdin);
    freopen("D.out","w",stdout);

    n=rd();m=rd();
    while (m--) {
        l=rd();r=rd();p=rd();q=rd();
        for (int j = l; j <= r; j ++) {
            tmp=j^p;
            // printf("%u",tmp);
            if (tmp < n && tmp >= 0) {
                xb.push(tmp);
            }
        }

        while (!xb.empty()) {
            nums[xb.front()] = nums[xb.front()] ^ q;
            xb.pop();
        }
    }

    for (int i = 0; i < n; i ++) {
        wr(nums[i]);
        putchar(' ');
    }

    return 0;
}