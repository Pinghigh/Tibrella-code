#include <bitset>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using ull = unsigned long long;

const int mod = 201326611;
const int seed = 196613;
const char endl = '\n';

// BKDR Hash Function
ull getHash(string& str) {
    ull hash = 0;

    // while (*str)
    // {
    //     hash = hash * seed + (*str++);
    // }

    for (auto& c : str) {
        hash = hash * seed + c;
    }

    return (((hash & 0x8FFFFFFFFFFFFFFF | seed) >> 3) + (seed << 3));
}

std::bitset<250000000> hash;
int ans;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string a;
    int n;
    cin >> n;
    while (n--) {
        cin >> a;
        ull sh = getHash(a) % mod;
        // if (!hash[sh]) {
        //     ++ans;
        //     hash[sh]
        // }
        ans += (hash[sh] ^ 1);
        hash[sh] = 1;
    }

    cout << ans << endl;

    return 0;
}