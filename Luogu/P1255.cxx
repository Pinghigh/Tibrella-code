#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

const i64 B = 1e16;
const i64 MOD = B * 10;
struct inf_t {
    std::vector<i64> val;

    template <typename T>
    inf_t& operator=(T b) {
        this->val.resize(0);
        while (b) {
            this->val.emplace_back(b % MOD);
            b /= MOD;
        }
        return *this;
    }
};

std::istream& operator>>(std::istream& in, inf_t& num) {
    std::string str;
    in >> str;
    i64 tmp = 0;
    i64 f = 1;
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        tmp = tmp + f * ((*it) ^ 48);
        f *= 10;
        if (tmp > B) {
            num.val.emplace_back(tmp);
            tmp = 0;
            f = 1;
        }
    }
    if (tmp) num.val.emplace_back(tmp);
    return in;
}

std::ostream& operator<<(std::ostream& out, inf_t num) {
    if (!num.val.size())
        out << '0';
    else {
        cout << num.val.back();
        cout.fill('0');
        for (auto it = num.val.rbegin() + 1; it != num.val.rend(); ++it)
            cout << std::setw(17) << *it;
    }
    return out;
}

inf_t operator+(inf_t a, inf_t b) {
    i64 tmp = 0;
    inf_t res;
    for (i32 i = 0, lim = std::max(a.val.size(), b.val.size()); i < lim; ++i) {
        if (i < a.val.size()) tmp += a.val[i];
        if (i < b.val.size()) tmp += b.val[i];
        res.val.emplace_back(tmp % MOD);
        tmp /= MOD;
    }
    if (tmp) res.val.emplace_back(tmp);
    return res;
}

inf_t feb[114514];
int main() {
    feb[0] = 1;
    feb[1] = 1;
    long long int t;
    cin >> t;
    long long int i = 0;
    while (t > i) {
        feb[i + 2] = feb[i] + feb[i + 1];
        feb[i].val.clear();
        feb[i].val.shrink_to_fit();
        i++;
    }
    cout << feb[t];
    return 0;
}