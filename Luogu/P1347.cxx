#include <iostream>
#include <queue>
#include <string>
#include <array>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::string;
using std::array;

#define N 30
#define M 614

int n, m;
char u, v;
int ic, oc;
array<int,N> bind;
array<int,N> ind;
int oud[N];
int cnt;
int g[N][N];
string res = "";
bool st[N];
int idx;
int root;
queue<int> nod;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    if (m < n - 1) {
        cout << "Sorted sequence cannot be determined." << endl;
        return 0;
    }

    for (int i = 1; i <= m; ++i) {
        res = "";
        cin >> u >> v >> v;
        if (!st[u-'A'+1]) ++cnt;
        if (!st[v-'A'+1]) ++cnt;
        st[u-'A'+1] = st[v-'A'+1] = 1;
        // if (oud[u - 'A' + 1] == 0) oc++;
        ++oud[u - 'A' + 1];
        // if (ind[v - 'A' + 1] == 0) ic++;
        ++bind[v - 'A' + 1];
        g[u - 'A' + 1][v - 'A' + 1] = 1;
        ind=bind;
        for (int j = 1; j <= n; ++j) {
            if (ind[j] == 0) {
                nod.push(j);
                // cout << (char)(j+'A'-1);
            }
        }
        nod.push(root);
        while (!nod.empty()) {
            // if (nod.size()>1) break;
            idx = nod.front();
            nod.pop();
            for (int j = 1; j <= n; ++j) {
                if (j == idx) {
                    continue;
                }
                if (g[idx][j]) {
                    --ind[j];
                    if (ind[j] == 0) {
                        nod.push(j);
                    }
                }
            }
            res += (char)('A' - 1 + idx);
            // cout << 1 << endl;
        }
        // cout << res << endl;
        // if (nod.size()>1) continue;
        if (res.size() != cnt) {
            cout << "Inconsistency found after " << i << " relations." << endl;
            return 0;
        } else if (res.size() == n) {
            cout << "Sorted sequence determined after " << i << " relations: " << res << '.' << endl;
            return 0;
        }
        
    }
    cout << "Sorted sequence cannot be determined." << endl;

    return 0;
}