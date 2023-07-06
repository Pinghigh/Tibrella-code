#include <iostream>
#include <string>

using namespace std;

#define N 100

string mid, las;

void dfs(int ml, int mr, int ll, int lr) {
    if (ml > mr || ll > lr) {
        return;
    }

    cout << las[lr];
    for (int i = ml; i <= mr; ++i) {
        if (mid[i] == las[lr]) {
            dfs(ml, i - 1, ll, ll + i - ml - 1);
            dfs(i + 1, mr, ll + i - ml, lr - 1);
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> mid >> las;

    dfs(0, mid.size() - 1, 0, las.size() - 1);

    return 0;
}
