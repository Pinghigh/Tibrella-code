#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

#define endl '\n'
#define N 100514
#define M 1000514

int nxt[N];
string a, b;
int n, m;

void get_nxt(string& str) {
    for (int i = 1, j = 0; i < str.size(); ++i) {
        while (j && str[i] != str[j]) {
            j = nxt[j];  // 如果 border 不合法就跳，直到没 border 为止
        }
        if (str[i] == str[j]) {
            ++j;  // 实际上上面循环完之后的 j 可能是合法 border
                  // 的结尾也有可能是无解（0），同时如果 border 合法，需要 +1（因为跳
                  // border 的时候跳的是之前的 border）
        }
        nxt[i + 1] = j;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b;
    get_nxt(b);

    for (int i = 0, j = 0; i < a.size(); ++i) {
        while (j && a[i] != b[j])
            j = nxt[j];
        if (a[i] == b[j]) ++j;
        if (j == b.size()) {
            cout << i - (int)b.size() + 2 << '\n';
        }
    }

    for (int i = 1; i <= b.size(); ++i)
        cout << nxt[i] << ' ';

    return 0;
}