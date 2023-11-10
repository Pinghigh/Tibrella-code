#include <cstdio>

using i8 = char;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using i32 = int;
using i64 = long long;
using f64 = double;

struct istream {
    const static size_t SIZE = 1 << 18;
    char buf[SIZE], *cur, *end;
    char get() {
        if (cur == end) {
            cur = buf;
            end = buf + fread(buf, 1, SIZE, stdin);
        }
        return (cur != end) ? *(cur++) : EOF;
    }

    istream& operator>>(char& c) {
        do
            c = get();
        while (c == ' ' || c == '\n' || c == '\r');
        return *this;
    }

    template <typename T>
    istream& operator>>(T& x) {
        x = 0;
        char c;
        do
            c = get();
        while (c < 48 || c > 57);
        do {
            x = (x << 3) + (x << 1) + (c ^ 48);
            c = get();
        } while (c > 47 && c < 58);
        return *this;
    }
} cin;

#define N 100005
#define C 50

#include <algorithm>

f64 ans[N], cnt[C], ctmp[C];
i32 d[N], b[N];

int main() {
    i32 n, k, l;
    cin >> n >> k >> l;
    for (i32 i = 1; i <= n; ++i) {
        char c;
        static f64 las = 0;
        static i32 delta = 0;
        i32 dd, bb;
        cin >> dd >> bb >> c;
        // printf("%d %d %c \n", dd, bb, c);
        if (c == 'D') {
            ans[bb] += l - dd;
            for (i32 j = 0; j < k; ++ j) ctmp[(j+bb) % k] = cnt[j];
            std::swap(cnt, ctmp);
            cnt[bb] += (dd - las) / 2;
            las = dd;
            delta = (delta + bb) % k;
        } else {
            ans[bb] += (dd - las) / 2;
            for (i32 j = 0; j < k; ++ j) ans[(j+bb) % k] += cnt[j];
            ans[(delta+bb)%k] += dd/2.0;
        }
    }
    for (i32 i = 0; i < k; ++i)
        printf("%.1lf\n", ans[i]);

    return 0;
}