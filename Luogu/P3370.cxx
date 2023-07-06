#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using u64 = unsigned long long;

const u64 seed = 12289;
const char endl = '\n';

u64 getHash(string& str) {
    u64 hash = 0;

    for (auto& c : str) {
        hash = hash * seed + c;
    }

    return hash;
}

int ans;
std::vector<u64> hash;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string a;
    int n;
    cin >> n;
    ans = n;
    hash.reserve(n + 10);
    while (n--) {
        cin >> a;
        hash.emplace_back(getHash(a));
    }

    u64 prev = -114514;
    std::sort(hash.begin(), hash.end());
    for (auto& i : hash) {
        if (i == prev) --ans;
        prev = i;
    }

    cout << ans << endl;

    return 0;
}