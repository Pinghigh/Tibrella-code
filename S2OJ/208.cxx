#include <cstdio>

#ifdef __WINDOWS__
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef __LINUX__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

template <typename T>
void read(T& _x) {
    _x = 0;
    static char ch;
    do {
        ch = getchar();
    } while (ch < 48 || ch > 57);
    do {
        _x = _x * 10 + (ch ^ 48);
        ch = getchar();
    } while (ch > 47 && ch < 58);
}

template <typename T, typename... Args>
void read(T& _x, Args&... args) {
    read(_x);
    read(args...);
}

template <typename T>
void write(T _x, char ch) {
    static int sta[40];
    static int pos;
    pos = 0;
    do {
        sta[++pos] = _x % 10;
        _x /= 10;
    } while (_x);

    do {
        putchar(sta[pos--] ^ 48);
    } while (pos);

    putchar(ch);
}

#define N 100015
#define L 17
// #define log(x) std::__lg(x)

int n, m;
int a[N];
int x, l, r;
int ll, rr;
int f[L + 5][N];
auto min = [](auto _x, auto _y) { return _x < _y ? _x : _y; };
auto log = [](int __n) { return sizeof(int) * __CHAR_BIT__ - 1 - __builtin_clz(__n); };

int query(int lef, int rig) {
    int llen = (rig - lef == 0) ? 0 : log(rig - lef);
    return min(f[llen][lef], f[llen][rig - (1 << llen) + 1]);
}

int main() {
    read(n, m);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        f[0][i] = a[i];
    }

    for (int lg = 1; lg <= log(n) + 1; ++lg) {
        for (int i = 1, c = 1 << lg; i + c - 1 <= n; ++i) {
            f[lg][i] = min(f[lg - 1][i], f[lg - 1][i + (1 << lg - 1)]);
            // printf("%d %d %d\n", i, i - 1 + c, f[lg][i]);
        }
    }

    while (m--) {
        read(x, l, rr);
        for (;;) {
            r = rr;
            if (l > r) {
                // write(x, '\n');
                break;
            }
            int bot = query(l, r);
            while (l < r) {
                int mid = l + r >> 1;
                if (query(l, mid) <= x) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            x %= a[r];
            l = r + 1;
            // write(x,'\n');
        }
    }
    return 0;
}
