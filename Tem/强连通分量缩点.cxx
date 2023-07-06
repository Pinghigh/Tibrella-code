// P3387

#include <bitset>
#include <cstring>
#include <iostream>

using std::bitset;
using std::cin;
using std::cout;

#define endl '\n'
#define N 100100
#define M 500100

int n, m;
int t1, t2;

class graph {
private:
    int min(int a, int b) {
        return a < b ? a : b;
    }
    int max(int a, int b) {
        return a > b ? a : b;
    }
    int dfn[N], low[N], tim;
    int sta[N], top;
    bitset<N> st;
    int outd[N], ind[N];
    int f[N];
    struct edge {
        edge* nex;
        int to;
    } es[M], *fir[N];
    int siz[N], id[N];
    int val[N];
    edge* tot = es;
    int cnt;
    int mxnod;

    int dfs(int nod) {
        int tmp = 0;
        if (f[nod]) return f[nod];
        f[nod] = val[nod];
        for (edge* e = fir[nod]; e; e = e->nex) {
            tmp = max(tmp, dfs(e->to));
        }
        f[nod] += tmp;
        return f[nod];
    }

    void __tarjan(int nod) {
        dfn[nod] = low[nod] = ++tim;  // 加时间戳
        sta[++top] = nod;             // 入栈
        st[nod] = true;
        for (edge* e = fir[nod]; e; e = e->nex) {
            int to = e->to;
            if (!dfn[to]) {
                __tarjan(to);
                low[nod] = min(low[nod], low[to]);
            } else if (st[to]) {
                low[nod] = min(low[nod], dfn[to]);
            }
        }

        if (dfn[nod] == low[nod]) {
            ++cnt;
            int pop;
            do {
                pop = sta[top--];
                st[pop] = false;
                id[pop] = cnt;
                siz[cnt] += val[pop];
            } while (pop != nod);
        }
    }

public:
    void add(int a, int b) {
        ++tot;
        tot->to = b;
        tot->nex = fir[a];
        fir[a] = tot;
        ++ind[b];
        ++outd[a];
    }

    void tarjan() {
        for (int i = 1; i <= mxnod; ++i) {
            if (!dfn[i]) __tarjan(i);
        }
    }

    void set_siz(int x) {
        mxnod = x;
    }

    void add_val(int& nod, int& v) {
        val[nod] = v;
    }

    void contract(graph& g) {
        g.set_siz(cnt);
        for (int i = 1; i <= mxnod; ++i) {
            for (edge* e = fir[i]; e; e = e->nex) {
                if (id[i] != id[e->to]) {
                    g.add(id[i], id[e->to]);
                }
            }
        }
        for (int i = 1; i <= cnt; ++i) {
            g.val[i] = siz[i];
        }
    }
    int find_max() {
        int res = 0;
        for (int i = 1; i <= mxnod; ++i) {
            if (!ind[i]) {
                res = max(res, dfs(i));
            }
        }
        return res;
    }

    void debug() {
        cout << "mxnod: " << mxnod << endl;
        for (int i = 1; i <= mxnod; ++i) {
            cout << "i: " << i << " f[i]: " << val[i] << endl;
        }
    }
} ori, nxt;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> t2;
        ori.add_val(i, t2);
    }
    for (int i = 1; i <= m; ++i) {
        cin >> t1 >> t2;
        ori.add(t1, t2);
    }
    ori.set_siz(n);
    ori.tarjan();
    ori.contract(nxt);
    cout << nxt.find_max() << endl;
    // nxt.debug();

    return 0;
}