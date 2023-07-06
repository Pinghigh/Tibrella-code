// P7771
#pragma GCC target("avx2,popcnt,lzcnt,fma,sse4.1,sse4.2,bmi,bmi2,abm,sse2,sse3,sse4,mmx")
#include <algorithm>
#include <cstdio>

#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a)

template <typename T>
void read(T& x) {
    x = 0;
    char ch;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename T>
void write(T x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 ^ '0');
}

using namespace std;

#define N 100514
// #define int long long

class edge {
public:
    edge* nex;
    int u, v;
    bool vis;
} graph[N * 2];

edge* tot = graph;
edge* fir[N];
int n, m;
int st, en;  // 起点
int t1, t2;
int ind[N], oud[N];
int ans[N * 2];
int tail;
pair<int, int> dat[N * 4];
int cnt;
void add(int a, int b) {
    ++tot;
    tot->u = a;
    tot->v = b;
    tot->nex = fir[a];
    fir[a] = tot;
    ++ind[b];
    ++oud[a];
}

void dfs(int num) {
    if (tail > m) return;
    for (edge* e = fir[num]; fir[num]; fir[num] = e->nex) {
        e = fir[num];
        if (e->vis) continue;
        e->vis = 1;
        dfs(e->v);
    }
    // ans.push_back(num);
    ans[++tail] = num;
}

signed main() {
    read(n);
    read(m);
    for (int i = 1; i <= m; ++i) {
        read(dat[i].second);
        read(dat[i].first);
    }
    sort(dat + 1, dat + m + 1, greater<pair<int, int>>);
    for (int i = 1; i <= m; ++i) {
        add(dat[i].second, dat[i].first);
    }
    // ans.reserve(2 * n);
    for (int i = 1; i <= n; ++i) {
        if (oud[i] - ind[i] == 1) {
            st = i;
            ++cnt;
        } else if (oud[i] == ind[i] - 1) {
            en = i;
            ++cnt;
        } else if (oud[i] != ind[i]) {
            ++cnt;
        }
    }
    if (cnt == 0) {
        st = en = 1;
    }
    if ((cnt != 0 && cnt != 2) || !st || !en) {
        puts("No");
        return 0;
    }

    if (n == 2) {
        for (int i = 0; i <= m; ++i) {
            write(1 + (i % 2));
            putchar(' ');
        }
        return 0;
    }

    dfs(st);

    for (auto it = tail; it > 0; --it) {
        printf("%d ", ans[it]);
    }

    return 0;
}