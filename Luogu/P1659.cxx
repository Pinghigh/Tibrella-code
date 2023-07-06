#include <algorithm>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
}



constexpr int MAXN = 1e6 + 514;
const int mod = 19930726;

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res *= a;
            res %= mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res % mod;
}

string ori, b;
long long int n, k;
int size;
long long int hw[MAXN];
long long int ans=1;
int mid, mr;
int p[MAXN];
int pos;

void init(string& a, string& res) {
    res += "$";
    res+=a;
    res += '^';
}

void manacher() {
    for (int i = 1; i <= n; ++i) {
        if (i < mr) {
            p[i] = min(p[(mid << 1) - i], mr - i);
        } else {
            p[i] = 1;
        }

        while (b[i + p[i]] == b[i - p[i]]) {
            ++p[i];
        }

        ++hw[1];
        --hw[(p[i] << 1)];
        

        if (mr < i + p[i]) {
            mr = i + p[i];
            mid = i;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ori.reserve(MAXN);
    b.reserve(MAXN * 2);

    cin >> n >> k >> ori;

    pos = n+1;
    init(ori, b);
    // cout << b;
    manacher();
    hw[0]=0;
    for (int i = 1; i <= n; ++i) {
        hw[i] += hw[i - 1];
        // cout << "i: " << i << " hw[i]: " << hw[i] << " hw[i-1]: " << hw[i-1] << endl; 
    }

    while (k > 0) {
        --pos;
        if (pos%2==0) {
            continue;
        }
        if (k > hw[pos]) {
            ans *= (binpow(pos,hw[pos])%mod);
            // cout << "pos: " << pos << " k: " << k << endl;
            ans %= mod;
            k -= hw[pos];
        } else {
            ans *= binpow(pos,k);
            // cout << "pos: " << pos << " k: " << k << endl;
            ans %= mod;
            break;
        }
    }
    ans %= mod;
    cout << ans << endl;

    return 0;
}