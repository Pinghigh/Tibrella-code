# 网络最大流——最高标号预流推进

## 0、写在前面

解决最大流问题，最常用的算法是 Dinic 和 ISAP，两种算法在实际应用中都相当快速。但是就理论而言，两种算法都属于增广路算法，复杂度上界都达到了 $\operatorname{O}(n^2m)$，因此在某些题目中或许存在毒瘤出题人构造数据卡这两种算法的情况。因此本文讲解一种复杂度上界在常用最大流算法中最优的最高标号预留推进算法（又叫 HLPP），其上界为 $\operatorname{O}(n^2\sqrt{m})$，并且在经过优化后这种算法在数据随机的情况下速度也不亚于上述两种增广路算法。

> 抱歉...我已经 绝对不可能再获得幸福了

## 1、预流推进的思想

HLPP 是预流推进算法中的一种，介绍一下预流推进算法的思想：

我们还是以水流来类比网络流。我们将每个点看作一个水库，每条边看作单向的管道。预流推进算法的思想就是，允许水在非源汇点的节点中暂时存储（我们将存储在非源汇点中的流称作这个点的超额流），同时伺机将自身的超额流通过管道推送出去。只要保证在算法结束后所有非源汇点的超额流都为 $0$，那么这种方案就是合法的。

同时为了避免反复推送而出现死循环的问题，我们再给每个节点引入高度的概念。同实际中一样，我们只允许高度较高的节点向高度较低的节点进行推送（不过还是略有不同，具体请见下文）。如果一个节点因为受到高度的限制而不能推送自身的超额流，那么我们就抬高这个节点的高度，我们把这个操作叫做重贴标签。

> 因为...我发现...

## 2、最高标号预流推进的过程

下面介绍 HLPP
的具体流程，在下文中，我们用 $e_v$ 表示节点 $v$ 的超额流，用 $h_v$ 表示节点 $v$ 的高度。

首先，我们将除了源点以外的节点的高度都置为 $0$
。特别地，我们将源点 $s$ 的高度置为 $n$，并且将 $s$ 的所有边都充满流量推送出去。我们不必担心这种操作会让流变得太多，因为多余的流量会在别的节点高度抬高到超过 $s$ 以后推送回去。我们还应该将推送过后超额流不为 $0$ 的节点加入队列中等待推送，同时，因为 HLPP 会要求我们每次都推送高度最高的节点（注意是对于超额流不为 $0$ 的节点而言的），因此这应当是一个以高度为键值的优先队列。

在进行完上述操作以后，我们开始处理优先队列。我们每次都取出队首 $v$ 并尝试推送，推送过程如下：逐一检查 $v$ 的出边，如果发现某条边还有流量并且边的另一端 $u$ 满足 $h_u+1=h_v$，即 $v$ 正好比 $u$ 的高度高 $1$ （注意在初始操作中对 $s$ 的推送并没有这个要求），那么这条边就是可以推送的。我们推送的流量应当既不可以超过这条边的流量，也不可以超过ev。在推送完成后记得修改 $u$ 和 $v$ 的超额流，并且如果 $u$ 还不在优先队列中，那么应当将 $u$ 加入优先队列。

推送过程执行完毕后，如果我们发现 $e_v$ 仍然不等于 $0$，说明当前的高度 $h_v$ 并不够，因此我们对 $v$ 重贴标签。我们找到有流量而且边的另一端 $u$ 高度最小的边，将 $h_v$ 设置为 $h_u+1$，这样就保证了下次一定可以推送。于是我们再将重贴标签后的 $v$ 加入优先队列中。

如果优先队列为空，那么除了源汇点以外的所有节点超额流都为 $0$，这是一个合法的流，并且也是最大流。

> 其实我...早就已经被幸福包围了

## 3、一点优化

虽然上述的算法是正确的，并且复杂度是 $\operatorname{O}(n^2\sqrt{m})$ 的，但是因为缺少一些优化，使得其上界比较紧，因此在随机数据下可能不如增广路算法。下面介绍对 HLPP 的优化，使得其在随机数据下的速度可以与增广路算法媲美。

首先，我们可以发现将所有非源点的高度设置为 $0$ 是有些浪费的。我们不妨通过一遍 bfs 将每个点的初始高度设置为它到汇点 $t$ 的最短距离，这样就节省了大量重贴标签操作。当然，源点s的高度还是应该设置为 $n$。

然后，我们还可以发现如果一个点 $v$ 再被重贴标签以后，如果它原来的高度已经没有其它点，那么高于它的点一定不能将流量推送到 $t$ 了。所以我们可以将高度大于 $h_v$ 且小于 $n+1$ 的点高度设置为 $n+1$，以便尽快将流量推送给 $s$。对于如何判断这个高度已经没有其它节点，可以和 ISAP 一样用一个 gap 数组来计数，这就是 HLPP 的 gap 优化。

> ——珂朵莉·诺塔·瑟尼欧里斯

## 4、C++实现

因为 HLPP 的细节还是挺多的，这里就放一下我的代码吧。HLPP 的码量其实不多，我这样的写法也只是 $100$ 行出头而已。所以在网络流问题中使用 HLPP 也是一个不错的选择。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

using std::min;
using std::priority_queue;
using std::queue;
using std::vector;
const int N = 2e4 + 5, M = 2e5 + 5, inf = 0x3f3f3f3f;
int n, s, t, tot;
int v[M << 1], w[M << 1], first[N], next[M << 1];
int h[N], e[N], gap[N << 1], inq[N];  // 节点高度是可以到达2n-1的
struct cmp {
    inline bool operator()(int a, int b) const {
        return h[a] < h[b];  // 因为在优先队列中的节点高度不会改变，所以可以直接比较
    }
};
queue<int> Q;
priority_queue<int, vector<int>, cmp> pQ;
inline void add_edge(int from, int to, int flow) {
    tot += 2;
    v[tot + 1] = from;
    v[tot] = to;
    w[tot] = flow;
    w[tot + 1] = 0;
    next[tot] = first[from];
    first[from] = tot;
    next[tot + 1] = first[to];
    first[to] = tot + 1;
    return;
}
inline bool bfs() {
    int now;
    register int go;
    memset(h + 1, 0x3f, sizeof(int) * n);
    h[t] = 0;
    Q.push(t);
    while (!Q.empty()) {
        now = Q.front();
        Q.pop();
        for (go = first[now]; go; go = next[go])
            if (w[go ^ 1] && h[v[go]] > h[now] + 1) h[v[go]] = h[now] + 1, Q.push(v[go]);
    }
    return h[s] != inf;
}
inline void push(int now)  // 推送
{
    int d;
    register int go;
    for (go = first[now]; go; go = next[go])
        if (w[go] && h[v[go]] + 1 == h[now]) {
            d = min(e[now], w[go]);
            w[go] -= d;
            w[go ^ 1] += d;
            e[now] -= d;
            e[v[go]] += d;
            if (v[go] != s && v[go] != t && !inq[v[go]]) pQ.push(v[go]), inq[v[go]] = 1;
            if (!e[now])  // 已经推送完毕可以直接退出
                break;
        }
    return;
}
inline void relabel(int now)  // 重贴标签
{
    register int go;
    h[now] = inf;
    for (go = first[now]; go; go = next[go])
        if (w[go] && h[v[go]] + 1 < h[now]) h[now] = h[v[go]] + 1;
    return;
}
inline int hlpp() {
    int now, d;
    register int i, go;
    if (!bfs())  // s和t不连通
        return 0;
    h[s] = n;
    memset(gap, 0, sizeof(int) * (n << 1));
    for (i = 1; i <= n; i++)
        if (h[i] < inf) ++gap[h[i]];
    for (go = first[s]; go; go = next[go])
        if (d = w[go]) {
            w[go] -= d;
            w[go ^ 1] += d;
            e[s] -= d;
            e[v[go]] += d;
            if (v[go] != s && v[go] != t && !inq[v[go]]) pQ.push(v[go]), inq[v[go]] = 1;
        }
    while (!pQ.empty()) {
        inq[now = pQ.top()] = 0;
        pQ.pop();
        push(now);
        if (e[now]) {
            if (!--gap[h[now]])  // gap优化，因为当前节点是最高的所以修改的节点一定不在优先队列中，不必担心修改对优先队列会造成影响
                for (i = 1; i <= n; i++)
                    if (i != s && i != t && h[i] > h[now] && h[i] < n + 1) h[i] = n + 1;
            relabel(now);
            ++gap[h[now]];
            pQ.push(now);
            inq[now] = 1;
        }
    }
    return e[t];
}
int m;
signed main() {
    int u, v, w;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    while (m--) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
    }
    printf("%d\n", hlpp());
    return 0;
}
```