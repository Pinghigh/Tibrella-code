#include <algorithm>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,sse4.2,bmi,bmi2,lzcnt,popcnt,mmx,abm,sse4a")



#define N 1003

#define i64 long long

i64 i, j, k;
i64 n, m;

struct good {
    i64 a, b, c;

    void read() {
        cin >> a >> b >> c;
    }
} shop[N];

i64 tot, ans = -0x3f3f3f3f;

int main() {
    cin >> n >> m;
    for (i64 i = 1; i <= n; ++i) shop[i].read();

    for (i = -1; i < 2; i += 2)
        for (j = -1; j < 2; j += 2)
            for (k = -1; k < 2; k += 2) {
                tot = 0;
                std::sort(shop + 1, shop + n + 1, [](good &a, good &b) { return (a.a * i + a.b * j + a.c * k) > (b.a * i + b.b * j + b.c * k); });
                for (auto cnt = shop; cnt != shop + m + 1; ++cnt) tot += cnt->a * i + cnt->b * j + cnt->c * k;
                ans = std::max(ans, tot);
            }

    cout << ans << '\n';
    return 0;
}