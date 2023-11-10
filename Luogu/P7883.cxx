#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <random>
#include <climits>

using i32 = int;
using f64 = double;

constexpr f64 deg = 7.114514;
f64 cs = cos(deg), sn = sin(deg);

#define N 400005

struct dot {
    f64 x, y;
    f64 fx, fy;

    void rotate() {
        fx = x*cs-y*sn, fy = x*sn+y*cs;
    }
} d[N];

i32 n;


f64 dis(const dot&a, const dot&b) {
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

int main() {
    scanf("%d",&n); 
    for (i32 i = 1; i <= n; ++ i) scanf("%lf %lf",&d[i].x, &d[i].y);

    for (i32 i = 1; i <= n; ++ i) d[i].rotate();

    std::sort(d+1,d+n+1,[](const auto&a, const auto&b){return a.fx*a.fy<b.fx*b.fy;});

    i32 k = std::min(50,n-1);

    f64 ans = 2e30+0.01;
    for (i32 i = 1; i <= n; ++ i) for (i32 j = i+1; j <= i+k && j <= n; ++ j) ans = std::min(ans,dis(d[i],d[j]));

    printf("%.0lf", ans);

    return 0;
}