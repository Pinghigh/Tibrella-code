#include <bitset>
#include <iostream>
#include <queue>
#include <string>

using std::bitset;
using std::cin;
using std::cout;
using std::string;

#define N 30004

using i32 = int;

bitset<(N << 1)> vis, his, val;
i32 son[N << 1][2];
i32 tot;
i32 fail[N << 1];
bitset<(N << 1)> danger;

void insert(string& s) {
    i32 idx = 0;
    for (auto c : s) {
        c ^= 48;
        if (!son[idx][c]) son[idx][c] = ++tot;
        val[son[idx][c]] = c;
        idx = son[idx][c];
    }
    danger[idx] = true;
}

void build() {
    std::queue<i32> q;
    if (son[0][0]) q.push(son[0][0]);
    if (son[0][1]) q.push(son[0][1]);
    while (q.size()) {
        i32 nod = q.front();
        q.pop();
        if (danger[fail[nod]]) danger[nod] = true;
        for (char i = 0; i < 2; ++i) {
            if (son[nod][i]) {
                fail[son[nod][i]] = son[fail[nod]][i];
                if (danger[fail[son[nod][i]]]) danger[son[fail[nod]][i]] = true;
                q.push(son[nod][i]);
            } else
                son[nod][i] = son[fail[nod]][i];
        }
    }
}

i32 n;
string s;

#include <cstdlib>

void dfs(i32 nod) {
    if (vis[nod]) {
        cout << "TAK";
        exit(0);
    }
    if (his[nod] || danger[nod]) return;

    vis[nod] = his[nod] = true;

    for (char i = 0; i < 2; ++i) {
        dfs(son[nod][i]);
    }
    vis[nod] = false;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    while (n--) {
        cin >> s;
        insert(s);
    }

    build();
    dfs(0);
    cout << "NIE";

    return 0;
}