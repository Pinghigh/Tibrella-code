#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;

#define N 1514000

int fa[N];
int rk[N];
int tmp1, tmp2;
int n, k;
int z, x, y;
int fAKe;

int find(int pos) {
    while (fa[pos] != pos)
        pos = fa[pos];
    return fa[pos];
}

void uni(int aRoot, int bRoot) {
    tmp1 = find(aRoot);
    tmp2 = find(bRoot);

    fa[tmp1] = fa[tmp2];
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;

    for (int i = 1; i <= N; ++i) {
        fa[i] = i;
    }

    while (k--) {
        cin >> z >> x >> y;
        if (x > n || y > n) {
            ++fAKe;
            continue;
        }
        if (z == 1) {
            if (find(x + n) == find(y) || find(y) == find(x + 2 * n)) {
                ++fAKe;
                continue;
            }
            uni(x, y);
            uni(x + n, y + n);
            uni(x + 2 * n, y + 2 * n);
        } else {
            if (x == y || find(x) == find(y) || find(x + 2 * n) == find(y)) {
                ++fAKe;
                // cout << "fuck" << endl;
                continue;
            }
            uni(y,x+n);
            uni(y+2*n, x);
            uni(x+2*n,y+n);
        }
    }
    cout << fAKe;

    return 0;
}