#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using std::cin;
using std::cout;
using std::string;

#define endl '\n'
#define log(__num) (int)ceil(__builtin_log10(__num))
#define N 105

int f[N][N];
string s;

template <typename T>
T min(T _a, T _b) {
    return _a < _b ? _a : _b;
}

bool check(int l, int r, int len) {
    while (l < r && r > 0) {
        if (s.substr(r-len+1,len) != s.substr(l,len)) return false;
        r -= len; 
    }
    return true;
}

int m[N];

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> s;
    int n = s.size();
    s = ' '+s;
    memset(f,0x3f,sizeof(f));
    
    for(int i=1;i<=9;i++)m[i]=1;
    for(int i=10;i<=99;i++)m[i]=2;
    m[100]=3;

    for (int i = 0; i <= n; ++ i) {
        f[i][i] = 1;
    }

    for (int len = 2; len <= n; ++ len) {
        for (int l = n-len+1, r = l+len-1; l > 0; -- l, -- r) {
            // 先处理第一种情况即两个折叠串合成

            for (int k = l; k < r; ++ k) {
                f[l][r] = min(f[l][r], f[l][k] + f[k+1][r]);
            }
            
            // 然后是把整个串折叠的情况，枚举折叠断点

            for (int k = l; k < r; ++ k) {
                int f_len = k - l + 1;
                if (len%f_len) continue;
                if (check(l,r,f_len)) f[l][r] = min(f[l][r], f[l][k] + 2 + m[len/f_len]);
            }
        }
    }

    cout << f[1][n] << endl;

    return 0;
}