#include <cstdio>

#ifdef __LINUX__
#define getchar() getchar_unlocked()
#define putchar(a) putchar_unlocked(a)
#endif

#ifdef __WINDOWS__
#define getchar() _getchar_nolock()
#define putchar(a) _putchar_nolock()
#endif

template <typename __inputType>
void read(__inputType& x) {
    x = 0;
    bool f = 0;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') {
            f = 1;
        }
    } while (ch < 48 || ch > 57);
    do {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
    x *= (f ? -1 : 1);
}

template <typename __inputType, typename... __inputArgs>
void read(__inputType& x, __inputArgs&... __args) {
    read(x);
    read(__args...);
}

template <typename __outputType>
void write(__outputType __x, char __ch = ' ') {
    static short int __output_stack[64], __pos;
    __pos = 0;
    do {
        __output_stack[__pos++] = __x % 10;
        __x /= 10;
    } while (__x);
    while (__pos--) {
        putchar(__output_stack[__pos] ^ 48);
    }
    putchar(__ch);
}

template <typename __outputType, typename... __outputArgs>
void write(__outputType __x, char __ch, __outputArgs... __args) {
    write(__x, __ch);
    write(__args...);
}

#include <vector>

using llint = long long int;
using pii = std::pair<llint, llint>;

#define endl '\n'
#define N 200005

llint dis, cnt, noddis;
llint n, t1, t2, t3;
std::vector<llint> start;

struct edge {
    edge *nex, *opp;
    int val, to;
    int tim;
} graph[N << 2];
edge *fir[N], *tot = graph;
void add(int a, int b, int c) {
    tot->to = b;
    tot->val = c;
    tot->opp = tot + 1;
    tot->nex = fir[a];
    fir[a] = tot++;

    tot->to = a;
    tot->val = c;
    tot->opp = tot - 1;
    tot->nex = fir[b];
    fir[b] = tot++;
}

pii find_far(int nod, int fa) {
    llint st = nod, mxdis = 0;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        pii tmp = find_far(e->to, nod);
        if (tmp.second + e->val > mxdis) {
            mxdis = tmp.second + e->val;
            st = tmp.first;
        }
    }
    return (pii){ st, mxdis };
}

void find_start(int nod, int fa, llint res) {
    if (res == noddis) {
        start.emplace_back(nod);
        return;
    }
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        find_start(e->to, nod, res + e->val);
    }
}

int add_up(int nod, int fa, llint res) {
    if (res == dis) {
        ++cnt;
        return 1;
    }
    int hav = 0;
    for (edge* e = fir[nod]; e; e = e->nex) {
        if (e->to == fa) continue;
        int tmp = add_up(e->to, nod, res + e->val);
        e->tim += tmp;
        hav += tmp;
    }
    return hav;
}

int main() {
    read(n);
    start.reserve(n);
    for (int i = 1; i < n; ++i) {
        read(t1, t2, t3);
        add(t1, t2, t3);
    }

    noddis = find_far(1, 0).second;
    find_start(1, 0, 0);
    dis = find_far(start[0], 0).second;

    write(dis, '\n');

    for (auto& i : start)
        add_up(i, 0, 0);

    llint ans = 0;
    for (edge* e = graph; e->to; ++e)
        if (e->tim == cnt) ++ans;
    write(ans, '\n');
    return 0;
}