#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 100005

i32 a[N], b[N];
int n;
i32 l[N * 10], r[N * 10], cnt;

#define REG1 n + 1
#define REG2 n + 2

bool rev;

void swap(const i32& a, const i32& b) {
    ++cnt;
    l[cnt] = a, r[cnt] = b;
    std::swap(::a[a], ::a[b]);
}

void revert() {
    std::swap(::a[l[cnt]], ::a[r[cnt]]);
    --cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (i32 i = 1; i <= n; ++i) 
        cin >> a[i];
    a[REG1] = n + 1, a[REG2] = n + 2;
    for (i32 i = 1; i <= n; ++i) {
        if (a[i] != i) {
            swap(REG1, i);
            while (a[REG1] != i)
                swap(a[REG1], REG1);
            revert();
            swap(a[REG1], REG2);
            swap(a[REG1], REG1);
            swap(a[REG2], REG2);
        }
    }
    if (a[REG1] != n + 1) swap(REG1, REG2);
    if (cnt) {
        cout << 2 << ' ' << cnt << '\n';
        for (i32 i = 1; i <= cnt; ++i)
            cout << l[i] << ' ' << r[i] << '\n';
    } else
        cout << "0 0";
    return 0;
}