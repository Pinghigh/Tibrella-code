#include <bitset>
#include <iostream>

using std::cin;
using std::cout;

#define N 505
#define M 50004

using i32 = int;

std::bitset<(N << 1)> graph[N];
i32 mat[N], cnt[N];
i32 n, m, e;
i32 t1, t2;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> e;
    for (i32 i = 1; i <= e; ++i) {
        cin >> t1 >> t2;
        graph[t1][t2 + n] = 1;
    }

    hyl();

    return 0;
}