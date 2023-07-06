#pragma GCC target("avx2,avx512f,sse4.2,bmi1,bmi2.popcnt,lzcnt,mmx")

#include <cstdio>
#include <cstring>

char ch;
template <typename __readType>
void read(__readType &__x) {
    __x = 0;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        __x = (__x<<1) + (__x<<3) + (ch^48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename __readType, typename ...__readArgs>
void read(__readType &__x, __readArgs &...__args) {
    read(__x); read(__args...);
}

template <typename __compareType>
__compareType max(__compareType __a, __compareType __b) {
    return (__a > __b ? __a : __b);
}

#define N 100514 
#define TREE 3
#define ST 2

int f[TREE+1][N][TREE+1][ST];

int n;
int a[N], b[N], c[N];

int main() {
    read(n);
    // memset(f,0x80,sizeof f);
    for (int i = 1; i <= n; ++ i) {
        read(a[i], b[i], c[i]);
    }

    f[1][2][2][1] =  b[2];
    f[1][2][3][1] =  c[2];

    f[2][2][1][0] =  a[2];
    f[2][2][3][1] =  c[2];

    f[3][2][1][0] =  a[2];
    f[3][2][2][0] =  b[2];
    for (int t = 1; t < 4; ++ t) {
        for (int i = 3; i <= n; ++ i) {
            // if (max(f[t][i-1][2][1], f[t][i-1][3][1]) > 0)
                f[t][i][1][0] = max(f[t][i-1][2][1], f[t][i-1][3][1]) + a[i];
            // if (f[t][i-1][3][1] > 0)
                f[t][i][2][0] = f[t][i-1][3][1] + b[i];
            // if (f[t][i-1][1][0] > 0)
                f[t][i][2][1] = f[t][i-1][1][0] + b[i];
            // if (max(f[t][i-1][2][0], f[t][i-1][1][0]) > 0)
                f[t][i][3][1] = max(f[t][i-1][2][0], f[t][i-1][1][0]) + c[i];
        }
    }

    f[1][1][1][0] = a[1] + max(f[1][n][2][1], f[1][n][3][1]);

    f[2][1][2][1] = b[1] + f[2][n][1][0];

    f[2][1][2][0] = b[1] + f[2][n][3][1];

    f[3][1][3][1] = max(f[3][n][2][0], f[3][n][1][0]) + c[1];

    printf("%d",max(max(f[1][1][1][0], f[2][1][2][1]), max(f[2][1][2][0], f[3][1][3][1])));

    return 0;
} 