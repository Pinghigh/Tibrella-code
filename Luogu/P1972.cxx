#include <algorithm>
#include <cstdio>

#if defined(__LINUX__)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

#if defined(__WINDOWS__)
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

char ch;
template <typename _Type>
void read(_Type& _x) {
    _x = 0;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        _x = _x * 10 + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename _Type, typename... _Args>
void read(_Type& _x, _Args&... _args) {
    read(_x);
    read(_args...);
}

template <typename _Type>
void write(_Type _x, char _ch) {
    static int sta[40];
    int pos = 0;
    do {
        sta[pos++] = (_x % 10);
        _x /= 10;
    } while (_x);
    while (pos--) {
        putchar(sta[pos] ^ 48);
    }
    putchar(_ch);
}

#define lowbit(__x) ((__x) & -(__x))
#define N 1000514

using std::sort;

int tree[N];
int n, m;

void modify(int pos, int x) {
    for (int i = pos; i <= n; i += lowbit(i)) {
        tree[i] += x;
    }
}

int query(int pos) {
    int res = 0;
    for (int i = pos; i; i -= lowbit(i)) {
        res += tree[i];
    }
    return res;
}

struct question {
    int l, r;
    int id;
    bool operator<(question& examp) {
        return this->r < examp.r;
    }
} q[N];

int mir[N];
int ori[N];
int ans[N];

int main() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(ori[i]);
    }
    read(m);
    for (int i = 1; i <= m; ++i) {
        read(q[i].l, q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + m + 1);
    int i = 0;
    for (int j = 1; j <= m; ++j) {
        while (i < q[j].r) {
            ++i;
            if (mir[ori[i]]) {
                modify(mir[ori[i]], -1);
            }
            modify(i, 1);
            mir[ori[i]] = i;
        }
        // i = q[j].r +1;
        ans[q[j].id] = query(q[j].r) - query(q[j].l - 1);
    }

    for (int j = 1; j <= m; ++j) {
        write(ans[j], '\n');
    }

    return 0;
}