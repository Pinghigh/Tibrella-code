#include <iostream>
#include <string>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 6003

i32 a[N], b[N], d[N], p[N];
std::string s, f[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n >> s;  
    for (i32 i = 0, j = 0, k = 0; i < n; ++ i) if (s[i] == 'a') a[d[i]=++j]=i;
    else b[d[i]=++k] = i;

    return 0;
}