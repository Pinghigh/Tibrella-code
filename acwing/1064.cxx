#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

#define endl '\n'
#define N 15
#define ST 1514
#define K 150
#define count(x) __builtin_popcount(x)

long long int f[N][K][ST];
long long int n, k;
long long int tmpa, tmpb;
vector<long long int> state;
long long int id[ST], cnt[ST];
vector<long long int> head[ST];  // head[i] 表示能转移到状态 i 的所有状态

bool check(long long int st) {
    return !((st >> 1) & st || (st << 1) & st);
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;

    for (int i = 0; i < (1 << n); ++i) {
        if (check(i)) {
            state.push_back(i);
            id[i] = state.size() - 1;  // 存储状态的下标
            cnt[i] = count(i);         // 存储状态数中有几个 1
        }
    }

    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state.size(); ++j) {
            tmpa = state[i];
            tmpb = state[j];
            if (!(tmpa & tmpb) && check(tmpa | tmpb)) {
                head[i].push_back(j);
                // head[tmpb].push_back(tmpa);
            }
        }
    }

    f[0][0][0] = 1;  // 什么都不放也是一种方案
    for (int i = 1; i <= n + 1; ++i) {
        for (int j = 0; j <= k; ++j) {
            for (long long int a = 0; a < state.size(); ++a) {
                if (j >= cnt[state[a]]) {
                    for (auto b : head[a]) {
                        f[i][j][a] += f[i - 1][j - cnt[state[a]]][b];
                    }
                }
            }
        }
    }
    cout << f[n + 1][k][0] << endl;

    return 0;
}
