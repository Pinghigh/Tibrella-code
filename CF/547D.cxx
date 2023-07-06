#include <cstring>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

#define N 200005

using i32 = int;
using i8 = char;

std::vector<i32> e[N];

i32 lasx[N], lasy[N];

i32 n, x, y;

i8 c[N];

void add(i32 a, i32 b) {
    e[a].emplace_back(b);
    e[b].emplace_back(a);
}

void dfs(i32 nod, i32 col) {
    c[nod] = col;
    for (auto& to : e[nod])
        if (!~c[to]) dfs(to, col ^ 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    memset(c, -1, sizeof(i8) * (n + 3));
    for (i32 i = 1; i <= n; ++i) {
        cin >> x >> y;
        if (lasx[x]) {
            add(lasx[x], i);
            lasx[x] = 0;
        } else
            lasx[x] = i;

        if (lasy[y]) {
            add(lasy[y], i);
            lasy[y] = 0;
        } else
            lasy[y] = i;
    }

    for (i32 i = 1; i <= n; ++i) {
        if (!~c[i]) dfs(i, 0);
        cout << "br"[c[i]];
    }

    return 0;
}