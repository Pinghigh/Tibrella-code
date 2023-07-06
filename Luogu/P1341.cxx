#include <bitset>
#include <iostream>
#include <vector>

const int N = 70;

using std::bitset;
using std::cin;
using std::cout;
using std::vector;
#define endl '\n'

bitset<N> graph[N];
int n;
char t1, t2;
int start = N;
int deg[N];
int cnt;
vector<int> ans;

template <typename T1, typename T2>
T1 min(T1 a, T2 b) {
    return a < b ? a : b;
}

void dfs(int nod) {
    for (int i = 0; i < N; ++i) {
        if (graph[nod][i]) {
            graph[nod][i] = graph[i][nod] = 0;
            dfs(i);
        }
    }
    ans.push_back(nod);
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ans.reserve(N * 4);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> t1 >> t2;
        t1 -= 'A';
        t2 -= 'A';
        graph[t1][t2] = graph[t2][t1] = 1;
        // cout << (int)t1 << ' ' << (int)t2 << endl;
        ++deg[t1];
        ++deg[t2];
    }
    for (int i = 0; i <= N; ++i) {
        if (deg[i] & 1) {
            if (!start) start = i;
            ++cnt;
        }
    }
    if (cnt && cnt != 2) {
        cout << "No Solution" << endl;
        return 0;
    }
    if (!cnt) {
        for (int i = 0; i <= N; ++ i) {
            if (deg[i]) {
                start = min(start,i);
                // cout << start + 'A';
                break;
            }
        }
    }

    dfs(start);

    for (auto i = ans.end() - 1; i >= ans.begin(); --i) {
        cout << (char)(*i + 'A');
    }

    return 0;
}