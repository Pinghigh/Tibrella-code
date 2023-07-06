#include <algorithm>
#include <queue>
#include <bitset>
#include <cstring>
#include <algorithm>

using namespace std;

#define N 1000100

int u[N], v[N], nexti[N], first[N];
int idx;
int n,m;
int t1,t2;
bitset<N> st;
queue<int> q;

int read() {
    int x = 0,f=1;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') f = -1;
    } while (ch > '9' || ch < '0');
    do {
        x = x*10 + ch -'0';
        ch = getchar();
    } while (ch <= '9' && ch >= '0');
    return f*x;
} 

void dfs(int a) {
    st[a]=1;
    printf("%d ",a);
    if (first[a] == -1) {
        return;
    }
    int i = first[a];
    while (i != -1) {
        if (!st[v[i]]) {
            dfs(v[i]);
        }
        i = nexti[i];
    }
}

void bfs() {
    while (!q.empty()) {
        printf("%d ",q.front());
        
        for (int i = first[q.front()]; ~i; i = nexti[i]) {
            if (!st[v[i]]) {
                st[v[i]] = 1;
                q.push(v[i]);
            }
        }
        q.pop();
    }
}

struct Node {
    int a,b;

    bool operator<(Node j) {
        return b>j.b;
    }
} nodes[N];

int main() {
    memset(first,-1,sizeof first);

    n=read(), m=read();
    for (int i = 0; i < m; ++ i) {
        nodes[i].a = read(); nodes[i].b = read();
    }

    sort(nodes, nodes+m);

    for (int i = 0; i < m; ++ i) {
        // cout << nodes[i].a << ' ' << nodes[i].b << endl;
        t1=nodes[i].a, t2=nodes[i].b;
        nexti[++idx]=first[t1];
        first[t1]=idx;
        u[idx]=t1;
        v[idx]=t2;
    }

    dfs(1);

    st.reset();
    putchar('\n');
    
    st[1]=1;
    q.push(1);
    bfs();

    return 0;
}