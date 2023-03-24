#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

#define N 20514
#define PII pair<int,int>

struct edge {
    int no;
    int u, v;
    int l1, l2;
    void init(int& a) {
        no = a;
        cin >> u >> v >> l1 >> l2;
    }
    bool operator<(const edge& a){
    	return l1<a.l1;
	}
} graph[N];

// edge* tot = graph;
// edge* fir[N];
int n, k, m;
int c1, c2;
int t1, t2, t3, t4;
int fa[N];
int rk[N];
int ans;
PII res[N];
int tail;
int max2;

int max(int a, int b) { return (a > b ? a : b); }

bool cmp(PII a, PII b) {
    return a.first < b.first;
}

int find(int a) {
    if (fa[a] != a) {
        fa[a] = find(fa[a]);
    }
    return fa[a];
}

void uni(int a, int b) {
    t1 = find(a);
    t2 = find(b);
    if (rk[t1] > rk[t2]) {
        fa[t2] = t1;
        rk[t1] = max(rk[t1], rk[t2] + 1);
    } else {
        fa[t1] = t2;
        rk[t2] = max(rk[t1], rk[t2] + 1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> m;
    for (int i = 1; i < m; ++i) {
        graph[i].init(i);
    }
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    sort(graph + 1, graph + m - 1);

    for (int i = 1; i < n; ++i) {
        t1 = find(graph[i].u);
        t2 = find(graph[i].v);
        if (t1 == t2) {
            continue;
        }
        uni(t1, t2);
        res[++tail].first = graph[i].no;
        res[tail].second = 1;
    }
    // for (int i = n-1; i >= k; --i) {
    //     if (i == k) {
    //         ans = max(ans,graph[i].l1);
    //         break;
    //     }
    //     res[tail--].second=2;
    //     ans = max(ans,graph[i].l2);
    //     if (graph[i].l2>graph[i-1].l1) {
    //         break;
    //     }
    // }
    sort(res+1,res+tail+1,cmp);
    cout << ans << endl;
    for (int i = 1; i <= tail; ++ i) {
        cout << res[i].first << ' ' << res[i].second << endl;
    }

    return 0;
}
