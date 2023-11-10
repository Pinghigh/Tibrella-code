#include <iostream>
#include <algorithm>
#include <string>

using std::cin;
using std::cout;

using i8 = char;
using i32 = int;
using i64 = long long;

#define N 500001

i32 fa[N], son[N], nxt[N];
std::string s;
i64 f[N], g[N];
i32 lst[N], stk[N], top;

i64 ans;
void dfs(const i32& u) {
    i32 lst = 0;
    if (s[u] == ')') {
        if (top) g[u] = g[fa[stk[top]]] + 1, lst = stk[top--];
    } else stk[++top] = u;
    f[u] = f[fa[u]] + g[u];
    ans ^= u * f[u];

    for (i32 v = son[u]; v; v = nxt[v]) 
        dfs(v);
    
    if (lst) stk[++top] = lst;
    else if (top) --top;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    i32 n;
    cin >> n >> s;
    s = '$' + s;
    for (i32 i = 2; i <= n; ++ i) {
        cin >> fa[i];
        nxt[i] = son[fa[i]]; son[fa[i]] = i;
    }
    dfs(1);
    cout << ans;

    return 0;
}