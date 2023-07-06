#include <iostream>
#include <climits>

using std::cin;
using std::cout;
using std::endl;

#define N 200005

int fa[N];
int rk[N];
int ne[N];
int n;
int dis[N];
int t1,t2; // tmp
int res=INT_MAX;

int min(int a, int b) {
    return (a<b?a:b);
}
int find(int nod) {
    if (fa[nod] != nod) {
        int las = fa[nod];
        fa[nod] = find(fa[nod]);
        dis[nod] += dis[las];
    }
    return fa[nod];
}
void uni(int a, int b) {
    t1 = find(a);
    t2 = find(b);
    if (t1 != t2) {
        fa[t1] = t2;
        dis[a] = dis[b] + 1;
    } else {
        res = min(dis[a] + dis[b]+1,res);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        fa[i] = i;
        // dis[i] = 1;
    }
    for (int i = 1; i <= n; ++ i) {
        cin >> ne[i];
        uni(i,ne[i]);
    }
    cout << res << endl;
    return 0;
}