#include <cstdio>
#include <cstring>

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
    if (!__x)
        putchar(48);
    else {
        if (__x < 0) {
            __x = -__x;
            putchar('-');
        }
        static char __output_stack[64], __pos;
        __pos = 0;
        do {
            __output_stack[__pos++] = __x % 10 ^ 48;
            __x /= 10;
        } while (__x);
        while (__pos--) {
            putchar(__output_stack[__pos]);
        }
    }
    putchar(__ch);
}

template <typename __outputType, typename... __outputArgs>
void write(__outputType __x, char __ch, __outputArgs... __args) {
    write(__x, __ch);
    write(__args...);
}

#include <algorithm>
#include <cmath>
#include <chrono>

using i8 = char;
using i16 = short int;
using i32 = long int;
using i64 = long long int;
using i128 = __int128;

template <typename type>
type gcd(type a, type b) {
    while (b)
        a %= b, std::swap(a, b);
    return a;
}

i128 p, b, n;

template <typename type>
type binpow(type x, type y) {
    type res = 1;
    x %= p;
    while (y) {
        if (y & 1) (res %= p) *= x %= p;
        x *= x %= p;
        y >>= 1;
    }
    return res % p;
}

auto max = [](auto a, auto b) { return a > b ? a : b; };

auto min = [](auto a, auto b) { return a < b ? a : b; };

#include <unordered_map>

struct my_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    // 针对 std::pair<int, int> 作为主键类型的哈希函数
    size_t operator()(std::pair<uint64_t, uint64_t> x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.first + FIXED_RANDOM) ^ (splitmix64(x.second + FIXED_RANDOM) >> 1);
    }
};

std::unordered_map<i64, i64, my_hash> mp;  // 存储的实际上是模数所对应的最大 r（从小到大枚举，挨个覆盖）

#include <cstdlib>

void failed() {
    puts("no solution");
    exit(0);
}

void output(i128 x) {
    write(x, '\n');
    exit(0);
}

int main() {
    read(p, b, n);

    b = (b % p + p) % p;
    n = (n % p + p) % p;

    if (b == 0) {
        if (n == 0) output(1);
        failed();
    }
    if (n == 1) {
        output(0);
    }
    if (b == 1) {
        failed();
    }

    i128 m = sqrt(p), z = n;
    for (i128 i = 0; i < m; ++i) {
        mp[z] = i;
        z = z * b % p;
    }
    z = binpow(b, m);
    for (i128 i = 1, pian = z; i <= p / m + 10; ++i) {
        auto it = mp.find(z);
        if (it != mp.end()) {
            output(m * i - it->second);
        }
        z = z * pian % p;
    }
    failed();

    return 0;
}