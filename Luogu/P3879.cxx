#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

struct custom_hash {
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

using u32 = uint32_t;
using u64 = uint64_t;
const u32 seed = 131;
const u64 mod1 = 402653189;
const u64 mod2 = 1610612741;
using puu = std::pair<u64, u64>;

std::unordered_map<puu, std::list<u32>, custom_hash> hd;
std::unordered_map<puu, bool, custom_hash> st;

puu get_hash(std::string& str) {
    puu hash = { 0, 0 };
    for (auto& c : str) {
        hash.first = (hash.first * seed % mod1 + c) % mod1;
        hash.second = (hash.second * seed % mod2 + c) % mod2;
    }
    return hash;
}

u32 n, m, l;
std::string s;

using std::cin;
using std::cout;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> l;
        st.clear();
        while (l--) {
            cin >> s;
            puu hash = get_hash(s);
            auto bit = st.find(hash);
            if (bit != st.end()) continue;
            auto it = hd.find(hash);
            if (it == hd.end()) it = hd.insert({ hash, std::list<u32>() }).first;
            it->second.emplace_back(i);
            st.insert({ hash, true });
        }
    }
    cin >> m;
    while (m--) {
        cin >> s;
        puu hash = get_hash(s);
        auto it = hd.find(hash);
        if (it != hd.end()) {
            for (auto& c : it->second) {
                cout << c << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}