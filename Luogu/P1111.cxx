#include <bitset>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

// #define getchar() getchar_unlocked()

template <class T>
void read(T& x) {
    x = 0;
    char ch;
    do {
        ch = getchar();
    } while (!isdigit(ch));
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (isdigit(ch));
}

template <class T>
T max(T& a, T& b) {
    return (a > b ? a : b);
}

template <class T>
T min(T& a, T& b) {
    return (a < b ? a : b);
}

#define N 1514
#define M 1005140
#define PII pair<int, int>

class edge {
public:
    int v;
    edge* nex;
    int end;
} graph[M];
edge* tot = graph;
edge* fir[N];
bitset<N> st;
int n, m;
int t1, t2, t3;
priority_queue<PII, vector<PII>, greater<PII> > q;
int root;
int e;
int ans;
int idx;

void add(int a, int b, int c);

int main() {
    read(n);
    read(m);
    for (int i = 1; i <= m; ++i) {
        read(t1);
        read(t2);
        read(t3);
        add(t1, t2, t3);
        add(t2, t1, t3);
        root = t1;
    }
    st[root] = 1;

    for (edge* i = fir[root]; i; i = i->nex) {
        q.push(make_pair(i->end, i->v));
    }
    while (e < n - 1) {
        while (st[q.top().second] && !q.empty()) {
            q.pop();
        }
        if (q.empty()) {
            puts("-1");
            return 0;
        }
        // printf("[INFO] nod:%d e:%d qsize:%d end:%d\n", q.top().second,e,q.size(),q.top().first);
        ans = max(ans, q.top().first);
        ++e;
        idx = q.top().second;
        q.pop();
        st[idx] = 1;
        for (edge* i = fir[idx]; i; i = i->nex) {
            //        	printf("[POS] i:%d",i);
            // printf("[FIND] from %d to %d end:%d \n",idx,i->v,i->end);
            // 	printf("[PUSH] from %d to %d\n",idx ,i->v);
            q.push(make_pair(i->end, i->v));
        }
    }
    printf("%d\n", ans);
    return 0;
}

void add(int a, int b, int c) {
    ++tot;
    tot->v = b;
    tot->nex = fir[a];
    tot->end = c;
    fir[a] = tot;
}