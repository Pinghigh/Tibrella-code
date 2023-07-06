#include <iostream>

using std::cin;
using std::cout;
using llint = long long int;

#define N 1000005

struct edge {
    edge* nex;
    llint to;
} graph[N << 1], *fir[N];
edge* tot = graph;
llint f[N], siz[N], dep[N];

void add(llint a, llint b) {
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

void get_f1(llint nod, llint fa) {
    siz[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        dep[e->to] = dep[nod] + 1;
        get_f1(e->to, nod);
        siz[nod] += siz[e->to];
    }
}

llint n;
llint t1, t2;

void get_ans(llint nod, llint fa) {
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        f[e->to] = f[nod] - 2 * siz[e->to] + siz[1];
        get_ans(e->to, nod);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (llint i = 1; i < n; ++i) {
        cin >> t1 >> t2;
        add(t1, t2);
        add(t2, t1);
    }
    get_f1(1, 0);
    llint ans = 0;
    for (llint i = 1; i <= n; ++i) {
        f[1] += dep[i];
    }
    get_ans(1, 0);
    f[0] = -114514;
    for (llint i = 1; i <= n; ++i) {
        if (f[i] > f[ans]) ans = i;
        // cout << f[i] << ' ';
    }
    cout << ans << '\n';

    return 0;
}