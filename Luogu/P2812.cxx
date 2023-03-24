#include <bitset>
#include <cstring>
#include <iostream>

using std::bitset;
using std::cin;
using std::cout;

#define endl '\n'
#define N 100100
#define M 5001000
#define llint long long int

llint n, m;
llint t1, t2;

class graph {
private:
    llint min(llint a, llint b) {
        return a < b ? a : b;
    }
    llint max(llint a, llint b) {
        return a > b ? a : b;
    }
    llint dfn[N], low[N], tim;
    llint sta[N], top;
    bitset<N> st;
    llint outd[N], ind[N];
    struct edge {
        edge* nex;
        llint to;
    } es[M], *fir[N];
    llint siz[N], id[N];
    llint val[N];
    edge* tot = es;
    llint cnt;

    void __tarjan(llint nod) {
        dfn[nod] = low[nod] = ++tim;  // 加时间戳
        sta[++top] = nod;             // 入栈
        st[nod] = true;
        for (edge* e = fir[nod]; e; e = e->nex) {
            llint to = e->to;
            if (!dfn[to]) {
                __tarjan(to);
                low[nod] = min(low[nod], low[to]);
            } else if (st[to]) {
                low[nod] = min(low[nod], dfn[to]);
            }
        }

        if (dfn[nod] == low[nod]) {
            ++cnt;
            llint pop;
            do {
                pop = sta[top--];
                st[pop] = false;
                id[pop] = cnt;
                ++siz[cnt];
            } while (pop != nod);
        }
    }

public:
    llint mxnod;
    void add(llint a, llint b) {
        ++tot;
        tot->to = b;
        tot->nex = fir[a];
        fir[a] = tot;
        ++ind[b];
        ++outd[a];
    }

    void tarjan() {
        for (llint i = 1; i <= mxnod; ++i) {
            if (!dfn[i]) __tarjan(i);
        }
    }

    void set_siz(llint x) {
        mxnod = x;
    }

    void add_val(llint& nod, llint& v) {
        val[nod] = v;
    }

    void contract(graph& g) {
        g.set_siz(cnt);
        for (llint i = 1; i <= mxnod; ++i) {
            for (edge* e = fir[i]; e; e = e->nex) {
                if (id[i] != id[e->to]) {
                    g.add(id[i], id[e->to]);
                }
            }
        }
        for (llint i = 1; i <= cnt; ++i) {
            g.val[i] = siz[i];
        }
    }
    llint cnt_outd() {
        llint res = 0;
        for (llint i = 1; i <= mxnod; ++i)
            if (!outd[i]) ++res;
        return res;
    }
    llint cnt_ind() {
        llint res = 0;
        for (llint i = 1; i <= mxnod; ++i)
            if (!ind[i]) ++res;
        return res;
    }

    void debug() {
        cout << "mxnod: " << mxnod << endl;
        for (llint i = 1; i <= mxnod; ++i) {
            cout << "i: " << i << " f[i]: " << val[i] << endl;
        }
    }
} ori, nxt;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (llint i = 1; i <= n; ++i) {
        while ((cin >> t1), t1) {
            ori.add(i, t1);
        }
    }
    ori.set_siz(n);
    ori.tarjan();
    ori.contract(nxt);

    t1 = nxt.cnt_ind();
    t2 = nxt.cnt_outd();
    cout << t1 << endl;
    cout << (t1 > t2 ? t1 : (nxt.mxnod == 1) ? 0 : t2) << endl;

    return 0;
}