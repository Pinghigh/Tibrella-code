#include <algorithm>
#include <iostream>


using std::cin;
using std::cout;
using std::endl;
using std::sort;

#define N 20010
#define M 114514

struct rel {
    int a, b;
    int data;

    bool operator<(rel exa) { return data < exa.data; }
    bool operator>(rel exa) { return data > exa.data; }
} all[M];
int fa[2 * N];
int n, m;
int rk[2 * N];
int fr, to;

template <class T>
T max(T a, T b) {
    return (a > b ? a : b);
}

template <class T>
T find(T a) {
    if (fa[a] != a) {
        fa[a] = find(fa[a]);
    }
    return fa[a];
}

template <class T>
void uni(T a, T b) {
    T tmp1, tmp2;
    tmp1 = find(a);
    tmp2 = find(b);
    if (rk[tmp1] > rk[tmp2]) {
        fa[tmp2] = tmp1;
        rk[tmp1] = max(rk[tmp1] + 0, rk[tmp2] + 1);
    } else {
        fa[tmp1] = tmp2;
        rk[tmp2] = max(rk[tmp1] + 1, rk[tmp2] + 0);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (rel* i = all + 1; i - all <= m; ++i) {
        cin >> i->a >> i->b >> i->data;
    }
    for (int i = 0; i <= 2 * n; ++i) {
        fa[i] = i;
    }
    sort(all + 1, all + m + 1);
    for (rel* i = all + m; i > all; --i) {
        fr = i->a;
        to = i->b;
        if (find(fr) == find(to) || find(to+n) == find(fr+n)) {
            cout << i->data << endl;
            return 0;
        } else {
            uni(fr, to + n);
            uni(to, fr + n);
        }
    }
    cout << "0" << endl;

    return 0;
}