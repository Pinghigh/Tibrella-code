#pragma GCC optimize("O3,unroll-loops,inline")
#pragma GCC target("tune=native")

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

using i32 = int;
using i64 = long long;

#define N 10000 

i64 f[7][N+2];

std::vector<i64> v;  
void solve(i64 l, i64 r, i32 i) {
    i64 pos = l + f[i-1][std::min(l,N*1ll)], k = std::min(l, N*1ll); // 最多 10000 或 l 次

    --pos;
    for (i32 j = 1; j <= k && pos <= r; ++ j) {  
        v.emplace_back(++pos);
        pos += f[i-1][std::min(pos+1,N*1ll)]; 
    }

    k = v.size();
    cout << k << '\n';
    for (const auto &x : v) cout << x << ' ';
    cout << endl;

    i64 res;
    cin >> res;
    v.emplace_back(r+1);
    switch(res) {       
        case(-2):case(-1): exit(0); break;
        case(0): r = v[0]-1; break;
        default: l = v[res-1]+1, r = v[res]-1;
    }
    v.clear();
    return solve(l, r, i-1);
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (i32 i = 1; i <= N; ++ i) f[1][i] = i;
    for (i32 c = 2; c < 6; ++ c) {
        for (i64 l = 1; l <= N; ++ l) {
            i64 r = l + f[c-1][l] - 1; 
            for (i32 p = 1; p <= l; ++ p) {
                if (r >= N) {r += (l-p+1)*(f[c-1][N]+1);break;}
                else r += 1 + f[c-1][r+2];
            }
            f[c][l] += r-l+1;
        }
    }

    solve(1,f[5][1],5);

    return 0;
}