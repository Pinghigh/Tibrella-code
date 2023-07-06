#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

#define N 100005

int64_t n;
int64_t w[N], d[N];
int64_t wprefix[N], dissuffix[N];
int64_t q[N], hh, tt;
int64_t sum;

double_t calc(int32_t j, int32_t k) {
    return (wprefix[j] * dissuffix[j] - wprefix[k] * dissuffix[k]) * 1.0 / (wprefix[j] - wprefix[k]);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int64_t i = 1; i <= n; ++i) {
        cin >> w[i] >> d[i];
        wprefix[i] = wprefix[i - 1] + w[i];
        sum += wprefix[i] * d[i];
    }
    for (int64_t i = n; i; --i) {
        dissuffix[i] = dissuffix[i + 1] + d[i];
    }

    hh = 1, tt = 0;
    q[++tt] = 0;

    int64_t ans = 0x3f3f3f3f3f3f3f3f;

    for (int64_t i = 1; i <= n; ++i) {
        while (tt > hh && calc(q[hh], q[hh + 1]) > dissuffix[i])
            ++hh;
        ans = std::min(sum - dissuffix[q[hh]] * wprefix[q[hh]] - dissuffix[i] * (wprefix[i] - wprefix[q[hh]]), ans);
        while (tt > hh && calc(q[tt - 1], q[tt]) < calc(q[tt], i))
            --tt;
        q[++tt] = i;
    }

    cout << ans;

    return 0;
}
