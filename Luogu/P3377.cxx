#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>
#include <bitset>

using namespace __gnu_pbds;
using std::cin;
using std::cout;
using std::endl;

#define N 100005

int fa[N];
int rk[N];
int n, m;
int op;
int x,y;
int tmp1, tmp2;
int t1,t2;

struct num {
    int data;
    int id;
    bool operator< (const num& a) const {
        return (data < a.data) || (data == a.data && id < a.id);
    }
    bool operator> (const num& a) const {
        return (data > a.data) || (data == a.data && id > a.id);
    }
};

num tmp;

int max(int a, int b) {
    return (a>b?a:b);
}

int find(int a) {
    if (fa[a] != a) fa[a] = find(fa[a]);
    return fa[a];
}

void uni(int a, int b) {
    fa[b] = a;
}

priority_queue<num, std::greater<num>, rc_binomial_heap_tag> heaps[N];
std::bitset<N> st;

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0)->tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
        fa[i] = i;
        cin >> t1;
        tmp.id = i;
        tmp.data=t1;
        heaps[i].push(tmp);
    }
    while (m --) {
        cin >> op;
        if (op == 1) {
            cin >> t1 >> t2;
            if (st[t1] || st[t2]) continue;
            t1 = find(t1);
            t2 = find(t2);
            if (t1 == t2) continue;
            heaps[t1].join(heaps[t2]);
            uni(t1,t2);
        } else {
            cin >> t1;
            if (st[t1]) {
                cout << -1 << endl;
            } else {
                t1 = find(t1);
                st[heaps[t1].top().id] = 1;
                cout << heaps[t1].top().data << endl;
                heaps[t1].pop();
            }
        }
    }


    return 0;
}