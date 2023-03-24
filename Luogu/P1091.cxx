#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::lower_bound;
using std::vector;

#define endl '\n'
#define N 105

vector<int> ori(N);
vector<int> vec(N);
int n;
vector<int> fir(N);
vector<int> sec(N);

template <class it_type>
void lis(it_type begin, it_type end, it_type data) {
    vec.resize(0);
    vec.push_back(*begin);
    ++begin;
    *data = vec.size();
    while (begin != end) {
        if (*begin > vec.back())
            vec.push_back(*begin);
        else
            *lower_bound(vec.begin(), vec.end(), *begin) = *begin;

        *(++data) = vec.size();
        ++begin;
    }
}

int cnt;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr)->tie(nullptr);

    cin >> n;
    ori.resize(n);
    fir.resize(n);
    sec.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> ori[i];

    lis(ori.begin(), ori.end(), fir.begin());
    lis(ori.rbegin(), ori.rend(), sec.rbegin());

    auto max = [](auto exa1, auto exa2) { return exa1 > exa2 ? exa1 : exa2; };
    int res = 0;
    for (int i = 0; i < n; ++i) {
        // cnt = 0;
        // while (*(ori.begin() + i + cnt) == ori[i] && cnt != n)
        //     ++cnt;
        // auto down = lower_bound(ori.begin() + cnt, ori.end(), ori[i]);
        // if (*down == ori[i]) --down;
        // if (down != ori.end()) {
        //     cout << i << ' ' << down - ori.begin() << endl;
        //     res = max(res, fir[i] + sec[down - ori.begin()]);
        // }
        res = max(fir[i], res);
        for (int j = i + 1; j < n; ++ j) {
            if (ori[i] > ori[j]) res = max(res, fir[i] + sec[j]);
        }
    }

    cout << n - res << endl;

    // for (int i = 0; i < n; ++i)
    //     cout << fir[i] << ' ';
    // cout << endl;

    // for (int i = 0; i < n; ++i)
    //     cout << sec[i] << ' ';
    // cout << endl;

    return 0;
}