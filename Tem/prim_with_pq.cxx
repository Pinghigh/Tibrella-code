// P3366

#include <bitset>
#include <iostream>
#include <queue>

using std::bitset;
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::priority_queue;

#define PII pair<int, int>
#define N 51400
#define M 2005140

struct edge {
    int u, v;
    int w;
    edge* nex;
} gra[M];

priority_queue<PII, std::vector<PII>, std::greater<PII>> q;
int n, m;
bitset<N> st;
int ans;
edge* tot = gra;
edge* fir[N];
int t1, t2, t3;  // tmp
int cnt;         // 记录多少个边加入了最小生成树集合
int to;

void add(int a, int b, int c) {
    ++tot;
    tot->u = a;
    tot->v = b;
    tot->w = c;
    tot->nex = fir[a];
    fir[a] = tot;
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> t1 >> t2 >> t3;
        add(t1, t2, t3);
        add(t2, t1, t3);  // 无向图
    }

    q.push(make_pair(0, 1));

    // // 遍历第一个点的所有出边加入队列
    // for (edge* e = fir[1]; e; e = e->nex) {
    //     q.push(make_pair(e->w, e->v));
    //     /*
    //         每条边建立一个 pair，第一个元素存长度，第二个元素存边指向的点
    //         pair 首先比较第一个元素，第一个元素相等再比较第二个元素
    //     */
    // }
    // st[1] = 1;

    while (cnt < n) {
        while (st[q.top().second] && !q.empty()) {
            q.pop();
        }
        if (q.empty()) {
            cout << "orz" << endl;
            return 0;
        }

        to = q.top().second;  // 存储一下，防止后面加新的边把原来堆顶的边顶掉
        ++cnt;
        ans += q.top().first;
        st[to] = 1;

        for (edge* e = fir[to]; e; e = e->nex) {
            q.push(make_pair(e->w, e->v));
        }
    }
    cout << ans;

    return 0;
}
