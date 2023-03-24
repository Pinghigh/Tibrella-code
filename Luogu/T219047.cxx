#include <cstdio>
#include <queue>

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

using std::priority_queue;
using std::vector;

#define endl '\n'

// struct str {
//     int len;
//     int start;
// };

#define N 1000005

// priority_queue<str, vector, [](const auto& a, const auto& b) { return a.len > b.len; }> res_heap;
// priority_queue<str, vector, [](const auto& a, const auto& b) { return a.start < b.start; }> start_heap;
vector<int> ori(N);
int he[N], en[N];
// str tmp;
int n;
int t1;
int length;
int sta;
auto max = [](auto a, auto b) { return a > b ? a : b; };
auto abs = [](auto a) { return a > -1 ? a : -a; };

int main() {
    ori.resize(0);

    read(n);
    for (int i = 0; i < n; ++i) {
        read(t1);
        ori.push_back(t1);
    }
    if (n == 1) {
        puts("1");
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (ori[i] > ori[i + 1]) {
            en[i] = i - sta + 1;
            for (int j = sta; j <= i; ++j) {
                // tmp.start = j;
                // tmp.len = i - j + 1;
                // start_heap.push(tmp);
                // res_heap.push(tmp);
                he[j] = i - j + 1;
                // printf("%d %d\n",j,he[j]);
            }
            sta = i + 1;
        }
    }

    int res = 0;

    for (int i = 0; i < n; ++i) {
        res = max(res, (ori[i] - ori[i + 2] > 1) ? (i==n-1?en[i]:(en[i] + 1)) : (i+2>=n-1?en[i]:(en[i] + 1)) + he[i + 2]);
    }

    write(res,'\n');

    return 0;
}