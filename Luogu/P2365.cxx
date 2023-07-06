#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

#define N 300005

unsigned long long t[N], c[N], f[N];
unsigned long long q[N], hh, tt;
unsigned long long sumt[N], sumc[N];
unsigned long long n, s;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(f, 0x3f, sizeof f);

    cin >> n >> s;
    for (unsigned long long int i = 1; i <= n; ++i) {
        cin >> t[i] >> c[i];
        sumt[i] = sumt[i - 1] + t[i];
        sumc[i] = sumc[i - 1] + c[i];
    }

    f[0] = 0;
    hh = 1, tt = 0;
    q[++tt] = 0;
    for (unsigned long long i = 1; i <= n; ++i) {
        while (hh < tt && f[q[hh + 1]] - f[q[hh]] <= (s + sumt[i]) * (sumc[q[hh + 1]] - sumc[q[hh]]))
            ++hh;
        unsigned long long j = q[hh];
        f[i] = f[j] - (s + sumt[i]) * sumc[j] + sumt[i] * sumc[i] + s * sumc[n];
        while (hh < tt && (f[q[tt]] - f[q[tt - 1]]) * (sumc[i] - sumc[q[tt]]) >= (f[i] - f[q[tt]]) * (sumc[q[tt]] - sumc[q[tt - 1]]))
            --tt;
        q[++tt] = i;
    }

    cout << f[n];

    return 0;
}