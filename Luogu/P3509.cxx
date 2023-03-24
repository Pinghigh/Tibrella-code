#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using llint = long long int;

#define N 1000005
#define endl '\n'

template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

llint nex[N];
llint num[N];
llint f[N];
llint tmp[N];

llint n, k, m;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> num[i];
    }

    llint *hh = num + 1, *tt = num + k + 1;
    nex[1] = k+1;

    for (int i = 2; i <= n; ++i) {
        while (tt < num + n && (*(tt + 1) - num[i] < num[i] - *hh)) {
            hh++, tt++;
        }
        // nex[i] = ((*tt - num[i] <= num[i] - *hh || *tt == num[i]) && *hh != num[i]) ? hh - num : tt - num;
        if (*tt - num[i] > num[i] - *hh)
            nex[i] = tt - num;
        else
            nex[i] = hh - num;
    }

    for (int i = 1; i <= n; ++i) {
        f[i] = i;
    }

    while (m) {
        if (m & 1) {
            for (int i = 1; i <= n; ++i) {
                f[i] = nex[f[i]];
            }
        }

        memcpy(tmp, nex, sizeof nex);

        for (int i = 1; i <= n; ++i) {
            nex[i] = tmp[tmp[i]];
        }
        m >>= 1;
    }

    for (int i = 1; i <= n; ++i) {
        cout << f[i] << ' ';
    }

    return 0;
}