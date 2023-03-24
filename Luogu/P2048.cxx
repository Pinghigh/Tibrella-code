#include <array>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <queue>
#include <vector>


using std::array;
using std::greater;
using std::make_pair;
using std::pair;
using std::priority_queue;
using std::vector;
using std::less;

/* template start */

#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a) 

// tmp for reading
bool o = 1;
char tmp;
int len;

template <typename T>
void read(T& x) {
    x = 0;
    o = 0;
    do {
        tmp = getchar();
        o|=(tmp=='-');
    } while (tmp<48||tmp>57);
    do {
        x = (x << 3) + (x << 1) + (tmp ^ 48);
        tmp = getchar();
    } while (tmp>47&&tmp<58);
    if (o) {
        x=-x;
    }
}

template <typename T>
void write(T x) {
    if (x < 0) {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 ^ '0');
}
/* template end */

/* data start */

const long long int MAXN = 5e5 + 3;  // Koishi is BEST
const short int MAXLOG = 19;
array<int, MAXN> f[MAXLOG];
array<long long, MAXN> ori, logn;
class section {
public:
    int l, r;
    int start;
    int v;
    int val;

    section(int a, int b, int c, long long d) {
        l = a;
        r = b;
        start = c;
        v = d;
        val=ori[start] - ori[v];
        // printf("r: %d v: %d\n",r,v);
    }
};

priority_queue<section> sec_heap;
int n, k, L, R;
long long input_tmp;
long long ans;
section now(0, 0, 0, 0);

bool operator>(const section& example1, const section& example2) {
    return example1.val > example2.val;
}
bool operator<(const section& example1, const section& example2) {
    return example1.val < example2.val;
}
/* data end */

/* ST List start */
template <typename T>
T min_ori(T &n1, T &n2) {
    // write(n1); putchar('\n');
    return (ori[n1] < ori[n2] ? n1 : n2);
}

template <typename T>
T max(T a, T b) {
    // write(n1); putchar('\n');
    return b & ((a - b) >> 31) | a & (~(a - b) >> 31);
}


void init_log() {
    logn[1] = 0;
    logn[2] = 1;

    for (int i = 3; i <= n; ++i) {
        logn[i] = logn[i >> 1] + 1;
        // write(logn[i]); putchar('\n');
    }
}

void init_list() {
    for (int i = 0; i <= logn[n]; ++i) {
        for (int j = 0; j + (1 << i) - 1 <= n; ++j) {
            if (!i) {
                f[i][j] = j;
            } else {
                f[i][j] = min_ori(f[i - 1][j], f[i - 1][j + (1 << i - 1)]);
            }
        }
    }
}

int query(int l, int r) {
    len = r - l + 1;
    return min_ori(f[logn[len]][l], f[logn[len]][r - (1 << logn[len]) + 1]);
}
/* ST List end */

int main() {
    // read and init
    read(n), read(k), read(L), read(R);
    for (int i = 1; i <= n; ++i) {
        read(input_tmp);
        ori[i] = input_tmp;
        ori[i] += ori[i - 1];
        // write(ori[i]); putchar('\n');
    }
    init_log();
    init_list();

    // main
    for (int i = n; i - L >= 0; --i) {
        sec_heap.push(section(max(0,i - R), i - L, i, query(max(i-R,0) , i - L)));
    }
    while (k--) {
        now = sec_heap.top();
        sec_heap.pop();
        // write(now.val); putchar('\n');
        ans += now.val;
        if (now.l < now.v) {
            sec_heap.push(section(now.l, now.v - 1, now.start, query(now.l, now.v - 1)));
        }
        if (now.v < now.r) {
            sec_heap.push(section(now.v + 1, now.r, now.start, query(now.v + 1, now.r)));
        }
    }
//    printf("%lld", ans);
    write(ans);
    return 0;
}   