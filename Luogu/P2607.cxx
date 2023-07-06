#include <cstdio>

using llint = long long int;
using ullint = unsigned long long int;
using sint = short int;
using uint = unsigned int;
using ldouble = long double;

#ifdef __WINDOWS__
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef __LINUX__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

char output_stk[40];
sint top;

template <typename T>
void read(T& x) {
    x = 0;
    static char ch;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename T, typename... Args>
void read(T& x, Args&... args) {
    read(x);
    read(args...);
}

template <typename T>
void write(T x) {
    do {
        output_stk[++top] = (x % 10) ^ 48;
        x /= 10;
    } while (x);
    do {
        putchar(output_stk[top]);
    } while (--top);
}

template <typename T>
void write(T x, char ch) {
    do {
        output_stk[++top] = (x % 10) ^ 48;
        x /= 10;
    } while (x);
    do {
        putchar(output_stk[top]);
    } while (--top);
    putchar(ch);
}

template <typename T, typename... Args>
void write(T& x, Args... args) {
    write(x);
    write(args...);
}

template <typename T, typename... Args>
void write(T& x, char ch, Args... args) {
    write(x, ch);
    write(args...);
}

#define N 1000006

struct edge {
    edge* nex;
    int to;
} graph[N << 1], *fir[N];
edge* tot = graph;
int ind[N];

void add(int a, int b) {
    ++ind[b];
    tot->to = b;
    tot->nex = fir[a];
    fir[a] = tot++;
}

int n;

#include <queue>

std::queue<int> q;
void topo() {
    for (int i = 1; i <= n; ++i)
        if (ind[i] == 1) q.push(i);
    while (q.size()) {
        int idx = q.front();
        q.pop();
        for (edge* e = fir[idx]; e; e = e->nex) {
            if (ind[v] > 1) {
                ind[e->to]--;
                if (ind[e->to] == 1) q.push(e->to);
            }
        }
    }
}

#include <bitset>

bitset<N> vis;
llint f[2][N][2];  // 1: 是否是环 3: 是否选

void dfs(int nod, int fa) {
    vis[nod] = 1;
    for (edge* e = fir[nod]; e; e = e->nex) {
        int to = e->to;
        if (to == fa || vis[to] || ind[to] != 1) continue;
        f[0][to][0] = max(f[0][nod][1], f[0][nod][0]);
        f[0][to][1] = f[0][nod][0] + power[to];
        dfs(to, nod);
    }
}

int t1, t2;
int power[N];
int ans;

int main() {
    read(n);

    for (int i = 1; i <= n; ++i) {
        read(power[i], t2);
        add(i, t2);
        add(t2, i);
    }

    topo();

    for (int i = 1; i <= n; ++i) {
        if (ind[i] == 1) continue;
        vis[i] = true;
        f[0][i][1] = power[i];
        dfs(i, 0);
    }

    // TODO: 添加一维记录第一个点是否选（只剩下环 DP 了）

    vis.reset();
    for (int i = 1; i <= n; ++i) {
        if (ind[i] != 1 && !vis[i]) {
            int start = i, fa;
            while (vis[start]) {
                vis[start] = true;
                int to;
                for (edge* e = fir[nod]; e; e = e->nex) {
                    to = e->to;
                    if (!vis[to] && ind[to] != 1) break;
                }
                if (to == start) break;
                f[1][to][1] = f[1][nod][0] + f[0][to][1];
                f[1][to][0] = max(f[1][nod][1], f[1][nod][0]) + f[0][to][0];
                start = to;
            }
            ans += (f[1][to][0]);
        }
    }

    return 0;
}