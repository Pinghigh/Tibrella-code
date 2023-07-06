#include <bitset>
#include <cstring>
#include <iostream>
#include <stack>

using std::bitset;
using std::cin;
using std::cout;
using std::stack;

#define endl '\n'

#define N 100004
#define M 1000005

auto max = [](auto a, auto b) { return a > b ? a : b; };

struct edge {
    edge* nex;
    int fr, to;
} graph[M], rgraph[M], agraph[M];
edge *po = graph, *pr = rgraph, *pa = agraph;
edge *ofir[N], *rfir[N], *afir[N];
int node[N];

void add(int a, int b, edge*& tot, edge** fir) {
    tot->fr = a;
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot;
    ++tot;
}

stack<int> sta;
int n, m;
int t1, t2;
int id[N];
int siz[N];
int scc_cnt;
bitset<N> vis;
int ind[N], outd[N];

void dfs(int nod) {
    if (vis[nod]) return;
    vis[nod] = true;
    for (edge* e = rfir[nod]; e; e = e->nex) {
        if (!vis[e->to]) dfs(e->to);
    }
    sta.push(nod);
}

void add_up(int nod) {
    id[nod] = scc_cnt;
    siz[scc_cnt] += node[nod];
    for (edge* e = ofir[nod]; e; e = e->nex) {
        if (!id[e->to]) add_up(e->to);
    }
}

int f[N];

int adfs(int nod) {
  int tmp = 0;
  if (f[nod]) return f[nod];
  f[nod] = siz[nod];
  for (edge* e = afir[nod]; e; e = e->nex) {
    tmp = max(tmp, adfs(e->to));
  }
  f[nod] += tmp;
  return f[nod];
}

int ans() {
  int res = 0;
  for (int i = 1; i <= scc_cnt; ++i) {
    if (!ind[i]) {
      res = max(res, adfs(i));
    }
  }
  return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> node[i];
    // cout << "FUCK" << endl;
    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        add(t1, t2, po, ofir);
        add(t2, t1, pr, rfir);
    }

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) dfs(i);
    }
    vis.reset();
//    while (sta.size()) {
//        int to = sta.top();
//        sta.pop();
//        if (sta.empty()) break;
//        if (id[to]) continue;
//        ++scc_cnt;
//        add_up(sta.top());
//    }


    for (int i = 1; i <= n; ++ i) {
        if (!id[sta.top()]) ++scc_cnt, add_up(sta.top());
        sta.pop();
    }

//    for (int i = 1; i <= n; ++i) {
//        for (edge* e = ofir[i]; e; e = e->nex) {
//            if (id[i] ^ id[e->to]) {
//                add(id[i], id[e->to], pa, afir);
//                ++ind[id[e->to]];
//            }
//        }
//    }

    for (edge* e = graph; e != po; ++ e) {
      if (id[e->fr] != id[e->to]) add(id[e->fr], id[e->to], pa, afir), ++ind[id[e->to]];
    }

    cout << ans() << endl;

    return 0;
}