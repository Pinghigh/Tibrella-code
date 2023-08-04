#pragma GCC target("fma,lzcnt,popcnt,bmi,bmi2,ssse3")
#pragma GCC optimize("Ofast,unroll-loops,inline")

#include <iostream>
#include <string>

using std::cin;
using std::cout;

using u32 = unsigned int;
using u64 = unsigned long long;

#define N 100005

constexpr u64 mod = 1e9 + 7;

u32 las[3];
u64 f[N];
std::string s;
unsigned sum = 0;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s;
    for (u32 i = 1; i < s.size(); ++i)
        if (s[i] == s[i - 1]) goto success;
    cout.put('1');
    return 0;

success:
    las[1] = las[0] = las[2] = N - 1;
    for (u32 i = 0; i < s.size(); ++i) {
        sum = (sum + s[i] - 'a' + 1) % 3;
        if (sum) ++f[i];
        f[i] = (f[i] + f[las[0]] + f[las[1]] + f[las[2]] - f[las[sum]]) % mod;
        las[sum] = i;
    }
    cout << f[s.size() - 1];

    return 0;
}