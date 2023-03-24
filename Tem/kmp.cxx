#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

#define endl '\n'
#define N 100514
#define M 1000514

int nxt[N];
string a,b;
int n,m;

void get_nxt(string str) {
    for (int i = 2, j = 0; i <= n; ++ i) {
        while (j && str[i] != str[j+1]) {
            j = nxt[j]; // 如果 border 不合法就跳，直到没 border 为止
        }
        if (str[i] == str[j+1]) {
            ++ j; // 实际上上面循环完之后的 j 可能是合法 border 的结尾也有可能是无解（0），同时如果 border 合法，需要 +1（因为跳 border 的时候跳的是之前的 border） 
        }
        nxt[i] = j;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> a >> m >> b;
    a = '0' + a;
    b = '0' + b;
    get_nxt(a);

    for (int i = 1, j = 0; i <= m; ++ i) {
        while (j && b[i] != a[j+1]) {
            j = nxt[j];
        }
        if (b[i] == a[j+1]) {
            ++ j;
        }
        // cout << "j: " << j << " string: " << b.substr(i,j) << endl;
        if (j == n) {
            j = nxt[j];
            cout << i - n << ' ';
        }
    }

    return 0;
}