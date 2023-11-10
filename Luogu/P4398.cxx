#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;
using u64 = unsigned long long;

#define N 51

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ 936483723u);

u64 h1[N][N], h2[N][N];
i32 salt1[N][N], salt2[N][N];
i32 a[N][N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    for (i32 i = 1; i <= n; ++ i)
        for (i32 j = 1; j <= n; ++ j)
            cin >> a[i][j];

    for (i32 i = 1; i <= n; ++ i) 
        for (i32 j = 1; j <= n; ++ j)
            salt1[i][j] = rng() >> 16, salt2[i][j] = rng() >> 16;

    // hash
    for (i32 i = 1; i <= n; ++ i)
        for (i32 j = 1; j <= n; ++ j) 
            

    return 0;
}