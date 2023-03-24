#include <bitset>
#include <cstdio>
#include <cstring>
#include <queue>

template <typename Type>
void read(Type& _x) {
    _x = 0;
    bool f;
    char ch;
    f = 0;
    do {
        ch = getchar();
        if (ch == '-') f = 1;
    } while (ch < 48 || ch > 57);
    do {
        _x = (_x << 3) + (_x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
    _x = f ? -_x : _x;
}

template <typename Type>
Type max(Type _a, Type _b) {
    return _a > _b ? _a : _b;
}

using std::bitset;
using std::queue;

#define N 105

struct edge {
    edge* nex;
    int u, v, w;
} graph[N * N];
edge* fir[N];
int outd[N];
int dis[N];
edge* idx = graph;
int n;

int l = 1, r = 10001, mid;
queue<int> q;
bitset<N> st;

void add(int u, int v, int w) {
    ++idx;
    idx->u = u;
    idx->v = v;
    idx->w = w;
    idx->nex = fir[u];
    ++outd[u];
    fir[u] = idx;
}

void spfa(int nod);

int t1, t2, t3;

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            read(t1);                // 中转变量
            if (t1) add(j, i, -t1);  // 反向存图
        }
    }

    spfa(n);

    printf("%d", dis[1]);

    return 0;
}

void spfa(int nod) {
    st.reset();
    memset(dis, 0x80, sizeof dis);
    dis[nod] = 0;
    st[nod] = 1;
    q.push(nod);

    while (!q.empty()) {
        nod = q.front();
        q.pop();
        st[nod] = 0;
        for (edge* e = fir[nod]; e; e = e->nex) {
            if (dis[e->v] > max(1, (dis[nod] + e->w + 1) / 2)) {  // +1 防止向下取整造成错误
                dis[e->v] = max(1, (dis[nod] + e->w + 1) / 2);
                if (!st[e->v]) {
                    q.push(e->v);
                    st[e->v] = 0;
                }
            }
        }
    }
}