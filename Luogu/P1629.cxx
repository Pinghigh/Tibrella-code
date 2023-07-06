#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <bitset>

using std::cin;
using std::cout;
using std::endl;
using std::priority_queue;
using std::max; 
using std::min;
using std::make_pair;
using std::bitset;
using std::vector;
using std::greater;

#define M 114514
#define N 1145
#define PII std::pair<int,int>

struct edge {
    int u,v;
    int nex;
    int w;
};

int fird[N], firr[N];
edge dir[M], rev[M];
int n,m;
int distd[N], distr[N];
priority_queue<PII, vector<PII>, greater<PII>> qd;
priority_queue<PII, vector<PII>, greater<PII>> qr;
bitset<N> st;
int idx;
int ans;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(fird, -1, sizeof fird);
    memset(firr, -1, sizeof firr);
    memset(distd, 0x3f, sizeof distd);
    memset(distr, 0x3f, sizeof distr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++ i) {
        cin >> dir[i].u >> dir[i].v >> dir[i].w;
        // 反向建图
        rev[i].u = dir[i].v;
        rev[i].w = dir[i].w;
        rev[i].v = dir[i].u;

        dir[i].nex = fird[dir[i].u];
        fird[dir[i].u] = i;

        rev[i].nex = firr[rev[i].u];
        firr[rev[i].u] = i;
    }

    distd[1] = 0;
    qd.push(make_pair(0,1));
    while (!qd.empty()) {
        idx = qd.top().second;
        qd.pop();
        if (st[idx]) {
            continue;
        }
        st[idx] = 1;

        for (int i = fird[idx]; ~i; i = dir[i].nex) {
            if (distd[dir[i].v] > distd[idx] + dir[i].w) {
                distd[dir[i].v] = distd[idx] + dir[i].w;
                qd.push(make_pair(distd[dir[i].v],dir[i].v));
            }
        }
    }

    st.reset();
    distr[1] = 0;
    qr.push(make_pair(0,1));
    while (!qr.empty()) {
        idx = qr.top().second;
        qr.pop();
        if (st[idx]) {
            continue;
        }
        st[idx] = 1;

        for (int i = firr[idx]; ~i; i = rev[i].nex) {
            if (distr[rev[i].v] > distr[idx] + rev[i].w) {
                distr[rev[i].v] = distr[idx] + rev[i].w;
                qr.push(make_pair(distr[rev[i].v], rev[i].v));
            }
        }
    }

    for (int i = 1; i <= n; ++ i) {
        ans += distr[i];
        ans += distd[i];
    }

    cout << ans;

    return 0;
}