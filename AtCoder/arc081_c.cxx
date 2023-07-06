#include <bitset>
#include <iostream>
#include <list>
#include <queue>
#include <string>

#define N 200005
#define LET 30

int f[N][LET], pre[N], nxt[N], letter[N] /* 记录当前点代表什么字母 */;
std::string str;

std::queue<int> q;
std::bitset<N> st;

const int end = 200003;

int main() {
    std::ios::sync_with_stdio(false);
    using std::cin;
    using std::cout;
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> str;
    int siz = str.size();
    str = '$' + str;
    for (int j = 0; j < 26; ++j) {
        f[siz][j] = end;
    }
    for (int i = siz - 1; ~i; --i) {
        // if (str[i] <= 'z' && str[i] >= 'a') {
        for (int j = 0; j < 26; ++j) {
            f[i][j] = f[i + 1][j];
        }
        f[i][str[i + 1] - 'a'] = i + 1;
        // }
    }

    // BFS
    q.push(0);
    while (q.size()) {
        int x = q.front();
        q.pop();
        st[x] = 1;
        for (int i = 0; i < 26; ++i) {
            int y = f[x][i];
            if (!st[y]) {
                st[y] = true;
                pre[y] = x;  // 利用 bfs 的最短路特性确定顺序
                nxt[x] = y;
                letter[y] = i + 'a';
                q.push(y);
            }
        }
    }

    int i = end;
    std::list<char> ans;
    while (i) {
        ans.push_front(letter[i]);
        i = pre[i];
    }

    for (auto c : ans)
        putchar(c);

    return 0;
}