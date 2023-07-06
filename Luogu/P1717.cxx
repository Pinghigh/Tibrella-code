#include <iostream>

using std::cin;
using std::cout;

const char endl = '\n';
constexpr int N = 25 + 5;
constexpr int TIME = 16 * 60 / 5 + 5;

int h, n;
int f[N][TIME];
int hv;
int fish;
int tim[N];

struct pool {
    int f;
    int d, t;
} road[N];

template <typename T>
T max(T __a, T __b) {
    return __a > __b ? __a : __b;
}

int ans;

int main() {
    // std::ios::sync_with_stdio(false);
    // cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> h;
    for (int i = 1; i <= n; ++i) {
        cin >> road[i].f;
    }
    for (int i = 1; i <= n; ++i) {
        cin >> road[i].d;
    }
    for (int i = 2; i <= n; ++i) {
        cin >> road[i].t;
        tim[i] = road[i].t + tim[i - 1];
    }

    h = h * 60 / 5;
    hv = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = tim[i]; j <= h; ++j) {
            for (int k = 0; j - tim[i] - k >= 0 && (k - 1) * road[i].d < road[i].f; ++k) {
                f[i][j] = max(f[i][j], f[i - 1][j - k - road[i].t] + k * (road[i].f + road[i].f - road[i].d * (k-1)) / 2);
                ans = max(ans, f[i][j]);
            }
        }
    }

    cout << ans << endl;

    return 0;
}