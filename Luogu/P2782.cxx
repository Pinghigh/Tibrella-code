#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

#define endl '\n'
#define N 200005

struct rel {
    int fr, to;

    const bool operator<(const rel& exa) const {
        return this->fr < exa.fr;
    }
} data[N];

using std::lower_bound;
using std::sort;
using std::vector;

int n;
vector<int> lis(N);

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr)->tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> data[i].fr >> data[i].to;
    }

    sort(data + 1, data + n + 1);

    lis.resize(0);
    lis.push_back(data[1].to);
    for (int i = 2; i <= n; ++i) {
        if (data[i].to > *(lis.end() - 1)) {
            lis.push_back(data[i].to);
        } else {
            *lower_bound(lis.begin(), lis.end(), data[i].to) = data[i].to;
        }
    }

    cout << lis.size();

    return 0;
}