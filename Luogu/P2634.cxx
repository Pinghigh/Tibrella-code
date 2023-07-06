#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;

using i8 = char;
using i32 = int;
using i64 = long long;

#define N 20004

const i32 kInf = 0x3f3f3f3f;
const i8 kMod = 3;

i32 kCnt;

std::bitset<N> vis;
struct edge {
    edge* nex;
    i32 to;
    i32 w;
} graph[N << 1], *fir[N];
edge* tot = graph;

void add(i32 a, i32 b, i32 w) {
    tot->to = b;
    tot->w = w;
    tot->nex = fir[a];
    fir[a] = tot++;
}

i32 rt_max_siz, rt, siz[N];

void getRoot(i32 nod, i32 fa, i32 nodCnt) {
    siz[nod] = 1;
    i32 max_siz = -kInf;
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to != fa && !vis[to]) {
            getRoot(to, nod, nodCnt);
            siz[nod] += siz[to];
            max_siz = std::max(max_siz, siz[to]);
        }
    }
    max_siz = std::max(max_siz, nodCnt - siz[nod]);
    if (max_siz < rt_max_siz) rt = nod, rt_max_siz = max_siz;
}

i32 tmp1, tmp2, tmp3;

i32 lenPathCnt[kMod];  // 当前树中模 3 余 i 的路径数量

void dfs(i32 nod, i32 fa, i32 val) {  // val 用来随时取模
    ++lenPathCnt[val];
    for (edge* e = fir[nod]; e; e = e->nex) {
        i32 to = e->to;
        if (to != fa && !vis[to]) dfs(to, nod, (val + e->w) % kMod);
    }
}

i32 calc(i32 nod, i32 val) {  // 返回当前树中，(路径长度 + val % 3 == 0) 的路径数量
    memset(lenPathCnt, 0, sizeof lenPathCnt);
    dfs(nod, 0, val);
    return lenPathCnt[0] * lenPathCnt[0] + (lenPathCnt[1] * lenPathCnt[2] << 1);
}

i32 ans;

void solve(i32 root) {
    ans += calc(root, 0);
    vis[root] = true;
    for (edge* e = fir[root]; e; e = e->nex) {
        i32 to = e->to;
        if (!vis[to]) {
            ans -= calc(to, e->w % kMod);
            rt = 0;
            rt_max_siz = kInf;
            getRoot(to, root, siz[to]);  // 新树的 size != kCnt
            solve(rt);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> kCnt;
    for (i32 i = 1; i < kCnt; ++i) {
        cin >> tmp1 >> tmp2 >> tmp3;
        add(tmp1, tmp2, tmp3);
        add(tmp2, tmp1, tmp3);
    }

    rt_max_siz = kInf;
    getRoot(1, 0, kCnt);
    solve(rt);

    i32 gcd = [](i32 x, i32 y) -> i32 {
        while (y) {
            x = x % y;
            std::swap(x, y);
        }
        return x;
    }(ans, kCnt * kCnt);

    cout << (ans) / gcd << '/' << (kCnt * kCnt) / gcd;

    return 0;
}