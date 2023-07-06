#include <bitset>
#include <iostream>
#include <string>
#include <unordered_map>

using std::bitset;
using std::cin;
using std::cout;
using std::string;
using std::unordered_map;

template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
}

unordered_map<string, int> mp;

#define N 40050
#define M 200050
#define endl '\n'

string s1, s2;
int n, m;
int ta;
int dfn[N], low[N], tim;
int sta[N], top;
int cnt;
int outd[N];
int id[N];
bitset<N> st;

struct edge {
    edge* nex;
    int u, v;
} graph[M];

edge *tot = graph, *fir[N];

void add(int a, int b) {
    ++tot;
    tot->u = a;
    tot->v = b;
    tot->nex = fir[a];
    fir[a] = tot;
}

void tarjan(int nod) {
    dfn[nod] = low[nod] = ++tim;  // 更新时间戳
    sta[++top] = nod;             // 新点压入栈
    st[nod] = true;               // 记录当前点已入栈
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->v;
        if (!dfn[to]) {
            tarjan(to);
            low[nod] = min(low[nod], low[to]);
        } else if (st[to])
            low[nod] = min(low[nod], low[to]);
    }

    if (dfn[nod] == low[nod]) {
        ++cnt;
        int pop;
        do {
            pop = sta[top--];
            st[pop] = false;
            id[pop] = cnt;
        } while (pop != nod);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s1 >> s2;
        mp[s1] = i;
        mp[s2] = i + n;
        add(i, i + n);
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> s1 >> s2;
        add(mp[s2], mp[s1]);
    }

    for (int i = 1; i <= 2 * n; ++i) {
        if (!dfn[i]) tarjan(i);
    }

    for (int i = 1; i <= n; ++i) {
        if (id[i] == id[i + n])
            cout << "Unsafe" << endl;
        else
            cout << "Safe" << endl;
    }

    return 0;
}