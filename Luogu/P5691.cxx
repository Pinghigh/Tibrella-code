#pragma GCC target("bmi,bmi2,sse4.2,sse4.1,sse4,avx2,lzcnt,fma,abm,mmx")

#include <bitset>
#include <iostream>
#include <unordered_map>
#include <chrono>

#define LL long long
using std::bitset;
using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;

#define N 10
#define M 160

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }

  // 针对 std::pair<int, int> 作为主键类型的哈希函数
  size_t operator()(std::pair<uint64_t, uint64_t> x) const {
    static const uint64_t FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x.first + FIXED_RANDOM) ^
           (splitmix64(x.second + FIXED_RANDOM) >> 1);
  }
};

LL binpow(LL a, LL b) {
    if (!b) {
        return 1;
    }
    LL res = binpow(a, b >> 1);
    if (b & 1) {
        return res * res * a;
    } else {
        return res * res;
    }
}

template <typename T>
T max(const T& a, const T& b) {
    return (a > b ? a : b);
}
template <typename T>
T min(const T& a, const T& b) {
    return (a < b ? a : b);
}

LL n, m;
unordered_map<LL, LL, custom_hash> l, r;
LL ans;
bitset<M> st[N];
LL dict[N][M];

class term {
public:
    LL no;
    LL k, p;
    LL calc(LL& val) {
        if (!st[no][val]) {
            dict[no][val] = k * binpow(val, p);
            st[no][val] = 1;
        }
        return dict[no][val];
    }
} data[N];

void dfs(unordered_map<LL, LL, custom_hash>& res, LL hh, LL num) {
    for (LL i = 1; i <= m; ++i) {
        // cout << hh << ' ';
        if (hh == (n >> 1)) {
            res[num + data[n >> 1].calc(i)] += 1;
        } else if (hh == n) {
            res[num + data[n].calc(i)] += 1;
        } else {
            dfs(res, hh + 1, num + data[hh].calc(i));
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> data[i].k >> data[i].p;
        data[i].no = i;
    }

    dfs(l, 1, 0);
    dfs(r, (n >> 1) + 1, 0);
    for (auto it : l) {
        ans += (it.second * r[-it.first]);
    }
    cout << ans;

    return 0;
}